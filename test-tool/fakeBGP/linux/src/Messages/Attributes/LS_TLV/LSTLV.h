/*
 * LSTLV.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef LSTLV_H_
#define LSTLV_H_

#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>
#include <iostream>

class LSTLV {

protected:
#pragma pack(push,1)	//Do not use padding!
	struct {
		uint16_t type;
		uint16_t length;
		uint8_t  value[4096-4];
	} data;
#pragma pack(pop)

	void setLength(uint16_t length) {
		data.length = htons(length);
	}

public:
	LSTLV(uint16_t type) {
		data.type = htons(type);
		setLength(0);
	}
	virtual ~LSTLV() {}
	const uint16_t getLength() const { return ntohs(data.length); }
	const uint16_t getFullSize() const { return getLength() + 4; }
	uint8_t* startPointer() const { return (uint8_t*) &data; }
	uint8_t* endPointer() const { return startPointer() + getFullSize(); }

	void appendData(void* src, unsigned size) {
		if (size + getFullSize() > sizeof(data)) {
			std::cout << "TLV would be too long. Exiting." << std::endl;
			throw;
		}

		memcpy(endPointer(), src, size);
		setLength(getLength() + size);
	}
};

#endif /* LSTLV_H_ */
