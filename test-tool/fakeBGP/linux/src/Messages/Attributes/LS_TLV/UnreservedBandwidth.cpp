/*
 * UnreservedBandwidth.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: egboeny
 */

#include "UnreservedBandwidth.h"
#include <endian.h>

UnreservedBandwidth::UnreservedBandwidth(float bytesPerSec[8]) : LSTLV(1091) {
	setLength(8*4);		//8x 32bit IEEE float

	uint32_t* source = (uint32_t*) bytesPerSec;			// Note, we handle them as int to make it easier
	uint32_t* target = (uint32_t*) data.value;			// to do the endian convertation

	for (int c = 0; c<8; c++) {
		target[c] = htobe32(source[c]);
	}
}

UnreservedBandwidth::~UnreservedBandwidth() {}

