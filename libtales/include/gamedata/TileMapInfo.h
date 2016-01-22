#ifndef TILEMAPINFO_H
#define TILEMAPINFO_H


#include "gamedata/TileMap.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"

namespace Tales {


class TileMapInfo {
public:
  TileMapInfo();
  TileMapInfo(Taddress address__,
              int w__,
              int h__,
              TileMap::TileMapFormat format__,
              int graphicNum__,
              int offset__,
              int paletteNum__,
              Tbyte upperByte__ = 0);
              
  Taddress address;
  int w;
  int h;
  TileMap::TileMapFormat format;
  int graphicNum;
  int offset;
  int paletteNum;
  Tbyte upperByte;
  
/*protected:
  Taddress address_;
  int w_;
  int h_;
  TileMap::TileMapFormat format_;
  int graphicNum_;
  int offset_;
  int paletteNum_;
  Tbyte upperByte_; */
};


};


#endif
