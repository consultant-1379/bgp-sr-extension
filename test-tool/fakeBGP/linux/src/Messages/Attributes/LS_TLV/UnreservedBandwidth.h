/*
 * UnreservedBandwidth.h
 *
 *  Created on: Mar 7, 2014
 *      Author: egboeny
 */

#ifndef UNRESERVEDBANDWIDTH_H_
#define UNRESERVEDBANDWIDTH_H_

#include "LSTLV.h"

class UnreservedBandwidth: public LSTLV {
public:
	UnreservedBandwidth(float bytesPerSec[8]);
	virtual ~UnreservedBandwidth();
};

#endif /* UNRESERVEDBANDWIDTH_H_ */
