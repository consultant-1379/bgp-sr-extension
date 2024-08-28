/*
 * ExtendedCommunity.h
 *
 *  Created on: Feb 7, 2014
 *      Author: egboeny
 */

#ifndef EXTENDEDCOMMUNITY_H_
#define EXTENDEDCOMMUNITY_H_

#include "../PathAttribute.h"

class ExtendedCommunity : PathAttribute {


public:

#pragma pack(push,1)	//Do not use padding!
	struct VRD {
		uint16_t type;
		uint16_t adminFieldT0[];		//Pointer for Type 0
		uint32_t adminFieldT12[];		//Pointer for Type 1 + 2
		uint16_t _field1;				//Data field T0 admin or first word of T1+T2 admin
		uint32_t assignedFieldT0[]; 	//Pointer for Type 0
		uint16_t _field2;				//Data field T0 assigned first word or T1+T2 admin second word
		uint32_t assignedFieldT12[];	//Pointer for Type 1 + 2
		uint32_t _field3;				//Last DWord data field
	};
#pragma pack(pop)

	ExtendedCommunity(const VRD& vrd);
	virtual ~ExtendedCommunity();
};

#endif /* EXTENDEDCOMMUNITY_H_ */
