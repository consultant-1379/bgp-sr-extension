/*
 * AdjacencySID.h
 */
#ifndef ADJACENCYSID_H_
#define ADJACENCYSID_H_

#include "LSTLV.h"

class AdjacencySID: public LSTLV {
public:
  AdjacencySID(uint8_t flags, bool value, uint32_t sid);
  virtual ~AdjacencySID();
};
#endif /* ADJACENCYSID_H_ */
