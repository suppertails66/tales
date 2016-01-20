#ifndef METATILESTRUCTURE_H
#define METATILESTRUCTURE_H


#include "gamegear/TileReference.h"
#include "structs/Tbyte.h"

namespace Tales {


/**
 * Structure of a metatile from component tiles.
 */
class MetatileStructure {
public:
  /**
   * Size of raw data.
   */
  const static int dataSize = 8;
  
  const static int metatileWidth = 16;
  const static int metatileHeight = 16;

  /**
   * Default constructor.
   */
  MetatileStructure();
  
  /**
   * Constructor from raw tile identifiers.
   * @param upperLeft__ Upper-left tile VRAM identifier.
   * @param upperRight__ Upper-right tile VRAM identifier.
   * @param lowerLeft__ Lower-left tile VRAM identifier.
   * @param lowerRight__ Lower-right tile VRAM identifier.
   */
  MetatileStructure(unsigned int upperLeft__,
                            unsigned int upperRight__,
                            unsigned int lowerLeft__,
                            unsigned int lowerRight__);
  
  /**
   * Constructor from TileReferences.
   * @param upperLeft__ Upper-left tile.
   * @param upperRight__ Upper-right tile.
   * @param lowerLeft__ Lower-left tile.
   * @param lowerRight__ Lower-right tile.
   */
  MetatileStructure(TileReference upperLeft__,
                            TileReference upperRight__,
                            TileReference lowerLeft__,
                            TileReference lowerRight__);
  
  /**
   * Saves to data.
   * @param data Byte array to write to.
   */
  void writeToData(Tbyte* data);
  
  /**
   * Loads from data.
   * @param data Data to load.
   * @return Number of bytes of data read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Getter.
   */
  TileReference& upperLeft();
  
  /**
   * Getter.
   */
  TileReference& upperRight();
  
  /**
   * Getter.
   */
  TileReference& lowerLeft();
  
  /**
   * Getter.
   */
  TileReference& lowerRight();
  
  /**
   * Getter.
   */
//  TileReference upperLeft() const;
  
  /**
   * Getter.
   */
//  TileReference upperRight() const;
  
  /**
   * Getter.
   */
//  TileReference lowerLeft() const;
  
  /**
   * Getter.
   */
//  TileReference lowerRight() const;
  
  /**
   * Setter.
   */
//  void setUpperLeft(TileReference upperLeft__);
  
  /**
   * Setter.
   */
//  void setUpperRight(TileReference upperRight__);
  
  /**
   * Setter.
   */
//  void setLowerLeft(TileReference lowerLeft__);
  
  /**
   * Setter.
   */
//  void setLowerRight(TileReference lowerRight__);
  
protected:

  /**
   * VRAM identifier of the upper-left tile of the metatile.
   */
  TileReference upperLeft_;
  
  /**
   * VRAM identifier of the upper-right tile of the metatile.
   */
  TileReference upperRight_;
  
  /**
   * VRAM identifier of the lower-left tile of the metatile.
   */
  TileReference lowerLeft_;
  
  /**
   * VRAM identifier of the lower-right tile of the metatile.
   */
  TileReference lowerRight_;
};


};


#endif 
