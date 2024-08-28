/*
 * NodeDescriptorSubTLV.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#include "IGPRouterID.h"

IGPRouterID::IGPRouterID(uint32_t routerID) : LSTLV(515) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(routerID);
}

IGPRouterID::IGPRouterID(uint8_t* routerId, unsigned length) : LSTLV(515) {
	setLength(length);
	memcpy(data.value, routerId, length);
}

IGPRouterID::~IGPRouterID() {
	// TODO Auto-generated destructor stub
}

