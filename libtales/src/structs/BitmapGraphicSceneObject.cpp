#include "structs/BitmapGraphicSceneObject.h"

namespace Tales {


BitmapGraphicSceneObject::BitmapGraphicSceneObject()
  : GenericGraphicSceneObject() { };
  
BitmapGraphicSceneObject::BitmapGraphicSceneObject(
                         Graphic bitmap__,
                         int x__,
                         int y__,
                         bool visible__)
  : GenericGraphicSceneObject(x__, y__, visible__),
    bitmap_(bitmap__) { };
  
void BitmapGraphicSceneObject::render(
                      Graphic& dst,
                      Box srcbox,
                      double scale) {
  // Calculate Graphic-local coordinates
  int realX = x_ - srcbox.x();
  int realY = y_ - srcbox.y();
  
  if (scale == 1.00) {
    // Blit
    dst.blit(bitmap_,
             Box(realX, realY, 0, 0),
             Graphic::noTransUpdate);
  }
  else {
    // Apply scaling
    realX *= scale;
    realY *= scale;
    
    // Create temporary graphic to hold scaled bitmap
    Graphic scaledBitmap(bitmap_.w() * scale, bitmap_.h() * scale);
    
    // Scale bitmap
    bitmap_.scale(scaledBitmap);
    
    // Blit
    dst.blit(scaledBitmap,
             Box(realX, realY, 0, 0),
             Graphic::noTransUpdate);
  }
}


};
