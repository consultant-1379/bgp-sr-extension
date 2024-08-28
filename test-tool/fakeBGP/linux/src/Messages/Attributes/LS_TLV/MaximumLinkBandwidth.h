/*
 * MaximumLinkBandwidth.h
 *
 *  Created on: Mar 8, 2014
 *      Author: egboeny
 */

#ifndef MAXIMUMLINKBANDWIDTH_H_
#define MAXIMUMLINKBANDWIDTH_H_

#include "LSTLV.h"

class MaximumLinkBandwidth: public LSTLV {
public:
	MaximumLinkBandwidth(float bw);
	virtual ~MaximumLinkBandwidth();
};

#endif /* MAXIMUMLINKBANDWIDTH_H_ */
