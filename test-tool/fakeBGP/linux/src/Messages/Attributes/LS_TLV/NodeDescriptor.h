/*
 * LocalNodeDescriptor.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef LOCALNODEDESCRIPTOR_H_
#define LOCALNODEDESCRIPTOR_H_

#include "LSTLV.h"

class LocalNodeDescriptor: public LSTLV {
public:
	LocalNodeDescriptor();
	virtual ~LocalNodeDescriptor();
};

class RemoteNodeDescriptor: public LSTLV {
public:
	RemoteNodeDescriptor();
	virtual ~RemoteNodeDescriptor();
};

#endif /* LOCALNODEDESCRIPTOR_H_ */
