#ifndef MAPPINGTOGRAPHIC_H
#define MAPPINGTOGRAPHIC_H


#include "gamedata/MappingToGraphicEntry.h"

namespace Tales {


class MappingToGraphic {
public:
  
  static MappingToGraphicEntry mappingToGraphic(int mappingIndex);
  
protected:
  
  const static int numMappings_ = 0x1F9;
  
  const static MappingToGraphicEntry mappingToGraphic_[numMappings_];
  
};


};


#endif
