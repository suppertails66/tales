#ifndef STANDARDUNCOMPRESSEDGRAPHICHEADER_H
#define STANDARDUNCOMPRESSEDGRAPHICHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


class StandardUncompressedGraphicHeader {
public:
  const static int dataSize = 7;

  /**
   * Default constructor.
   */
  StandardUncompressedGraphicHeader();
  
  /**
   * Constructor from raw data.
   * @param data Raw data to read from.
   */
  StandardUncompressedGraphicHeader(const Tbyte* data);
  
  /**
   * Read from raw data.
   * @param data Raw data to read from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Getter.
   */
  Taddress graphicAddress() const;
  
  /**
   * Getter.
   */
  int numTiles() const;
  
  /**
   * Getter.
   */
  Taddress vramWriteAddress() const;
  
  
protected:
  
  Taddress graphicAddress_;
  
  int numTiles_;
  
  Taddress vramWriteAddress_;
  
};


};


#endif
