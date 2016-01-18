#include "editors/LevelSolidityGraphicSceneLayer.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/MetatileStructure.h"
#include "editors/LengthMapDrawer.h"
#include <iostream>

namespace Tales {


LevelSolidityGraphicSceneLayer::LevelSolidityGraphicSceneLayer(
                             const LevelHeader& levelHeader__,
                             const MapLayout& mapLayout__,
                             EditableMetatileLengthMaps&
                               metatileLengthMaps__,
                             const EditableMetatileBehaviors&
                               metatileBehaviors__,
                             SolidityMode solidityMode__)
  : LevelGraphicSceneLayer(levelHeader__,
                           mapLayout__),
    metatileLengthMaps_(&metatileLengthMaps__),
    metatileBehaviors_(&metatileBehaviors__),
    solidityMode_(solidityMode__) {
  // Cache metatiles
  for (int i = 0; i < EditableMetatileBehaviors::numEntries; i++) {
    Graphic metatileGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    
    switch (solidityMode__) {
    case verticalMode:
      LengthMapDrawer::drawHeightMap(metatileGraphic,
                           metatileLengthMaps_->mapAt(
                             metatileBehaviors_->metatileBehavior(i)
                               .heightMapIndex()),
                           metatileBehaviors_->metatileBehavior(i));
      break;
    case horizontalMode:
      LengthMapDrawer::drawWidthMap(metatileGraphic,
                           metatileLengthMaps_->mapAt(
                             metatileBehaviors_->metatileBehavior(i)
                               .widthMapIndex()),
                           metatileBehaviors_->metatileBehavior(i));
      break;
    default:
      break;
    }
                             
    metatileCache_.push_back(metatileGraphic);
  }
}
                      
void LevelSolidityGraphicSceneLayer::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  drawMetatiles(dst,
                srcbox,
                scale);
}

void LevelSolidityGraphicSceneLayer::drawMetatile(
                          Graphic& drawSurf,
                          int metatileID,
                          int baseDrawX,
                          int baseDrawY) {
  drawSurf.blit(metatileCache_[(int)metatileID],
                Box(baseDrawX,
                    baseDrawY,
                    MetatileStructure::metatileWidth,
                    MetatileStructure::metatileHeight),
                Graphic::noTransUpdate);
}
  
Graphic& LevelSolidityGraphicSceneLayer
    ::metatileGraphic(int metatileID) {
  return metatileCache_[metatileID];
}


}
