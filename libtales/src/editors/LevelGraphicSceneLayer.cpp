#include "editors/LevelGraphicSceneLayer.h"
#include "gamedata/MetatileStructure.h"

namespace Tales {


LevelGraphicSceneLayer::LevelGraphicSceneLayer(
                       const LevelHeader& levelHeader__,
                       const MapLayout& mapLayout__)
  : GraphicSceneLayer(),
    levelHeader_(&levelHeader__),
    mapLayout_(&mapLayout__) { };
    
LevelGraphicSceneLayer::~LevelGraphicSceneLayer() { };
  
void LevelGraphicSceneLayer::drawMetatiles(Graphic& dst,
                     Box srcbox,
                     double scale) {
  // Regenerate cache if size has changed
/*  if ((srcbox.w() != renderCache_.w())
      || (srcbox.h() != renderCache_.h())) {
    renderCache_ = Graphic(srcbox.w(), srcbox.h());
  } */
  
//  renderCache_.clear();
  
  Graphic& drawSurf = dst;
                    
  // Convert source X and Y to base metatile position
  int metatileBaseX = srcbox.x() / MetatileStructure::metatileWidth
                     * MetatileStructure::metatileWidth
                       / MetatileStructure::metatileWidth;
  int metatileBaseY = srcbox.y() / MetatileStructure::metatileHeight
                     * MetatileStructure::metatileHeight
                       / MetatileStructure::metatileHeight;
                       
  // Compute width and height, adding extra metatiles so the entire
  // visible area is covered
  int metatileEndX = metatileBaseX
          + (srcbox.w() / MetatileStructure::metatileWidth
               * MetatileStructure::metatileWidth
                  / MetatileStructure::metatileWidth)
          + 2;
  int metatileEndY = metatileBaseY
          + (srcbox.h() / MetatileStructure::metatileHeight
               * MetatileStructure::metatileHeight
                  / MetatileStructure::metatileHeight)
          + 2;
  
  for (int j = metatileBaseY; j < metatileEndY; j++) {
    for (int i = metatileBaseX; i < metatileEndX; i++) {
//      std::cout << i << " " << j << std::endl;
      int sourceTileIndex = (j * levelHeader_->width()) + i;
      // If metatile does not exist (outside of level bounds), draw nothing
      if ((i < 0) || (j < 0)
          || (i >= levelHeader_->width())
          // check if metatile is below level
          || (sourceTileIndex >= MapLayout::dataSize)) {
        continue;
      }
      
      int baseDrawX = (i * MetatileStructure::metatileWidth) - srcbox.x();
      int baseDrawY = (j * MetatileStructure::metatileHeight) - srcbox.y();
      
      Tbyte metatileID = mapLayout_->getMetatile(sourceTileIndex);
      
      this->drawMetatile(
                   drawSurf,
                   (int)metatileID,
                   baseDrawX,
                   baseDrawY);
      
/*      MetatileStructure metatileStructure
        = metatileStructureSet_->metatileMapping((int)metatileID);
      
//      std::cout << (int)metatileID << std::endl;
      
      drawMetatileWithPriority(drawSurf,
                               metatileStructure,
                               baseDrawX,
                               baseDrawY); */
    }
  }
  
//  drawSurf.regenerateTransparencyModel();
  
/*  if (scale == 1.00) {
    dst.blit(drawSurf,
             Box(0, 0, 0, 0),
             Graphic::noTransUpdate);
  }
  else {
    if ((scaleCache_.w() != drawSurf.w() * scale)
        || (scaleCache_.h() != drawSurf.h() * scale)) {
      scaleCache_ = Graphic(drawSurf.w() * scale,
                            drawSurf.h() * scale);
    }
    
    drawSurf.scale(scaleCache_,
             Box(0, 0,
                 drawSurf.w() * scale,
                 drawSurf.h() * scale),
             Graphic::transUpdate);
    
    dst.blit(scaleCache_,
             Box(0, 0, 0, 0),
             Graphic::noTransUpdate); 
  } */
}


}; 
