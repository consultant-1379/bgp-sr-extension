/*
 * Origin.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#include "Origin.h"

Origin::Origin(OriginType type) {
	binary_message.flags = ATTR_TRANSITIVE;
	binary_message.type = 1;
	binary_message.setLength(4);
	*binary_message.getValStart() = type;
}

Origin::~Origin() {
	// TODO Auto-generated destructor stub
}

