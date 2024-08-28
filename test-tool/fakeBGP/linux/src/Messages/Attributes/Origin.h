/*
 * Origin.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef ORIGIN_H_
#define ORIGIN_H_

#include "../PathAttribute.h"

class Origin: public PathAttribute {
public:
	enum OriginType {IGP = 0, EGP = 1, Incomplete = 2};

	Origin(OriginType type);
	virtual ~Origin();
};

#endif /* ORIGIN_H_ */
