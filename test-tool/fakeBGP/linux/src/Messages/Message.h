/*
 * Message.h
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

class Message {
public:
	Message();
	virtual ~Message();

	virtual const void* getMessage() const = 0;
	virtual const unsigned getSize() const = 0;
};

#endif /* MESSAGE_H_ */
