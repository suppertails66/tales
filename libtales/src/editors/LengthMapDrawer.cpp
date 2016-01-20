#include "editors/LengthMapDrawer.h"
#include "gamedata/MetatileStructure.h"

namespace Tales {


void LengthMapDrawer::drawWidthMap(Graphic& dst,
                         MetatileWidthMap widthMap,
                         MetatileBehavior behavior) {
  drawLengthMap(dst, widthMap, DrawMode::drawWidth, behavior);
}
                           
void LengthMapDrawer::drawHeightMap(Graphic& dst,
                          MetatileHeightMap heightMap,
                          MetatileBehavior behavior) {
  drawLengthMap(dst, heightMap, DrawMode::drawHeight, behavior);
}

void LengthMapDrawer::drawWidthMap(Graphic& dst,
                         MetatileWidthMap widthMap) {
  drawLengthMap(dst, widthMap, DrawMode::drawWidth);
}
                         
void LengthMapDrawer::drawHeightMap(Graphic& dst,
                         MetatileHeightMap heightMap) {
  drawLengthMap(dst, heightMap, DrawMode::drawHeight);
}

void LengthMapDrawer::drawLengthMap(Graphic& dst,
                          MetatileWidthMap lengthMap,
                          DrawMode drawMode,
                          MetatileBehavior behavior) {
  dst = Graphic(MetatileStructure::metatileWidth,
                MetatileStructure::metatileHeight);
  dst.clear(Color(0xFF, 0xFF, 0xFF, Color::fullAlphaOpacity));
  
  for (int i = 0; i < MetatileLengthMap::numElements; i++) {
    LengthMapValue length = lengthMap.lengthAt(i);
    
    // Skip 0 values
    if (length.magnitude() == 0) {
      continue;
    }
    
    // Default color: black
    Color color(0x00, 0x00, 0x00, Color::fullAlphaOpacity);
    
    // If max regular magnitude is exceeded, color red
    if (length.magnitude() > LengthMapValue::maxRegularMagnitude) {
      color = Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity);
    }
    
    // If not fully solid, reduce color intensity
    if (!(behavior.fullySolid())) {
      // Double intensity reduction if not also solid on top
      if (behavior.solidOnTop()) {
        color = Color((color.r() == 0) ? 0x80
                        : (color.r() * 2),
                      0x80,
                      0x80,
                      Color::fullAlphaOpacity);
      }
      else {
        color = Color((color.r() == 0) ? 0xC0
                        : (color.r() * 4),
                      0xC0,
                      0xC0,
                      Color::fullAlphaOpacity);
      }
    }
    
    switch (drawMode) {
    case drawWidth:
      // note that width maps use reverse semantics from height --
      // for width, "backwards" growth is toward negative direction
      if (length.direction() == LengthMapValue::backward) {
        dst.drawLine(0,
                     i,
                     0 + length.magnitude(),
                     i,
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      else {
        dst.drawLine(MetatileStructure::metatileWidth,
                     i,
                     MetatileStructure::metatileWidth
                       - length.magnitude(),
                     i,
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      break;
    case drawHeight:
      if (length.direction() == LengthMapValue::backward) {
        dst.drawLine(i,
                     MetatileStructure::metatileHeight,
                     i,
                     MetatileStructure::metatileHeight
                       - length.magnitude(),
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      else {
        dst.drawLine(i,
                     0,
                     i,
                     0 + length.magnitude(),
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      break;
    default:
      break;
    }
  }
  
  dst.regenerateTransparencyModel();
}

void LengthMapDrawer::drawLengthMap(Graphic& dst,
                          MetatileWidthMap lengthMap,
                          DrawMode drawMode) {
//  dst = Graphic(MetatileStructure::metatileWidth,
//                MetatileStructure::metatileHeight);
  dst.clear(Color(0xFF, 0xFF, 0xFF, Color::fullAlphaOpacity));
  
  for (int i = 0; i < MetatileLengthMap::numElements; i++) {
    LengthMapValue length = lengthMap.lengthAt(i);
    
    // Skip 0 values
    if (length.magnitude() == 0) {
      continue;
    }
    
    // Default color: black
    Color color(0x00, 0x00, 0x00, Color::fullAlphaOpacity);
    
    // If max regular magnitude is exceeded, color red
    if (length.magnitude() > LengthMapValue::maxRegularMagnitude) {
      color = Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity);
    }
    
    switch (drawMode) {
    case drawWidth:
      // note that width maps use reverse semantics from height --
      // for width, "backwards" growth is toward negative direction
      if (length.direction() == LengthMapValue::backward) {
        dst.drawLine(0,
                     i,
                     0 + length.magnitude(),
                     i,
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      else {
        dst.drawLine(MetatileStructure::metatileWidth,
                     i,
                     MetatileStructure::metatileWidth
                       - length.magnitude(),
                     i,
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      break;
    case drawHeight:
      if (length.direction() == LengthMapValue::backward) {
        dst.drawLine(i,
                     MetatileStructure::metatileHeight,
                     i,
                     MetatileStructure::metatileHeight
                       - length.magnitude(),
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      else {
        dst.drawLine(i,
                     0,
                     i,
                     0 + length.magnitude() - 1,
                     color,
                     1,
                     Graphic::noTransUpdate);
      }
      break;
    default:
      break;
    }
  }
  
  dst.regenerateTransparencyModel();
}


};
