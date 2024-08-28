/*
 * ASPath.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#include "ASPath.h"

ASPath::ASPath() {
	binary_message.flags = ATTR_TRANSITIVE | ATTR_EXTENDEDLEN;
	binary_message.type = 2;
	binary_message.setLength(4);
}

ASPath::~ASPath() {
	// TODO Auto-generated destructor stub
}

