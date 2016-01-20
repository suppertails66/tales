#include "editors/GridGraphicSceneLayer.h"
#include <iostream>

namespace Tales {


GridGraphicSceneLayer::GridGraphicSceneLayer()
  : GraphicSceneLayer(),
    lineSpacing_(0),
    lineWidth_(0),
    enlargeOnZoom_(false),
    xLimit_(0),
    yLimit_(0) { };
  
GridGraphicSceneLayer::GridGraphicSceneLayer(
                      int lineSpacing__,
                      int lineWidth__,
                      Color color__,
                      bool enlargeOnZoom__)
  : GraphicSceneLayer(),
    lineSpacing_(lineSpacing__),
    lineWidth_(lineWidth__),
    color_(color__),
    enlargeOnZoom_(enlargeOnZoom__),
    xLimit_(0),
    yLimit_(0) { };
  
void GridGraphicSceneLayer::render(Graphic& dst,
            Box srcbox,
            double scale) {
  if (!visible_) {
    return;
  }
  
//  int maxPos = basePos + (srcbox.w() * scale);
  int realSpacing = lineSpacing_ * scale;
  
  int realXLimit = xLimit_ * scale;
  int realYLimit = yLimit_ * scale;
  
  if (xLimit_ == 0) {
//    realXLimit = (srcbox.x() + srcbox.w()) * scale;
    realXLimit = dst.w();
  }
  
  if (yLimit_ == 0) {
//    realYLimit = (srcbox.y() + srcbox.h()) * scale;
    realYLimit = dst.h();
  }
  
  if (dst.w() < realXLimit) {
    realXLimit = dst.w();
  }
  
  if (dst.h() < realYLimit) {
    realYLimit = dst.h();
  }
  
  int realLineWidth = lineWidth_;
  if (enlargeOnZoom_) {
    realLineWidth *= scale;
  }
  
  // Compute where to start drawing lines
  int baseXPos = srcbox.x() * scale;
//  int baseXPos = srcbox.x();
  int drawXBase = -(baseXPos % realSpacing);
  
  int baseYPos = srcbox.y() * scale;
//  int baseYPos = srcbox.y();
  int drawYBase = -(baseYPos % realSpacing);
  
  // Draw vertical lines
  for (int i = drawXBase; i < realXLimit; i += realSpacing) {
    dst.drawLine(i, 0,
                 i, realYLimit,
                 color_,
                 realLineWidth,
                 Graphic::noTransUpdate);
  }
  
  // Draw horizontal lines
  for (int i = drawYBase; i < realYLimit; i += realSpacing) {
    dst.drawLine(0, i,
                 realXLimit, i,
                 color_,
                 realLineWidth,
                 Graphic::noTransUpdate);
  }
}
  
int GridGraphicSceneLayer::lineSpacing() const {
  return lineSpacing_;
}

int GridGraphicSceneLayer::lineWidth() const {
  return lineWidth_;
}

Color GridGraphicSceneLayer::color() const {
  return color_;
}

bool GridGraphicSceneLayer::enlargeOnZoom() const {
  return enlargeOnZoom_;
}

void GridGraphicSceneLayer::setLineSpacing(int lineSpacing__) {
  lineSpacing_ = lineSpacing__;
}

void GridGraphicSceneLayer::setLineWidth(int lineWidth__) {
  lineWidth_ = lineWidth__;
}

void GridGraphicSceneLayer::setColor(Color color__) {
  color_ = color__;
}

void GridGraphicSceneLayer::setEnlargeOnZoom(bool enlargeOnZoom__) {
  enlargeOnZoom_ = enlargeOnZoom__;
}
  
void GridGraphicSceneLayer::setXLimit(int xLimit__) {
  xLimit_ = xLimit__;
}

void GridGraphicSceneLayer::setYLimit(int yLimit__) {
  yLimit_ = yLimit__;
}


};
