/*
 * NodeNLRI.h
 *
 *  Created on: Feb 11, 2014
 *      Author: egboeny
 */

#ifndef NODENLRI_H_
#define NODENLRI_H_

#include "LSTLV.h"

class LSNLRI : public LSTLV {
protected:

#pragma pack(push, 1)
	struct NLRINodeStruct {
		uint8_t protocolID;
		uint64_t identifier;
	} *NLRIData;
#pragma pack(pop)

protected:
	LSNLRI(uint8_t type, uint8_t protoID, uint64_t identifier);

public:
	virtual ~LSNLRI();
};

class NodeNLRI : public LSNLRI {
public:
	NodeNLRI(uint8_t protoID, uint64_t identifier) : LSNLRI(1, protoID, identifier) {}
	virtual ~NodeNLRI() {}
};

class LinkNLRI : public LSNLRI {
public:
	LinkNLRI(uint8_t protoID, uint64_t identifier) : LSNLRI(2, protoID, identifier) {}
	virtual ~LinkNLRI() {}
};

class Prefixv4NLRI : public LSNLRI {
public:
    Prefixv4NLRI(uint8_t protoID, uint64_t identifier) : LSNLRI(3, protoID, identifier) {}
    virtual ~Prefixv4NLRI() {}
};

#endif /* NODENLRI_H_ */
