/*
 * BgpLsId.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: egboeny
 */

#include "BgpLsId.h"

BgpLsId::BgpLsId(uint32_t bgpLsId) : LSTLV(513) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(bgpLsId);
}

BgpLsId::~BgpLsId() {
	// TODO Auto-generated destructor stub
}

