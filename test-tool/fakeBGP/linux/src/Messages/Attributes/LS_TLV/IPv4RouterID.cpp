/*
 * IPv4RouterID.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: egboeny
 */

#include "IPv4RouterID.h"

IPv4RouterID::IPv4RouterID(uint32_t routerID) : LSTLV(1028) {
	setLength(4);
	*((uint32_t*) data.value) = htonl(routerID);
}

IPv4RouterID::IPv4RouterID(boost::asio::ip::address_v4& address) : LSTLV(1028) {
    setLength(4);

    *((uint32_t*) data.value) = htonl(address.to_ulong());
}

IPv4RouterID::~IPv4RouterID() {
	// TODO Auto-generated destructor stub
}

