/*
 * PrefixSID.h
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#ifndef UNIDIRECTIONALLINKDELAY_H_
#define UNIDIRECTIONALLINKDELAY_H_

#include "LSTLV.h"

class UnidirectionalLinkDelay: public LSTLV {
public:
    UnidirectionalLinkDelay(uint8_t flags, uint32_t delay, uint16_t type = 1101) ;
	virtual ~UnidirectionalLinkDelay();
};

#endif /* UNIDIRECTIONALLINKDELAY_H_ */
