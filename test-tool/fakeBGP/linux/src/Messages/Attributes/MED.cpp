/*
 * MED.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#include "MED.h"

MED::MED(uint32_t medVal) {
	binary_message.flags = ATTR_OPTIONAL;
	binary_message.type = 4;
	binary_message.setLength(7);
	*((uint32_t*)binary_message.getValStart()) = htonl(medVal);
}

MED::~MED() {
	// TODO Auto-generated destructor stub
}

