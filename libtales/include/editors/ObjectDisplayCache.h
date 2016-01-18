#ifndef OBJECTDISPLAYCACHE_H
#define OBJECTDISPLAYCACHE_H


#include "structs/Graphic.h"

namespace Tales {


class ObjectDisplayCache {
public:
  ObjectDisplayCache();
  
  ObjectDisplayCache(Graphic graphic__,
                     int offsetX__,
                     int offsetY__);
  
  Graphic& graphic();
  int offsetX() const;
  int offsetY() const;
  
  void setGraphic(Graphic graphic__);
  void setOffsetX(int offsetX__);
  void setOffsetY(int offsetY__);
  
protected:

  Graphic graphic_;
  int offsetX_;
  int offsetY_;
  
};


};


#endif
