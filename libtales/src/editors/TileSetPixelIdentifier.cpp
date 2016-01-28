#include "editors/TileSetPixelIdentifier.h"

namespace Tales {


TileSetPixelIdentifier::TileSetPixelIdentifier()
  : tileNum_(0),
    x_(0),
    y_(0) { };
    
TileSetPixelIdentifier::TileSetPixelIdentifier(
    int tileNum__, int x__, int y__)
  : tileNum_(tileNum__),
    x_(x__),
    y_(y__) { };
  
int TileSetPixelIdentifier::tileNum() const {
  return tileNum_;
}

int TileSetPixelIdentifier::x() const {
  return x_;
}
int TileSetPixelIdentifier::y() const {
  return y_;
}

void TileSetPixelIdentifier::setTileNum(int tileNum__) {
  tileNum_ = tileNum__;
}

void TileSetPixelIdentifier::setX(int x__) {
  x_ = x__;
}

void TileSetPixelIdentifier::setY(int y__) {
  y_ = y__;
}


};
