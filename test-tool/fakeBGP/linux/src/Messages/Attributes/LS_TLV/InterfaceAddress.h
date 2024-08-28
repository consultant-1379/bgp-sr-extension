/*
 * InterfaceAddress.h
 *
 *  Created on: Oct 28, 2014
 *      Author: egboeny
 */

#ifndef INTERFACEADDRESS_H_
#define INTERFACEADDRESS_H_

#include "LSTLV.h"

#include <boost/asio/ip/address_v4.hpp>

class InterfaceAddress : public LSTLV {
public:
    InterfaceAddress(boost::asio::ip::address_v4 address);
	virtual ~InterfaceAddress();
};

#endif /* INTERFACEADDRESS_H_ */
