#ifndef LEVELEFFECTGRAPHICSCENELAYER_H
#define LEVELEFFECTGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/WrapScrollGraphic.h"
#include "editors/LevelGraphicSceneLayer.h"
#include "editors/VRAMCache.h"
#include "editors/MetatileGraphicCollection.h"
#include "gamedata/LevelHeader.h"
#include "gamedata/MapLayout.h"
#include "gamedata/MetatileStructureSet.h"
#include "gamedata/EditableMetatileBehaviors.h"

namespace Tales {


class LevelEffectGraphicSceneLayer : public LevelGraphicSceneLayer {
public:
  static void drawMetatileEffect(Graphic& metatileGraphic,
                                 int indexNum,
                                 const MetatileBehavior& behavior);
  
  Graphic& metatileGraphic(int metatileID);

  LevelEffectGraphicSceneLayer(const LevelHeader& levelHeader__,
                               const MapLayout& mapLayout__,
                               const EditableMetatileBehaviors&
                                 metatileBehaviors__);
                                 
  virtual ~LevelEffectGraphicSceneLayer() { };
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
protected:

  virtual void drawMetatile(Graphic& drawSurf,
                            int metatileID,
                            int baseDrawX,
                            int baseDrawY);
  
  const EditableMetatileBehaviors* metatileBehaviors_;
  
  MetatileGraphicCollection metatileCache_;
  
};


};


#endif
