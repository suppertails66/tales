#ifndef BITMAPGRAPHICSCENEOBJECT_H
#define BITMAPGRAPHICSCENEOBJECT_H


#include "structs/GenericGraphicSceneObject.h"
#include "structs/Graphic.h"

namespace Tales {


class BitmapGraphicSceneObject : public GenericGraphicSceneObject {
public:
  BitmapGraphicSceneObject();
  
  BitmapGraphicSceneObject(Graphic bitmap__,
                           int x__,
                           int y__,
                           bool visible__ = true);
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale = 1.00);
protected:

  Graphic bitmap_;
  
};


};


#endif
