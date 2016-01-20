#ifndef GRAPHICTOMAPPINGENTRY_H
#define GRAPHICTOMAPPINGENTRY_H


#include "structs/GraphicIdentifier.h"
#include <string>

namespace Tales {


class GraphicToMappingEntry {
public:
  GraphicToMappingEntry(int mappingIndex__,
                        int tileOffset__,
                        std::string name__);
  
  int mappingIndex;
  int tileOffset;
  std::string name;
protected:
  
};


};


#endif
