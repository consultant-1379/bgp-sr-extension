/*
 * AS.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: egboeny
 */

#include "PrefixMetric.h"

PrefixMetric::PrefixMetric(uint32_t metric) : LSTLV(1155) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(metric);
}

PrefixMetric::~PrefixMetric() {
	// TODO Auto-generated destructor stub
}

