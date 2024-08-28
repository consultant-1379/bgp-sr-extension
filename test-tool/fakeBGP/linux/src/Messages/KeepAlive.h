/*
 * KeepAlive.h
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#ifndef KEEPALIVE_H_
#define KEEPALIVE_H_

#include "Message.h"
#include <stdint.h>

class KeepAlive : public Message {
	typedef uint8_t StaticMessage[19];

	StaticMessage binary_message;

public:
	KeepAlive();
	virtual ~KeepAlive();
	virtual const void* getMessage() const { return binary_message; }
	virtual const unsigned getSize() const { return sizeof(binary_message); }
};

/*const uint8_t KeepAlive::binary_message[19] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //Init
		 	 	 	 	 	 	 	 	 	   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,*/
		 	 	 	 	 	 	 	 	 	   //len=19B | type=4=KeepAlive
//		 	 	 	 	 	 	 	 	 	   0x00, 0x13, 04 };

#endif /* KEEPALIVE_H_ */
