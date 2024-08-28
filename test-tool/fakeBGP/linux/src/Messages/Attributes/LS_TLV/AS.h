/*
 * NodeDescriptorSubTLV.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef AS_H_
#define AS_H_

#include "LSTLV.h"

class AS: public LSTLV {
public:
    AS(uint32_t as);
	virtual ~AS();
};

#endif /* AS_H_ */
