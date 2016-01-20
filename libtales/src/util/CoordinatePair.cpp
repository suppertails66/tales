#include "util/CoordinatePair.h"

namespace Luncheon {


CoordinatePair::~CoordinatePair() { };

int CoordinatePair::x() const {
  return x_;
}
void CoordinatePair::setX(int x__) {
  x_ = x__;
}

int CoordinatePair::y() const {
  return y_;
}
void CoordinatePair::setY(int y__) {
  y_ = y__;
}

CoordinatePair::CoordinatePair()
  : x_(0), y_(0) { };

CoordinatePair::CoordinatePair(int x__, int y__)
  : x_(x__), y_(y__) { };


};
