#ifndef LEVELBOUNDSGRAPHICSCENELAYER_H
#define LEVELBOUNDSGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "gamedata/LevelHeader.h"

namespace Tales {


class LevelBoundsGraphicSceneLayer : public GraphicSceneLayer {
public:
  LevelBoundsGraphicSceneLayer(LevelHeader& levelHeader__);
                               
  virtual ~LevelBoundsGraphicSceneLayer();
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
protected:

  const static int marginLeft_ = 6 * 8;
  const static int marginRight_ = marginLeft_ + (20 * 8);
  const static int marginTop_ = 5 * 8;
  const static int marginBottom_ = marginTop_ + (18 * 8);
  
  LevelHeader* levelHeader_;
  
};


};


#endif
