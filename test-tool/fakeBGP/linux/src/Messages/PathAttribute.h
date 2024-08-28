/*
 * PathAttribute.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef PATHATTRIBUTE_H_
#define PATHATTRIBUTE_H_

#include "Message.h"
#include "Attributes/LS_TLV/LSTLV.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <iostream>

#define ATTR_OPTIONAL 	0x80
#define ATTR_TRANSITIVE 	0x40
#define ATTR_INCOMPLETE	0x20
#define ATTR_EXTENDEDLEN	0x10

class PathAttribute: public Message {
protected:

#pragma pack(push,1)	//Do not use padding!
	struct AttributeStruct {
		uint8_t flags;
		uint8_t type;
		uint8_t length[];
		uint16_t extLength[];
		uint8_t value[4096-2];

		uint8_t* getValStart() { return value + ((flags & ATTR_EXTENDEDLEN)?2:1); }
		const unsigned getLength() const {
			if (flags & ATTR_EXTENDEDLEN)
				return ntohs(*extLength) + 4;
			else
				return (*length) + 3;
		}
		void setLength(uint16_t len) {
			if (flags & ATTR_EXTENDEDLEN) {
				if (len < 4) {
					std::cout << "Length cannot be less than 4. Exiting." << std::endl;
					throw;
				}
				*extLength = htons(len - 4);
			}
			else {
				if (len < 3) {
					std::cout << "Length cannot be less than 3. Exiting." << std::endl;
					throw;
				}
				if (len > 0xff) {
					std::cout << "Short length must not be higher than 0xff. Exiting." << std::endl;
					throw;
				}
				*length = len - 3;
			}
		}

		uint8_t* endPointer() const { return ((uint8_t *)this) + getLength(); }

	};
#pragma pack(pop)

	AttributeStruct binary_message;

public:
	PathAttribute();
	virtual ~PathAttribute();

	virtual const void* getMessage() const { return &binary_message; }
	virtual const unsigned getSize() const { return binary_message.getLength(); }
};

class BGPLSPathAttribute : public PathAttribute {

public:
	BGPLSPathAttribute()  {}
	virtual ~BGPLSPathAttribute() {}

	void appendTLV(const LSTLV& tlv) {
		if (binary_message.getLength() + tlv.getFullSize() > sizeof(binary_message)) {
			std::cout << "Attribute size would be to big. Exiting." << std::endl;
			throw;
		}

		memcpy(binary_message.endPointer(), tlv.startPointer(), tlv.getFullSize());
		binary_message.setLength(binary_message.getLength() + tlv.getFullSize());
	}
};

#endif /* PATHATTRIBUTE_H_ */
