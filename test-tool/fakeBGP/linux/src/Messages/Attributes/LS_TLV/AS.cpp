/*
 * AS.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: egboeny
 */

#include "AS.h"

AS::AS(uint32_t as) : LSTLV(512) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(as);
}

AS::~AS() {
	// TODO Auto-generated destructor stub
}

