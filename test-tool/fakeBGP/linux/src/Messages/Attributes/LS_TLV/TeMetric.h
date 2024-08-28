/*
 * TeMetric.h
 *
 *  Created on: Dec 12, 2017
 *      Author: ericsson
 */

#ifndef TEMETRIC_H_
#define TEMETRIC_H_

#include "LSTLV.h"

class TeMetric: public LSTLV {
public:
	TeMetric(uint16_t cost);
	virtual ~TeMetric();
};

#endif /* TEMETRIC_H_ */
