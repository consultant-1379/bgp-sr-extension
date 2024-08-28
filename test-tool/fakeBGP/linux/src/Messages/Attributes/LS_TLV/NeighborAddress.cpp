/*
 * PrefixSID.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#include "NeighborAddress.h"

NeighborAddress::NeighborAddress(boost::asio::ip::address_v4 address) : LSTLV(260) {
    setLength(4);
    *((uint32_t*) data.value) = htonl(address.to_ulong());
}

NeighborAddress::~NeighborAddress() {
	// TODO Auto-generated destructor stub
}

