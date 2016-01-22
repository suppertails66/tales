#ifndef TILEMAP_H
#define TILEMAP_H


#include "structs/Tbyte.h"
#include <string>

namespace Tales {


/**
 * A rectangular area composed of tiles identifiers.
 */
class TileMap {
public:
  TileMap();
  TileMap(const Tbyte* data, int w__, int h__);
  
  int readFromData(const Tbyte* data, int w__, int h__);
  void writeToData(Tbyte* data) const;
  
  void save(std::string& data) const;
  int load(const Tbyte* data);
protected:
  int w_;
  int h_;
};


};


#endif