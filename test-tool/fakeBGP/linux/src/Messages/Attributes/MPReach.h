/*
 * MPReach.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef MPREACH_H_
#define MPREACH_H_

#include <boost/asio/ip/address_v4.hpp>

#include "../PathAttribute.h"
#include "LS_TLV/LSTLV.h"

class MPReach: public BGPLSPathAttribute {
public:
	MPReach(const uint16_t _afi, const uint8_t _safi, const uint8_t nhAddress[], const uint8_t nhAddressLen);
	MPReach(const uint16_t _afi, const uint8_t _safi, const boost::asio::ip::address_v4 address);
	virtual ~MPReach();
};

class LSMPReach: public MPReach {
public:
	LSMPReach(const uint8_t nhAddress[], const uint8_t nhAddressLen) : MPReach(16388, 71, nhAddress, nhAddressLen) { }
	LSMPReach(boost::asio::ip::address_v4& address) : MPReach(16388, 71, address) { }
	virtual ~LSMPReach() { }
};

#endif /* MPREACH_H_ */
