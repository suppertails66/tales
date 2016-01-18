#include "structs/BoxGraphicSceneObject.h"

namespace Tales {


BoxGraphicSceneObject::BoxGraphicSceneObject()
  : GenericGraphicSceneObject(),
    lineWidth_(0),
    width_(0),
    height_(0) { };
  
BoxGraphicSceneObject::BoxGraphicSceneObject(
                      Color color__,
                      int lineWidth__,
                      int width__,
                      int height__,
                      int x__,
                      int y__,
                      bool visible__)
  : GenericGraphicSceneObject(x__, y__, visible__),
    color_(color__),
    lineWidth_(lineWidth__),
    width_(width__),
    height_(height__) { };
  
void BoxGraphicSceneObject::render(Graphic& dst,
                                   Box srcbox,
                                   double scale) {
  // Calculate Graphic-local coordinates
  int realX = x_ - srcbox.x();
  int realY = y_ - srcbox.y();
  
  // Apply scaling
  realX *= scale;
  realY *= scale;
    
  // Draw border
  dst.drawRectBorder(realX,
                     realY,
                     width_ * scale,
                     height_ * scale,
                     color_,
                     lineWidth_,
                     Graphic::noTransUpdate);
}


}; 
