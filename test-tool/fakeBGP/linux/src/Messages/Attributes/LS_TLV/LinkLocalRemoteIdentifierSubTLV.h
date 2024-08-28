/*
 * LinkLocalRemoteIdentifierSubTLV.h
 *
 *  Created on: Feb 28, 2014
 *      Author: enyedi
 */

#ifndef LINKLOCALREMOTEIDENTIFIERSUBTLV_H_
#define LINKLOCALREMOTEIDENTIFIERSUBTLV_H_

#include "LSTLV.h"

class LinkLocalRemoteIdentifierSubTLV: public LSTLV {
public:
	LinkLocalRemoteIdentifierSubTLV(uint32_t localId, uint32_t remoteId);
	virtual ~LinkLocalRemoteIdentifierSubTLV();
};

#endif /* LINKLOCALREMOTEIDENTIFIERSUBTLV_H_ */
