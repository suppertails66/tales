#ifndef LEVELGRAPHICSCENELAYER_H
#define LEVELGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "editors/MetatileGraphicCollection.h"
#include "gamedata/LevelHeader.h"
#include "gamedata/MapLayout.h"
#include "structs/Graphic.h"
#include "structs/Box.h"

namespace Tales {


class LevelGraphicSceneLayer : public GraphicSceneLayer {
public:
  LevelGraphicSceneLayer(const LevelHeader& levelHeader__,
                         const MapLayout& mapLayout__);
                         
  virtual ~LevelGraphicSceneLayer();
  
  virtual void drawMetatiles(Graphic& dst,
                     Box srcbox,
                     double scale);
  
protected:
  
  virtual void drawMetatile(Graphic& drawSurf,
                            int metatileID,
                            int baseDrawX,
                            int baseDrawY) =0;

  const LevelHeader* levelHeader_;
  const MapLayout* mapLayout_;

};


};


#endif
