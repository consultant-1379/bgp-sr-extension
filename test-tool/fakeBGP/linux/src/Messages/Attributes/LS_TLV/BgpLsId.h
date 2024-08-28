/*
 * NodeDescriptorSubTLV.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef BGPLSID_H_
#define BGPLSID_H_

#include "LSTLV.h"

class BgpLsId: public LSTLV {
public:
    BgpLsId(uint32_t bgpLsId);
	virtual ~BgpLsId();
};

#endif /* BGPLSID_H_ */
