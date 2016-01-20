#include "structs/GenericGraphicSceneLayer.h"
#include <iostream>

namespace Tales {


GenericGraphicSceneLayer::GenericGraphicSceneLayer()
  : GraphicSceneLayer() { };

GenericGraphicSceneLayer::~GenericGraphicSceneLayer() {
  // Delete all object pointers
  for (int i = 0; i < graphicPointers_.size(); i++) {
    delete graphicPointers_[i];
  }
}

void GenericGraphicSceneLayer::render(
                      Graphic& dst,
                      Box srcbox,
                      double scale) {
  render(dst,
         srcbox,
         scale,
         1.00);
}

void GenericGraphicSceneLayer::render(
                      Graphic& dst,
                      Box srcbox,
                      double preScale,
                      double postScale) {
  // Render all objects
  for (int i = 0; i < graphicPointers_.size(); i++) {
    graphicPointers_[i]->render(dst,
                                srcbox,
                                preScale);
  }
  
  // Apply post-render scaling if needed
  if (postScale != 1.00) {
    Graphic tmp(srcbox.w() * postScale, srcbox.h() * postScale);
    dst.scale(tmp);
    dst = tmp;
  }
}
                      
void GenericGraphicSceneLayer::addObject(GenericGraphicSceneObject* object) {
  graphicPointers_.push_back(object);
}
                      
void GenericGraphicSceneLayer::clearObjects() {
  for (int i = 0; i < graphicPointers_.size(); i++) {
    delete graphicPointers_[i];
  }
  
  graphicPointers_.clear();
}


};
