#ifndef ASSEMBLEDRAWMAPPING_H
#define ASSEMBLEDRAWMAPPING_H


#include "structs/TwoDByteArray.h"

namespace Tales {


class AssembledRawMapping {
public:
  AssembledRawMapping();
  
  AssembledRawMapping(const TwoDByteArray& data__,
                      int offsetX__,
                      int offsetY__);
  
  TwoDByteArray& data();
  int offsetX() const;
  int offsetY() const;
  
  void setData(const TwoDByteArray& data__);
  void setOffsetX(int offsetX__);
  void setOffsetY(int offsetY__);
protected:
  TwoDByteArray data_;
  int offsetX_;
  int offsetY_;
};


};


#endif
