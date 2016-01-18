#include "editors/ColorPreviewGraphicSceneLayer.h"

namespace Tales {


ColorPreviewGraphicSceneLayer::ColorPreviewGraphicSceneLayer()
  : color_(255, 255, 255, Color::fullAlphaOpacity) { };
  
void ColorPreviewGraphicSceneLayer::render(Graphic& dst,
                    Box srcbox,
                    double scale) {
  dst.fillRect(0, 0,
               srcbox.w() * scale, srcbox.h() * scale,
               color_);
}

void ColorPreviewGraphicSceneLayer::setColor(Color color__) {
  color_ = color__;
}


};
