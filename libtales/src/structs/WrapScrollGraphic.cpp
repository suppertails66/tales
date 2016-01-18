#include "structs/WrapScrollGraphic.h"
#include <iostream>

namespace Tales {


WrapScrollGraphic::WrapScrollGraphic()
  : surface_(),
    offsetX_(0),
    offsetY_(0) { };

WrapScrollGraphic::WrapScrollGraphic(int w, int h)
  : surface_(w, h),
    offsetX_(0),
    offsetY_(0) { };
  
void WrapScrollGraphic::scrollInX(int amount) {
  offsetX_ = (offsetX_ + amount) % surface_.w();
}

void WrapScrollGraphic::scrollInY(int amount) {
  offsetY_ = (offsetY_ + amount) % surface_.h();
}

Graphic& WrapScrollGraphic::surface() {
  return surface_;
}

int WrapScrollGraphic::offsetX() const {
  return offsetX_;
}

int WrapScrollGraphic::offsetY() const {
  return offsetY_;
}

void WrapScrollGraphic::blit(const Graphic& src,
          Box dstbox,
          Box srcbox,
          Graphic::TransBlitOption updateTrans) {
  int xPos = (dstbox.x() + offsetX_) % surface_.w();
  if (xPos < 0) {
    xPos += surface_.w();
  }
  
  int yPos = (dstbox.y() + offsetY_) % surface_.h();
  if (yPos < 0) {
    yPos += surface_.h();
  }
  
//  std::cout << xPos << " " << yPos << " "
//    << dstbox.w() << " " << dstbox.h() << std::endl;
          
  surface_.blit(src,
                    Box(xPos,
                        yPos,
                        dstbox.w(),
                        dstbox.h()),
                    srcbox,
                    updateTrans);
}

void WrapScrollGraphic::copy(const Graphic& src,
          Box dstbox,
          Box srcbox,
          Graphic::TransBlitOption updateTrans) {
  int xPos = (dstbox.x() + offsetX_) % surface_.w();
  if (xPos < 0) {
    xPos += surface_.w();
  }
  
  int yPos = (dstbox.y() + offsetY_) % surface_.h();
  if (yPos < 0) {
    yPos += surface_.h();
  }
  
  surface_.copy(src,
                    Box(xPos,
                        yPos,
                        dstbox.w(),
                        dstbox.h()),
                    srcbox,
                    updateTrans);
}


};
