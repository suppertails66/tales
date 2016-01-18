#include "gamedata/AreaMapReference.h"

namespace Tales {


AreaMapReference::AreaMapReference()
  : areaNum_(0),
    mapNum_(0) { };

AreaMapReference::AreaMapReference(
                 int areaNum__,
                 int mapNum__)
  : areaNum_(areaNum__),
    mapNum_(mapNum__) { };

int AreaMapReference::areaNum() const {
  return areaNum_;
}

int AreaMapReference::mapNum() const {
  return mapNum_;
}

void AreaMapReference::setAreaNum(int areaNum__) {
  areaNum_ = areaNum__;
}

void AreaMapReference::setMapNum(int mapNum__) {
  mapNum_ = mapNum__;
}


};
