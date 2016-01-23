#ifndef TILEMAPINFOS_H
#define TILEMAPINFOS_H


#include "gamedata/TileMapInfo.h"

namespace Tales {


class TileMapInfos {
public:
  /**
   * Returns number of tilemaps.
   * @return Number of tilemaps.
   */
  static int numTileMaps();
  
  /**
   * Returns TileMapInfo for the given tilemap index.
   * @return TileMapInfo for the given tilemap index.
   */
  static TileMapInfo tileMapInfo(int index);
protected:
  /**
   * Number of tilemaps.
   */
  const static int numTileMaps_ = 184;
  
  /**
   * Array of tilemap infos.
   */
  const static TileMapInfo tileMapInfos_[];
};


};


#endif
