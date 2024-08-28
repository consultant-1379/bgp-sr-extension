/*
 * NodeDescriptorSubTLV.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef PREFIXMETRIC_H_
#define PREFIXMETRIC_H_

#include "LSTLV.h"

class PrefixMetric: public LSTLV {
public:
    PrefixMetric(uint32_t metric);
	virtual ~PrefixMetric();
};

#endif /* PREFIXMETRIC_H_ */
