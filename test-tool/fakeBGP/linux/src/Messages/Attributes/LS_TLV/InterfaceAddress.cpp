/*
 * PrefixSID.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: egboeny
 */

#include "InterfaceAddress.h"

InterfaceAddress::InterfaceAddress(boost::asio::ip::address_v4 address) : LSTLV(259) {
    setLength(4);
    *((uint32_t*) data.value) = htonl(address.to_ulong());
}

InterfaceAddress::~InterfaceAddress() {
	// TODO Auto-generated destructor stub
}

