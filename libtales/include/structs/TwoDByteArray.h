#ifndef TWODBYTEARRAY_H
#define TWODBYTEARRAY_H


#include "structs/TwoDArray.h"
#include "structs/Tbyte.h"

namespace Tales {


class TwoDByteArray : public TwoDArray<Tbyte> {
public:
  TwoDByteArray();
  TwoDByteArray(int w__, int h__);
  
  void clear();
protected:
  
};


};


#endif
