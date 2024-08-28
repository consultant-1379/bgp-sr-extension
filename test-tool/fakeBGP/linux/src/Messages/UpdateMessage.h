/*
 * UpdateMessage.h
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#ifndef UPDATEMESSAGE_H_
#define UPDATEMESSAGE_H_

#include "Message.h"
#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include "PathAttribute.h"

class PathAttributeOld : public Message {
	typedef uint8_t StaticMessage[29];

	StaticMessage binary_message;

public:
	PathAttributeOld() {
		//Flags are (MSB to LSB): Optional/Well-known,Transitive,Incomplete,ExtendedLen
		StaticMessage binary_message =
							{
							//Origin IGP: flags|origin| 1B | IGP |
									       0x40, 0x01, 0x01, 0x00,
							//AS Path:    flags|ASpath| len=0B   |
									       0x50, 0x02, 0x00, 0x00,
							//NextHop:	  flags|NextHop| 4B |NH=101.101.101.101     |
									       0x40, 0x03, 0x04, 0x65, 0x65, 0x65, 0x65,
							//MED:		  flags| MED | 4B   |MED value = 0          |
									       0x80, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
							//LocalPref:  flags|LocPrf| 4B  |LocPrf value = 100     |
									       0x40, 0x05, 0x04, 0x00, 0x00, 0x00, 0x64
							};

		memcpy(this->binary_message, binary_message, sizeof(StaticMessage));
	}
	virtual ~PathAttributeOld() {}
	virtual const void* getMessage() const { return binary_message; }
	virtual const unsigned getSize() const { return sizeof(binary_message); }
};

//Only IPv4, and only the simplest one (at first)
class NLRI : public Message {
#pragma pack(push,1)	//Do not use padding!
	struct NLRIStruct {
		uint8_t 	preflen;
		uint32_t 	prefix;
	};
#pragma pack(pop)

	struct NLRIStruct binary_message;

public:
	NLRI(uint32_t prefix, uint8_t preflen) {
		//Check the prefix
		uint32_t mask=0;
		for (int cnt=0; cnt<32-preflen; cnt++)
			mask = (mask << 1) + 1;

		if ((prefix & mask) != 0)
			throw std::string("Bad prefix.");

		binary_message.preflen = preflen;
		binary_message.prefix = htonl(prefix);
	}
	virtual ~NLRI() {}
	virtual const void* getMessage() const { return &binary_message; }
	virtual const unsigned getSize() const { return 1 + binary_message.preflen/8 + ((binary_message.preflen%8)?1:0); }
};

class UpdateMessage: public Message {
#pragma pack(push,1)	//Do not use padding!
	struct UpdateStruct {
		uint8_t marker[16];
		uint16_t length;
		uint8_t type;
		uint16_t unfeasibleRouteLength;
		uint16_t pathAttributeLength;
		uint8_t tail[4096-23];

		UpdateStruct() {
			memset(marker, 0xff, 16);
			type = 2;
			length = htons(23);		//The length of the empty message
			unfeasibleRouteLength = 0;
			pathAttributeLength = 0;
		}
		void setLength(uint16_t length) { this->length = htons(length); }
		uint16_t getLength() const { return ntohs(length); }
		uint8_t* endPointer() const { return ((uint8_t *)this) + getLength(); }
		void appendMessage(const Message& message) {
			if (message.getSize() + getLength() > sizeof(tail)+23) {
				std::cerr << "Update message is too long!" << std::endl;
				throw;
			}

			memcpy(endPointer(), message.getMessage(), message.getSize());
			setLength(getLength() + message.getSize());
		}
	};
#pragma pack(pop)

	struct UpdateStruct binary_message;

public:

	UpdateMessage();
	virtual ~UpdateMessage();
	virtual const void* getMessage() const { return &binary_message; }
	virtual const unsigned getSize() const { return	binary_message.getLength(); }

	void appendAttribute(const PathAttribute attr) {
		binary_message.appendMessage(attr);
		binary_message.pathAttributeLength = htons(ntohs(binary_message.pathAttributeLength) + attr.getSize());
	}
	void appendNLRI(const NLRI nlri) {
		binary_message.appendMessage(nlri);
	}
};

#endif /* UPDATEMESSAGE_H_ */
