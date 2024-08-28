/*
 * BGPLSAttribute.h
 *
 *  Created on: Mar 6, 2014
 *      Author: egboeny
 */

#ifndef BGPLSATTRIBUTE_H_
#define BGPLSATTRIBUTE_H_

#include "../PathAttribute.h"

class BGPLSAttribute: public BGPLSPathAttribute {
public:
	BGPLSAttribute(uint8_t type);
	virtual ~BGPLSAttribute();
};

#endif /* BGPLSATTRIBUTE_H_ */
