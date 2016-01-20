#ifndef COLORPREVIEWGRAPHICSCENELAYER_H
#define COLORPREVIEWGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/Color.h"

namespace Tales {


class ColorPreviewGraphicSceneLayer : public GraphicSceneLayer {
public:
  ColorPreviewGraphicSceneLayer();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  void setColor(Color color__);
protected:
  Color color_;
  
};


};


#endif
