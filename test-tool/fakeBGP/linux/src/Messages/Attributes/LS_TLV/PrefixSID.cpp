/*
 * PrefixSID.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#include "PrefixSID.h"

#pragma pack(push,1)    //Do not use padding!
struct DataStruct {
    uint8_t flags;
    uint8_t algorithm;
    uint32_t SID;
};
#pragma pack(pop)

#pragma pack(push,1)    //Do not use padding!
struct DataStruct2 {
    uint8_t flags;
    uint8_t algorithm;
    uint16_t reserved;
    uint32_t SID;
};
#pragma pack(pop)

PrefixSID::PrefixSID(uint8_t flags, uint32_t SID) : LSTLV(1158) {
	setLength(sizeof(DataStruct));
	DataStruct* ds = (DataStruct*) data.value;
	ds->flags = flags;
	ds->algorithm = 0;      //Shortest path. Currently only this is supported
	ds->SID = htonl(SID);
}

PrefixSID::PrefixSID(uint8_t flags, uint32_t SID, bool add_reserved_bytes) : LSTLV(1158) {
	setLength(sizeof(DataStruct2));
	DataStruct2* ds = (DataStruct2 *)data.value;
	ds->flags = flags;
	ds->algorithm = 0;      //Shortest path. Currently only this is supported
	ds->reserved = 0;
	ds->SID = htonl(SID);
}

PrefixSID::~PrefixSID() {
	// TODO Auto-generated destructor stub
}

