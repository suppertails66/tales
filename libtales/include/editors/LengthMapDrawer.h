#ifndef LENGTHMAPDRAWER_H
#define LENGTHMAPDRAWER_H


#include "structs/Graphic.h"
#include "gamedata/MetatileLengthMap.h"
#include "gamedata/MetatileWidthMap.h"
#include "gamedata/MetatileHeightMap.h"
#include "gamedata/MetatileBehavior.h"

namespace Tales {


class LengthMapDrawer {
public:
  static void drawWidthMap(Graphic& dst,
                           MetatileWidthMap widthMap,
                           MetatileBehavior behavior);
                           
  static void drawHeightMap(Graphic& dst,
                           MetatileHeightMap heightMap,
                           MetatileBehavior behavior);

  static void drawWidthMap(Graphic& dst,
                           MetatileWidthMap widthMap);
                           
  static void drawHeightMap(Graphic& dst,
                           MetatileHeightMap heightMap);
protected:
  enum DrawMode {
    drawWidth = 0,
    drawHeight
  };

  static void drawLengthMap(Graphic& dst,
                            MetatileWidthMap lengthMap,
                            DrawMode drawMode,
                            MetatileBehavior behavior);

  static void drawLengthMap(Graphic& dst,
                            MetatileWidthMap lengthMap,
                            DrawMode drawMode);
  
};


};


#endif
