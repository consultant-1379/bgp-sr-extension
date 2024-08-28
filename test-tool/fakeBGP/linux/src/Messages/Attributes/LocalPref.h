/*
 * LocalPref.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef LOCALPREF_H_
#define LOCALPREF_H_

#include "../PathAttribute.h"

class LocalPref: public PathAttribute {
public:
	LocalPref(uint32_t localPref);
	virtual ~LocalPref();
};

#endif /* LOCALPREF_H_ */
