/*
 * OpenMessage.h
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */
 
#ifndef OPENMESSAGE_H_
#define OPENMESSAGE_H_

#include "Message.h"
#include <stdint.h>
#include <string>

class OpenMessage: public Message {
	typedef uint8_t StaticMessage[61];
	StaticMessage binary_message;
public:
	OpenMessage(const std::string& bgp_id);
	virtual ~OpenMessage();
	virtual const void* getMessage() const { return binary_message; }
	virtual const unsigned getSize() const { return sizeof(binary_message); }
};

#endif /* OPENMESSAGE_H_ */

