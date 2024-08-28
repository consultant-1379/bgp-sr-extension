/*
 * NextHop.h
 *
 *  Created on: May 5, 2014
 *      Author: egboeny
 */

#ifndef NEXTHOP_H_
#define NEXTHOP_H_

#include "../PathAttribute.h"

class NextHop: public PathAttribute {
public:
	NextHop(uint32_t nextHop);
	virtual ~NextHop();
};

#endif /* NEXTHOP_H_ */
