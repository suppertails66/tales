#include "editors/LevelEffectGraphicSceneLayer.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/MetatileStructure.h"
#include <iostream>

namespace Tales {


LevelEffectGraphicSceneLayer::LevelEffectGraphicSceneLayer(
                             const LevelHeader& levelHeader__,
                             const MapLayout& mapLayout__,
                             const EditableMetatileBehaviors&
                               metatileBehaviors__)
  : LevelGraphicSceneLayer(levelHeader__,
                           mapLayout__),
    metatileBehaviors_(&metatileBehaviors__) {
  // Cache metatiles
  for (int i = 0; i < EditableMetatileBehaviors::numEntries; i++) {
    Graphic metatileGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    
//    MetatileBehavior behavior = metatileBehaviors_->metatileBehavior(i);
    
    drawMetatileEffect(metatileGraphic,
                       i,
                       metatileBehaviors_->metatileBehavior(i));
                             
    metatileCache_.push_back(metatileGraphic);
  }
}
                      
void LevelEffectGraphicSceneLayer::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  drawMetatiles(dst,
                srcbox,
                scale);
}

void LevelEffectGraphicSceneLayer::drawMetatile(
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

void LevelEffectGraphicSceneLayer::drawMetatileEffect(
                               Graphic& metatileGraphic,
                               int indexNum,
                               const MetatileBehavior& behavior) {
  metatileGraphic.clear(Color(0xFF, 0xFF, 0xFF, Color::fullAlphaOpacity));
    
  switch (behavior.metatileType()) {
  case MetatileTypes::nullType:
    metatileGraphic.clear(
      Color(0xFF, 0xFF, 0xFF, Color::fullAlphaOpacity));
    break;
  case MetatileTypes::climbable1:
  case MetatileTypes::climbable2:
    metatileGraphic.clear(
      Color(0x88, 0x88, 0x88, Color::fullAlphaOpacity));
    break;
//  case MetatileTypes::climbable2:
//    metatileGraphic.clear(
//      Color(0xCC, 0xCC, 0xCC, Color::fullAlphaOpacity));
//    break;
  case MetatileTypes::nonclimbable:
    metatileGraphic.clear(
        Color(0x44, 0x44, 0x44, Color::fullAlphaOpacity));
//      Color(0x22, 0x22, 0x22, Color::fullAlphaOpacity));
    break;
  case MetatileTypes::damaging:
    metatileGraphic.clear(
      Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity));
    switch (indexNum) {
    case 0x68:
    case 0x69:
      // up
      for (int i = 0; i < 16; i += 8) {
        metatileGraphic.drawLine(i, 15,
                                 i + 4, 2,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
        metatileGraphic.drawLine(i + 4, 2,
                                 i + 8, 15,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
      }
      break;
    case 0x6A:
    case 0x6B:
      // down
      for (int i = 0; i < 16; i += 8) {
        metatileGraphic.drawLine(i, 0,
                                 i + 4, 13,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
        metatileGraphic.drawLine(i + 4, 13,
                                 i + 8, 0,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
      }
      break;
    case 0x6C:
    case 0x6D:
      // right
      for (int i = 0; i < 16; i += 8) {
        metatileGraphic.drawLine(0, i,
                                 13, i + 4,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
        metatileGraphic.drawLine(13, i + 4,
                                 0, i + 8,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
      }
      break;
    case 0x6E:
    case 0x6F:
      // left
      for (int i = 0; i < 16; i += 8) {
        metatileGraphic.drawLine(15, i,
                                 1, i + 4,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
        metatileGraphic.drawLine(2, i + 4,
                                 15, i + 8,
                                 Color(0xFF, 0xFF, 0x00, 
                                       Color::fullAlphaOpacity),
                                 1);
      }
      break;
    case 0x70:
    case 0x71:
      // all
    default:
      break;
    }
    break;
  case MetatileTypes::instadeath:
    metatileGraphic.drawLine(0, 0,
                             15, 15,
                             Color(0xFF, 0x00, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
    metatileGraphic.drawLine(15, 0,
                             0, 15,
                             Color(0xFF, 0x00, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
//      metatileGraphic.clear(
//        Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity));
    break;
  case MetatileTypes::water:
    metatileGraphic.clear(
      Color(0x00, 0x00, 0xFF, Color::fullAlphaOpacity));
    
    switch (indexNum) {
    case 0x9A:
      // u
      metatileGraphic.drawLine(8, 0,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(8, 0,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x9B:
      // d
      metatileGraphic.setPixel(8, 15, Color(0xFF, 0, 0,
                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(8, 0,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(8, 15,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x9C:
      // l
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x9D:
      // r
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    default:
      break;
    }
    
    break;
  case MetatileTypes::gust:
    metatileGraphic.clear(
      Color(0x00, 0x80, 0x00, Color::fullAlphaOpacity));
    switch (indexNum) {
    case 0x78:
      // u
//      metatileGraphic.setPixel(8, 0, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(8, 0,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(8, 0,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x79:
      // d
      metatileGraphic.setPixel(8, 15, Color(0xFF, 0, 0,
                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(8, 0,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(8, 15,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7A:
      // l
//      metatileGraphic.setPixel(0, 8, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7B:
      // r
//      metatileGraphic.setPixel(15, 8, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 0,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 15,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7C:
      // ul
//       metatileGraphic.setPixel(0, 0, Color(0xFF, 0, 0,
//                                            Color::fullAlphaOpacity));
      metatileGraphic.drawLine(1, 1,
                               14, 14,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(1, 1,
                               8, 1,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(1, 1,
                               1, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7D:
      // ll
 //     metatileGraphic.setPixel(0, 15, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(1, 14,
                               14, 1,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(1, 14,
                               1, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(1, 14,
                               8, 14,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7E:
      // lr
//      metatileGraphic.setPixel(15, 15, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(1, 1,
                               14, 14,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(14, 14,
                               8, 14,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(14, 14,
                               14, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x7F:
      // ur
//      metatileGraphic.setPixel(15, 0, Color(0xFF, 0, 0,
//                                           Color::fullAlphaOpacity));
      metatileGraphic.drawLine(1, 14,
                               14, 1,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(14, 1,
                               8, 1,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(14, 1,
                               14, 8,
                               Color(0xFF, 0xFF, 0x00, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    default:
      break;
    }
    break;
  case MetatileTypes::conveyorLeft:
    metatileGraphic.clear(
      Color(0x80, 0x00, 0x80, Color::fullAlphaOpacity));
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
    break;
  case MetatileTypes::crumbling:
    // ignore the name -- these are actually the tiles that the Wrench can be
    // used on to reverse conveyors
    // behavior probably hardcoded by tile ID
    metatileGraphic.clear(
      Color(0xC0, 0xC0, 0x00, Color::fullAlphaOpacity));
    switch (indexNum) {
    case 0x76:  // normal
      metatileGraphic.drawLine(0, 4,
                               15, 4,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 4,
                               4, 0,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 4,
                               4, 7,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 12,
                               0, 12,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 12,
                               12, 8,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 12,
                               12, 15,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x77:  // reversed
      metatileGraphic.drawLine(0, 4,
                               15, 4,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 4,
                               12, 0,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 4,
                               12, 7,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 12,
                               0, 12,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 12,
                               4, 8,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 12,
                               4, 15,
                               Color(0x00, 0x00, 0xFF, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    default:
      break;
    }
    break;
  case MetatileTypes::crumblingStart:
    metatileGraphic.clear(
      Color(0x00, 0x00, 0x00, Color::fullAlphaOpacity));
    for (int j = 0; j < 16; j += 2) {
      for (int k = 0; k < 16; k += 2) {
        if ((!(j % 4))) {
          // x is even: skip if y is odd
          if (((k % 4))) {
            continue;
          }
        }
        else {
          // x is odd: skip if y is even
          if ((!(k % 4))) {
            continue;
          }
        }
        
        metatileGraphic.setPixel(j, k, Color(0xFF, 0xFF, 0xFF,
                                             Color::fullAlphaOpacity));
        metatileGraphic.setPixel(j + 1, k, Color(0xFF, 0xFF, 0xFF,
                                             Color::fullAlphaOpacity));
        metatileGraphic.setPixel(j, k + 1, Color(0xFF, 0xFF, 0xFF,
                                             Color::fullAlphaOpacity));
        metatileGraphic.setPixel(j + 1, k + 1, Color(0xFF, 0xFF, 0xFF,
                                             Color::fullAlphaOpacity));
      }
    }
    break;
  case MetatileTypes::bombable:
    metatileGraphic.clear(
      Color(0xFF, 0x80, 0x00, Color::fullAlphaOpacity));
    // large bomb
    if ((indexNum == 0x63) || (indexNum == 0x64) || (indexNum == 0x65)) {
      metatileGraphic.fillRect(3, 5, 11, 10, 
                               Color(0, 0, 0, Color::fullAlphaOpacity),
                               Graphic::noTransUpdate);
      metatileGraphic.drawLine(8, 5,
                               8, 2,
                               Color(0, 0, 0, Color::fullAlphaOpacity),
                               1);
    }
    // regular bomb
    else {
      metatileGraphic.fillRect(5, 5, 7, 7, 
                               Color(0, 0, 0, Color::fullAlphaOpacity),
                               Graphic::noTransUpdate);
      metatileGraphic.drawLine(8, 5,
                               8, 2,
                               Color(0, 0, 0, Color::fullAlphaOpacity),
                               1);
    }
    
    // ring
    if (indexNum == 0x9E) {
      metatileGraphic.drawRectBorder(7, 7, 3, 3,
                               Color(0xFF, 0xFF, 0, Color::fullAlphaOpacity),
                               1,
                               Graphic::noTransUpdate);
    }
    break;
  case MetatileTypes::conveyorRight:
    metatileGraphic.clear(
      Color(0x80, 0x00, 0x80, Color::fullAlphaOpacity));
    switch (indexNum) {
    case 0x74:
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 0,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(0, 8,
                               8, 15,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    case 0x75:
      metatileGraphic.drawLine(0, 8,
                               15, 8,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 0,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      metatileGraphic.drawLine(15, 8,
                               8, 15,
                               Color(0xFF, 0x80, 0x80, 
                                     Color::fullAlphaOpacity),
                               1);
      break;
    default:
      break;
    }
    break;
  case MetatileTypes::napalm:
    metatileGraphic.clear(
      Color(0xFF, 0x80, 0x80, Color::fullAlphaOpacity));
    metatileGraphic.fillRect(5, 5, 7, 7, 
                             Color(0, 0, 0, Color::fullAlphaOpacity),
                             Graphic::noTransUpdate);
    metatileGraphic.drawLine(8, 5,
                             8, 2,
                             Color(0, 0, 0, Color::fullAlphaOpacity),
                             1);
    break;
  case MetatileTypes::downOnly:
    metatileGraphic.clear(
      Color(0x00, 0x00, 0x00, Color::fullAlphaOpacity));
//    metatileGraphic.fillRect(8, 0, 1, 16, 
//                             Color(0xFF, 0xFF, 0x00, Color::fullAlphaOpacity),
//                             Graphic::noTransUpdate);
    metatileGraphic.drawLine(8, 0,
                             8, 15,
                             Color(0xFF, 0xFF, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
    metatileGraphic.drawLine(0, 8,
                             8, 15,
                             Color(0xFF, 0xFF, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
    metatileGraphic.drawLine(8, 15,
                             15, 8,
                             Color(0xFF, 0xFF, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
    break;
  case MetatileTypes::bigGust:
    metatileGraphic.clear(
      Color(0x80, 0xFF, 0x80, Color::fullAlphaOpacity));
    metatileGraphic.drawLine(8, 0,
                             8, 15,
                             Color(0x00, 0x00, 0xFF, 
                                   Color::fullAlphaOpacity),
                             1);
    metatileGraphic.drawLine(0, 8,
                             8, 0,
                             Color(0x00, 0x00, 0xFF, 
                                   Color::fullAlphaOpacity),
                             1);
    metatileGraphic.drawLine(8, 0,
                             15, 8,
                             Color(0x00, 0x00, 0xFF, 
                                   Color::fullAlphaOpacity),
                             1);
    break;
  case MetatileTypes::typeD:
  case MetatileTypes::type10:
  case MetatileTypes::type12:
    metatileGraphic.drawLine(0, 0,
                             15, 15,
                             Color(0xFF, 0x00, 0x00, 
                                   Color::fullAlphaOpacity),
                             1);
    break;
  default:
    break;
  }
    
  metatileGraphic.regenerateTransparencyModel();
}
  
Graphic& LevelEffectGraphicSceneLayer::metatileGraphic(int metatileID) {
  return metatileCache_[metatileID];
}


}
