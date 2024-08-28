/*
 * AdjacencySID.cpp
 *
 */
#include "AdjacencySID.h"

#pragma pack(push,1)
struct DataStruct {
  uint8_t flags;
  uint8_t weight;
  uint16_t reserved;
  uint32_t index;
};
#pragma pack(pop)

#pragma pack(push,1)
struct DataStruct2 {
  uint8_t flags;
  uint8_t weight;
  uint16_t reserved;
  uint8_t label0; // MSB octect, first nibble sets to 0
  uint8_t label1;
  uint8_t label2;
};
#pragma pack(pop)

AdjacencySID::AdjacencySID(uint8_t flags, bool value, uint32_t sid) : LSTLV(1099)
{
  if (!value) {
    setLength(sizeof(DataStruct));
    DataStruct *ds = (DataStruct *)data.value;
    ds->flags = flags;
    ds->weight = 0;
    ds->reserved = 0;
    ds->index = htonl(sid);
  } else {
    setLength(sizeof(DataStruct2));
    DataStruct2 *ds = (DataStruct2 *)data.value;
    ds->flags = flags;
    ds->weight = 0;
    ds->reserved = 0;
    ds->label0 = ((sid & 0x00FF0000) >> 16);
    ds->label1 = ((sid & 0x0000FF00) >> 8);
    ds->label2 = ((sid & 0x000000FF) >> 0);
    ds->label0 &= 0x0F;
  }
}

AdjacencySID::~AdjacencySID()
{
}
