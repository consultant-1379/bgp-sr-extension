/*
 * PrefixSID.h
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#ifndef PREFIXSID_H_
#define PREFIXSID_H_

#include "LSTLV.h"

class PrefixSID: public LSTLV {
public:
    PrefixSID(uint8_t flags, uint32_t SID);
    PrefixSID(uint8_t flags, uint32_t SID, bool add_reserved_bytes);
	virtual ~PrefixSID();
};

#endif /* PREFIXSID_H_ */
