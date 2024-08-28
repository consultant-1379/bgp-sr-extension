/*
 * IPReachability.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: enyedi
 */

#include "IPReachability.h"

#include <math.h>

IPReachability::IPReachability(const boost::asio::ip::address_v4& address, const uint8_t len) : LSTLV(265) {
    // former code:
    // setLength(1 + ceil(len/8));
    // was bogus for prefix length not exactly divisible by 4 due to the integer division
    // that cannot return any fractionals for ceil() to work properly
    // for example 25/8 = 3 -> ceil(3) = 3 -> setLength(4) instead of 5
    // now proper ceiling is obtained by explicit computation of quotient mod and adding up one if needed
    uint8_t m = len % 8;
    uint8_t length = len/8;
    if (m > 0) length = length + 1;
    setLength(length+1); // passed length is always increased by one

    *data.value = len;
    *((uint32_t*)(data.value+1)) = htonl(address.to_ulong());
}

IPReachability::~IPReachability() {
    // TODO Auto-generated destructor stub
}

