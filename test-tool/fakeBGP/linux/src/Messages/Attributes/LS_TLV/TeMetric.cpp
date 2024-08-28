/*
 * TeMetric.cpp
 *
 *  Created on: Dec 12, 2017
 *      Author: ericsson
 */

#include "TeMetric.h"

TeMetric::TeMetric(uint16_t metric) : LSTLV(1092) {

	setLength(2);
	*((uint16_t*) data.value) = htons(metric);
}

TeMetric::~TeMetric() {
	// TODO Auto-generated destructor stub
}

