#ifndef LEVELMETADATAENTRY_H
#define LEVELMETADATAENTRY_H


#include "structs/Tbyte.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


class LevelMetadataEntry {
public:
  LevelMetadataEntry();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
protected:
  
};


};


#endif
