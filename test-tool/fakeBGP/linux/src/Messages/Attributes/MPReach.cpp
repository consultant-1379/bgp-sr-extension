/*
 * MPReach.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#include "MPReach.h"

MPReach::MPReach(const uint16_t _afi, const uint8_t _safi, const uint8_t _nhAddr[], const uint8_t _nhAddrLen) {
	uint16_t* afi;
	uint8_t* safi;
	uint8_t* nhAddr;

	binary_message.flags = ATTR_OPTIONAL | ATTR_EXTENDEDLEN;
	binary_message.type = 14;	//MP_REACH_NLRI
	binary_message.setLength(9+_nhAddrLen); //At the begining: flag+type+extLen+afi(2B)+safi+addr size+address+1B reserved

	afi = (uint16_t*)binary_message.getValStart();
	safi = (uint8_t*)(afi+1);
	nhAddr = safi+1;

	//AFI + SAFI
	*afi = htons(_afi);
	*safi = _safi;

	//Copy address
	*nhAddr = _nhAddrLen;	//Length
	nhAddr++;
	memcpy(nhAddr, _nhAddr, _nhAddrLen);
	nhAddr += _nhAddrLen;
	*nhAddr = 0;		//This is the reserved byte
}

MPReach::MPReach(const uint16_t _afi, const uint8_t _safi, const boost::asio::ip::address_v4 address) {
    uint16_t* afi;
    uint8_t* safi;
    uint8_t* nhAddr;

    binary_message.flags = ATTR_OPTIONAL | ATTR_EXTENDEDLEN;
    binary_message.type = 14;   //MP_REACH_NLRI
    binary_message.setLength(13); //At the begining: flag+type+extLen+afi(2B)+safi+addr size+address+1B reserved

    afi = (uint16_t*)binary_message.getValStart();
    safi = (uint8_t*)(afi+1);
    nhAddr = safi+1;

    //AFI + SAFI
    *afi = htons(_afi);
    *safi = _safi;

    //Copy address
    *nhAddr = 4;   //Length
    nhAddr++;
    *((uint32_t*)nhAddr) = htonl(address.to_ulong());
    nhAddr += 4;
    *nhAddr = 0;        //This is the reserved byte
}

MPReach::~MPReach() {
	// TODO Auto-generated destructor stub
}

