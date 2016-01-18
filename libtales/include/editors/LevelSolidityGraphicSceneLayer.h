#ifndef LEVELSOLIDITYGRAPHICSCENELAYER_H
#define LEVELSOLIDITYGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/WrapScrollGraphic.h"
#include "editors/LevelGraphicSceneLayer.h"
#include "editors/VRAMCache.h"
#include "editors/MetatileGraphicCollection.h"
#include "gamedata/LevelHeader.h"
#include "gamedata/MapLayout.h"
#include "gamedata/MetatileStructureSet.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/EditableMetatileHeightMaps.h"

namespace Tales {


class LevelSolidityGraphicSceneLayer : public LevelGraphicSceneLayer {
public:
  enum SolidityMode {
    verticalMode = 0,
    horizontalMode
  };

  Graphic& metatileGraphic(int metatileID);

  LevelSolidityGraphicSceneLayer(const LevelHeader& levelHeader__,
                               const MapLayout& mapLayout__,
                               EditableMetatileLengthMaps&
                                 metatileLengthMaps__,
                               const EditableMetatileBehaviors&
                                 metatileBehaviors__,
                               SolidityMode solidityMode__);
                                 
  virtual ~LevelSolidityGraphicSceneLayer() { };
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
protected:

  virtual void drawMetatile(Graphic& drawSurf,
                            int metatileID,
                            int baseDrawX,
                            int baseDrawY);
  
  EditableMetatileLengthMaps* metatileLengthMaps_;
  const EditableMetatileBehaviors* metatileBehaviors_;
  
  MetatileGraphicCollection metatileCache_;
  
  SolidityMode solidityMode_;
  
};


};


#endif
