/*
 * MaxReservableBandwidth.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: egboeny
 */

#include "MaxReservableBandwidth.h"

MaxReservableBandwidth::MaxReservableBandwidth(float bw) : LSTLV(1090){
	setLength(4);
	uint32_t* bwAsInt = (uint32_t*) &bw;
	*((uint32_t*)data.value) = htobe32(*bwAsInt);
}

MaxReservableBandwidth::~MaxReservableBandwidth() { }

