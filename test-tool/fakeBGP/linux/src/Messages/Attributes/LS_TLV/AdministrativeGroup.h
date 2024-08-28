/*
 * AdiministrativeGroup.h
 *
 *  Created on: Dec 19, 2017
 *      Author: ericsson
 */

#ifndef ADMINISTRATIVEGROUP_H_
#define ADMINISTRATIVEGROUP_H_

#include "LSTLV.h"

class AdministrativeGroup: public LSTLV {
public:
    AdministrativeGroup(uint32_t administrativeGroup);
	virtual ~AdministrativeGroup();
};

#endif /* ADMINISTRATIVEGROUP_H_ */
