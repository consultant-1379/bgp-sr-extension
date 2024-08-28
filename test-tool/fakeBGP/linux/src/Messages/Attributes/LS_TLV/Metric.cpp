/*
 * Metric.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: egboeny
 */

#include "Metric.h"

Metric::Metric(uint16_t metric) : LSTLV(1095) {

	setLength(2);
	*((uint16_t*) data.value) = htons(metric);
}

Metric::~Metric() {
	// TODO Auto-generated destructor stub
}

