/*
 * SIDLabelBinding.h
 *
 *  Created on: Mar 6, 2014
 *      Author: egboeny
 */

#ifndef SIDLABELBINDING_H_
#define SIDLABELBINDING_H_

#include "LSTLV.h"

class SIDLabelBinding: public LSTLV {
#pragma pack(push,1)	//Do not use padding!
	struct SLBT {
		uint8_t	flags;
		uint8_t weight;
		uint16_t range;
		uint8_t prefixLength;

	};
#pragma pack(pop)

public:
	SIDLabelBinding();
	virtual ~SIDLabelBinding();
};

#endif /* SIDLABELBINDING_H_ */
