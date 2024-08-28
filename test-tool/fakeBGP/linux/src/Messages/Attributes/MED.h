/*
 * MED.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef MED_H_
#define MED_H_

#include "../PathAttribute.h"

class MED: public PathAttribute {
public:
	MED(uint32_t medVal);
	virtual ~MED();
};

#endif /* MED_H_ */
