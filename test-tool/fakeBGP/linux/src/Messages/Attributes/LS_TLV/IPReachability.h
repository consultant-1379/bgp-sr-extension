/*
 * IPReachability.h
 *
 *  Created on: Oct 25, 2014
 *      Author: enyedi
 */

#ifndef IPREACHABILITY_H_
#define IPREACHABILITY_H_

#include <boost/asio/ip/address_v4.hpp>

#include "LSTLV.h"

class IPReachability : public LSTLV {
public:
    IPReachability(const boost::asio::ip::address_v4& address, const uint8_t len);
    virtual ~IPReachability();
};

#endif /* IPREACHABILITY_H_ */
