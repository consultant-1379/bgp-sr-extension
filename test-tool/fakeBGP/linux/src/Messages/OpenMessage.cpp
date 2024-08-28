/*
 * OpenMessage.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#include "OpenMessage.h"
#include <string.h>
#include <string>
#include <iostream>

OpenMessage::OpenMessage(const std::string& bgp_id) {
uint8_t bgp_id_buffer[4] = { 0, 0, 0, 0 };
std::size_t prev = -1;
int index = 0;
for ( std::size_t i = bgp_id.find("."); i != std::string::npos; i = bgp_id.find(".",i+1) ) 
{
   std::cout << index << " " << bgp_id.substr(prev+1, i-prev-1) << std::endl;
   bgp_id_buffer[index++] = std::stoi(bgp_id.substr(prev+1, i-prev-1));
   prev = i;
}
bgp_id_buffer[index++] = std::stoi(bgp_id.substr(prev+1, bgp_id.size()-1));

for ( int k = 0; bgp_id_buffer[k]; ++k ) 
{
  printf("%d", bgp_id_buffer[k]);
}
StaticMessage binary_message =  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //Init
			 	 	 	 	     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			 	 	 	 	 	 //55 byte |open | BGPv4| AS: 6666 | Hold Time:180
			 	 	 	 	 	 0x00, 0x3d, 0x01, 0x04, 0x1a, 0x0a, 0x00, 0xb4,
			 	 	 	 	 	 //id:172.31.32.16 |opt:32B|
			 	 	 	 	 	 bgp_id_buffer[0], bgp_id_buffer[1], bgp_id_buffer[2], bgp_id_buffer[3], 0x20,
			 	 	 	 	     //Cap=2|len=6|type=4BAS|len=4B|AS=6666
			 	 	 	 	 	 0x02, 0x06,     0x41,     0x04, 0x00, 0x00, 0x1a, 0x0a,
			 	 	 	 	 	 //Cap=2|len=6|MultExt|len=4B|AFI=1(IPv4)|reserved| SAFI=1(unicast)
			 	 	 	 	 	 0x02, 0x06,     0x01,  0x04, 0x00, 0x01,  0x00,    0x01,
			 	 	 	 	 	 //Cap=2|len=6|MultExt|len=4B|AFI=1(IPv6)|reserved| SAFI=1(unicast)
			 	 	 	 	 	 0x02, 0x06,     0x01,  0x04, 0x00, 0x02,  0x00,    0x01,
			 	 	 	 	 	 //Cap=2|len=6|MultExt|len=4B|AFI=16388(BGP-LS)|reserved| SAFI=71(non-VPN)
			 	 	 	 	 	 0x02, 0x06,     0x01,  0x04,    0x40, 0x04,      0x00,    0x47};

memcpy(this->binary_message, binary_message, sizeof(StaticMessage));
}

OpenMessage::~OpenMessage() {
	// TODO Auto-generated destructor stub
}

