#ifndef CHARACTERUNCOMPRESSEDGRAPHICHEADER_H
#define CHARACTERUNCOMPRESSEDGRAPHICHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


class CharacterUncompressedGraphicHeader {
public:
  const static int dataSize = 4;

  /**
   * Default constructor.
   */
  CharacterUncompressedGraphicHeader();
  
  /**
   * Constructor from raw data.
   * @param data Raw data to read from.
   */
  CharacterUncompressedGraphicHeader(const Tbyte* data);
  
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
  
protected:
  
  Taddress graphicAddress_;
  
  int numTiles_;
  
};


};


#endif
