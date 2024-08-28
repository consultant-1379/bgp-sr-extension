/*
 * LinkLocalRemoteIdentifierSubTLV.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: enyedi
 */

#include "LinkLocalRemoteIdentifierSubTLV.h"

LinkLocalRemoteIdentifierSubTLV::LinkLocalRemoteIdentifierSubTLV(uint32_t localId, uint32_t remoteId) : LSTLV(258) {
	setLength(8);
	*((uint32_t*) data.value) = htonl(localId);
	*(((uint32_t*) data.value) +1) = htonl(remoteId);
}

LinkLocalRemoteIdentifierSubTLV::~LinkLocalRemoteIdentifierSubTLV() {
	// TODO Auto-generated destructor stub
}

