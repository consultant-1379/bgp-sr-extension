/*
 * ASPath.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef ASPATH_H_
#define ASPATH_H_

#include "../PathAttribute.h"

class ASPath: public PathAttribute {
public:
	//Constructor for empty path - currently only empty is supported.
	ASPath();
	virtual ~ASPath();
};

#endif /* ASPATH_H_ */
