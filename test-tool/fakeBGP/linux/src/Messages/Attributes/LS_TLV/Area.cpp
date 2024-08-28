/*
 * PrefixSID.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#include "Area.h"

Area::Area(uint32_t area) : LSTLV(514) {
    setLength(4);
    *((uint32_t*) data.value) = htonl(area);
}

Area::~Area() {
	// TODO Auto-generated destructor stub
}

