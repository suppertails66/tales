#include "gamedata/TileMapInfo.h"

namespace Tales {


TileMapInfo::TileMapInfo()
  : address(0),
    w(0),
    h(0),
    format(TileMap::twoBytesPerTile),
    graphicNum(0),
    offset(0),
    paletteNum(0),
    upperByte(0) { };

TileMapInfo::TileMapInfo(Taddress address__,
            int w__,
            int h__,
            TileMap::TileMapFormat format__,
            int graphicNum__,
            int offset__,
            int paletteNum__,
            std::string name__,
            Tbyte upperByte__)
  : address(address__),
    w(w__),
    h(h__),
    format(format__),
    graphicNum(graphicNum__),
    offset(offset__),
    paletteNum(paletteNum__),
    name(name__),
    upperByte(upperByte__) { };


};
