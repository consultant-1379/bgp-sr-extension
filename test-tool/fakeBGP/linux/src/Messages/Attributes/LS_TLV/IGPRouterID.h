/*
 * NodeDescriptorSubTLV.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef IGPROUTERID_H_
#define IGPROUTERID_H_

#include "LSTLV.h"

class IGPRouterID: public LSTLV {
public:
	IGPRouterID(uint32_t routerID);
	IGPRouterID(uint8_t* routerId, unsigned length);
	virtual ~IGPRouterID();
};

#endif /* IGPROUTERID_H_ */
