#ifndef FIXEDGRAPHICTABLEENTRY_H
#define FIXEDGRAPHICTABLEENTRY_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <string>

namespace Tales {


class FixedGraphicTableEntry {
public:
  const static int dataSize = 2;

  FixedGraphicTableEntry();
  
  FixedGraphicTableEntry(const Tbyte* data);
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  int writeToData(Tbyte* data);
  
  int readFromData(const Tbyte* data);
  
  int leftTileIndex() const;
  
  int rightTileIndex() const;
  
  void setLeftTileIndex(int leftTileIndex__);
  
  void setRightTileIndex(int rightTileIndex__);

protected:
  
  int leftTileIndex_;
  
  int rightTileIndex_;  
  
};


};


#endif
