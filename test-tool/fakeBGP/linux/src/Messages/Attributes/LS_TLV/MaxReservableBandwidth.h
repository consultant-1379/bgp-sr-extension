/*
 * MaxReservableBandwidth.h
 *
 *  Created on: Mar 11, 2014
 *      Author: egboeny
 */

#ifndef MAXRESERVABLEBANDWIDTH_H_
#define MAXRESERVABLEBANDWIDTH_H_

#include "LSTLV.h"

class MaxReservableBandwidth: public LSTLV {
public:
	MaxReservableBandwidth(float bw);
	virtual ~MaxReservableBandwidth();
};

#endif /* MAXRESERVABLEBANDWIDTH_H_ */
