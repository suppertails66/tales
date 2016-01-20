#include "editors/ObjectDisplayCache.h"

namespace Tales {


ObjectDisplayCache::ObjectDisplayCache()
  : offsetX_(0),
    offsetY_(0) { };

ObjectDisplayCache::ObjectDisplayCache(Graphic graphic__,
                   int offsetX__,
                   int offsetY__)
  : graphic_(graphic__),
    offsetX_(offsetX__),
    offsetY_(offsetY__) { };
                     
Graphic& ObjectDisplayCache::graphic() {
  return graphic_;
}

int ObjectDisplayCache::offsetX() const {
  return offsetX_;
}

int ObjectDisplayCache::offsetY() const {
  return offsetY_;
}

void ObjectDisplayCache::setGraphic(Graphic graphic__) {
  graphic_ = graphic__;
}

void ObjectDisplayCache::setOffsetX(int offsetX__) {
  offsetX_ = offsetX__;
}

void ObjectDisplayCache::setOffsetY(int offsetY__) {
  offsetY_ = offsetY__;
}


};
