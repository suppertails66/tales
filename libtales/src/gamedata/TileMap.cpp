#include "gamedata/TileMap.h"

namespace Tales {


TileMap::TileMap()
  : w_(0), h_(0) { };

TileMap::TileMap(const Tbyte* data, int w__, int h__)
  : w_(w__),
    h_(h__) {
  readFromData(data, w__, h__);
}

int TileMap::readFromData(const Tbyte* data, int w__, int h__) {
  int byteCount = 0;
  
  return byteCount;
}

void TileMap::writeToData(Tbyte* data) const {
  
}

void TileMap::save(std::string& data) const {
  
}

int TileMap::load(const Tbyte* data) {
  int byteCount = 0;
  
  return byteCount;
}


};