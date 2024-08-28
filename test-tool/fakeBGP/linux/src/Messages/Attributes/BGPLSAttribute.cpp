/*
 * BGPLSAttribute.cpp
 *
 *  Created on: Mar 6, 2014
 *      Author: egboeny
 */

#include "BGPLSAttribute.h"

BGPLSAttribute::BGPLSAttribute(uint8_t type) {
	binary_message.flags = ATTR_OPTIONAL | ATTR_TRANSITIVE;	//It should NOT be transitive, but ODL thinks it should be
	binary_message.type = type;		//This type is not allocated yet, but it seems that ODL use this value
	binary_message.setLength(3);	//In the beginning this is the initial length. Later this becomes longer
}

BGPLSAttribute::~BGPLSAttribute() {
	// TODO Auto-generated destructor stub
}

