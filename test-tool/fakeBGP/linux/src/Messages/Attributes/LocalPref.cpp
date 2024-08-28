/*
 * LocalPref.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#include "LocalPref.h"

LocalPref::LocalPref(uint32_t localPref) {
	binary_message.flags = ATTR_TRANSITIVE;
	binary_message.type = 5;
	binary_message.setLength(7);
	*((uint32_t*)binary_message.getValStart()) = htonl(localPref);
}

LocalPref::~LocalPref() {
	// TODO Auto-generated destructor stub
}

