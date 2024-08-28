/*
 * MaximumLinkBandwidth.cpp
 *
 *  Created on: Mar 8, 2014
 *      Author: egboeny
 */

#include "MaximumLinkBandwidth.h"
#include <endian.h>

MaximumLinkBandwidth::MaximumLinkBandwidth(float bw) : LSTLV(1089){

	setLength(4);
	uint32_t* bwAsInt = (uint32_t*) &bw;
	*((uint32_t*)data.value) = htobe32(*bwAsInt);

}

MaximumLinkBandwidth::~MaximumLinkBandwidth() {
	// TODO Auto-generated destructor stub
}

