/*
 * NeighborAddress.h
 *
 *  Created on: Oct 28, 2014
 *      Author: egboeny
 */

#ifndef NEIGHBORADDRESS_H_
#define NEIGHBORADDRESS_H_

#include "LSTLV.h"

#include <boost/asio/ip/address_v4.hpp>

class NeighborAddress : public LSTLV {
public:
    NeighborAddress(boost::asio::ip::address_v4 address);
	virtual ~NeighborAddress();
};

#endif /* NEIGHBORADDRESS_H_ */
