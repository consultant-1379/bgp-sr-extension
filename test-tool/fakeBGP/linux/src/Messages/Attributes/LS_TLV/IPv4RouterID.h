/*
 * IPv4RouterID.h
 *
 *  Created on: Mar 13, 2014
 *      Author: egboeny
 */

#ifndef IPV4ROUTERID_H_
#define IPV4ROUTERID_H_

#include <boost/asio/ip/address_v4.hpp>

#include "LSTLV.h"

class IPv4RouterID: public LSTLV {
public:
	IPv4RouterID(uint32_t routerID);
	IPv4RouterID(boost::asio::ip::address_v4& address);
	virtual ~IPv4RouterID();
};

#endif /* IPV4ROUTERID_H_ */
