/*
 * PrefixSID.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#include "UnidirectionalLinkDelay.h"

#pragma pack(push,1)    //Do not use padding!
struct DataStruct {
    uint8_t flags;
    uint8_t delay[3];
};
#pragma pack(pop)

UnidirectionalLinkDelay::UnidirectionalLinkDelay(uint8_t flags, uint32_t delay, uint16_t type) : LSTLV(type) {
	if (delay >= 16777216)
	    throw std::string("Too big for delay.");

    setLength(sizeof(DataStruct));
	DataStruct* ds = (DataStruct*) data.value;
	*((uint32_t*)(((uint8_t*)ds->delay)-1)) = htonl(delay);      //We're using that this is not the first byte
	ds->flags = flags;      //Now filling the right flags value
}

UnidirectionalLinkDelay::~UnidirectionalLinkDelay() {
	// TODO Auto-generated destructor stub
}

