#include "editors/LevelBoundsGraphicSceneLayer.h"

namespace Tales {


LevelBoundsGraphicSceneLayer
    ::LevelBoundsGraphicSceneLayer(LevelHeader& levelHeader__)
  : levelHeader_(&levelHeader__) { };
                               
LevelBoundsGraphicSceneLayer
    ::~LevelBoundsGraphicSceneLayer() { };
                      
void LevelBoundsGraphicSceneLayer
        ::render(Graphic& dst,
                    Box srcbox,
                    double scale) {
  int leftX = (levelHeader_->cameraLeftLimit() - srcbox.x()
                  + marginLeft_) * scale;
  int rightX = (levelHeader_->cameraRightLimit() - srcbox.x()
                  + marginRight_) * scale;
  int topY = (levelHeader_->cameraTopLimit() - srcbox.y()
                  + marginTop_) * scale;
  int bottomY = (levelHeader_->cameraBottomLimit() - srcbox.y()
                  + marginBottom_) * scale;
  
  dst.drawLine(leftX, 0,
               leftX, dst.h(),
               Color(255, 255, 0, Color::fullAlphaOpacity),
               2,
               Graphic::noTransUpdate);
  
  dst.drawLine(rightX, 0,
               rightX, dst.h(),
               Color(255, 255, 0, Color::fullAlphaOpacity),
               2,
               Graphic::noTransUpdate);
  
  dst.drawLine(0, topY,
               dst.w(), topY,
               Color(255, 255, 0, Color::fullAlphaOpacity),
               2,
               Graphic::noTransUpdate);
  
  dst.drawLine(0, bottomY,
               dst.w(), bottomY,
               Color(255, 255, 0, Color::fullAlphaOpacity),
               2,
               Graphic::noTransUpdate);
}


};
