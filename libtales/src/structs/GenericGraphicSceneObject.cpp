#include "structs/GenericGraphicSceneObject.h"

namespace Tales {


GenericGraphicSceneObject::GenericGraphicSceneObject()
  : x_(0),
    y_(0),
    visible_(false) { };
  
GenericGraphicSceneObject::GenericGraphicSceneObject(
                          int x__,
                          int y__,
                          bool visible__)
  : x_(x__),
    y_(y__),
    visible_(visible__) { };

GenericGraphicSceneObject::~GenericGraphicSceneObject() { };
  
int GenericGraphicSceneObject::x() const {
  return x_;
}

int GenericGraphicSceneObject::y() const {
  return y_;
}

bool GenericGraphicSceneObject::visible() const {
  return visible_;
}

void GenericGraphicSceneObject::setX(int x__) {
  x_ = x__;
}

void GenericGraphicSceneObject::setY(int y__) {
  y_ = y__;
}

void GenericGraphicSceneObject::setVisible(bool visible__) {
  visible_ = visible__;
}


};
