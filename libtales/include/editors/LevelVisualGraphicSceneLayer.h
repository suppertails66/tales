#ifndef LEVELVISUALGRAPHICSCENELAYER_H
#define LEVELVISUALGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/WrapScrollGraphic.h"
#include "editors/LevelGraphicSceneLayer.h"
#include "editors/VRAMCache.h"
#include "editors/MetatileGraphicCollection.h"
#include "gamedata/LevelHeader.h"
#include "gamedata/MapLayout.h"
#include "gamedata/MetatileStructureSet.h"
#include <vector>

namespace Tales {


class LevelVisualGraphicSceneLayer : public LevelGraphicSceneLayer {
public:
  enum PriorityLevel {
    priorityBG,
    priorityFG
  };
  
  static void drawMetatileVisual(Graphic& metatileGraphic,
                                 const VRAMCache& src,
                                 MetatileStructure metatileStructure);
                                 
  static void drawMetatilePriorityVisual(Graphic& metatileGraphic,
                                 const VRAMCache& src,
                                 MetatileStructure metatileStructure,
                                 PriorityLevel tilePriority);
  
  Graphic& metatileGraphic(int metatileID);

  LevelVisualGraphicSceneLayer(const VRAMCache& vramCache__,
                               const LevelHeader& levelHeader__,
                               const MapLayout& mapLayout__,
                               const MetatileStructureSet&
                                 metatileStructureSet__,
                               PriorityLevel priority__);
                                 
  virtual ~LevelVisualGraphicSceneLayer() { };
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
                        
/*  virtual void render(WrapScrollGraphic& dst,
                      Box dstbox,
                      Box srcbox); */
protected:

  virtual void drawMetatile(Graphic& drawSurf,
                            int metatileID,
                            int baseDrawX,
                            int baseDrawY);

  static void drawMetatileWithPriority(Graphic& dst,
                                const VRAMCache& vramCache_,
                                MetatileStructure metatileStructure,
                                int baseDrawX,
                                int baseDrawY,
                                PriorityLevel tilePriority);
                                

  static void drawTileIfSamePriority(Graphic& dst,
                              const VRAMCache& vramCache_,
                              TileReference tileRef,
                              int drawX,
                              int drawY,
                              PriorityLevel tilePriority);
                                

  static void drawTile(Graphic& dst,
                       const VRAMCache& src,
                       TileReference tileRef,
                       int drawX,
                       int drawY);

  const static int mapTileOffset_ = 256;

  const VRAMCache* vramCache_;
  
  const MetatileStructureSet* metatileStructureSet_;
  
  PriorityLevel priority_;
  
//  Graphic renderCache_;
  
  MetatileGraphicCollection metatileCache_;
//  Graphic scaleCache_;
  
};


};


#endif
