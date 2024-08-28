/*
 * Metric.h
 *
 *  Created on: Mar 7, 2014
 *      Author: egboeny
 */

#ifndef METRIC_H_
#define METRIC_H_

#include "LSTLV.h"

class Metric: public LSTLV {
public:
	Metric(uint16_t cost);		//Note: metric can be anything, but 16 bits enough for OSPF
	virtual ~Metric();
};

#endif /* METRIC_H_ */
