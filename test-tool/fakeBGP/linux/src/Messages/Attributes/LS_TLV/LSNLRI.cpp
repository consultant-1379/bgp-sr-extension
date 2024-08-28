/*
 * NodeNLRI.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#include "LSNLRI.h"
#include <endian.h>

LSNLRI::LSNLRI(uint8_t type, uint8_t protocolID, uint64_t identifier) :
	LSTLV(type) {

	NLRIData = (struct NLRINodeStruct*) data.value;
	setLength(sizeof(NLRINodeStruct));
	NLRIData->protocolID = protocolID;
	NLRIData->identifier = htobe64(identifier);
}

LSNLRI::~LSNLRI() {
	// TODO Auto-generated destructor stub
}

