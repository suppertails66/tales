#ifndef BOXGRAPHICSCENEOBJECT_H
#define BOXGRAPHICSCENEOBJECT_H


#include "structs/GenericGraphicSceneObject.h"
#include "structs/Graphic.h"

namespace Tales {


class BoxGraphicSceneObject : public GenericGraphicSceneObject {
public:
  BoxGraphicSceneObject();
  
  BoxGraphicSceneObject(Color color__,
                        int lineWidth__,
                        int width__,
                        int height__,
                        int x__,
                        int y__,
                        bool visible__ = true);
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale = 1.00);
protected:
  
  Color color_;
  
  int lineWidth_;
  
  int width_;
  
  int height_;
  
};


};


#endif
