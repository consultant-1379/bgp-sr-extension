/*
 * NextHop.cpp
 *
 *  Created on: May 5, 2014
 *      Author: egboeny
 */

#include "NextHop.h"

NextHop::NextHop(uint32_t nextHop) {
	binary_message.flags = ATTR_TRANSITIVE;
	binary_message.type = 3;
	binary_message.setLength(7);
	*((uint32_t*)binary_message.getValStart()) = htonl(nextHop);
}

NextHop::~NextHop() {
	// TODO Auto-generated destructor stub
}

