/*
 * AdiministrativeGroup.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: ericsson
 */

#include "AdministrativeGroup.h"

AdministrativeGroup::AdministrativeGroup(uint32_t administrativeGroup) : LSTLV(1088) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(administrativeGroup);
}

AdministrativeGroup::~AdministrativeGroup() {
	// TODO Auto-generated destructor stub
}

