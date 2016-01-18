#ifndef LEVELGRAPHICSHEADER_H
#define LEVELGRAPHICSHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <string>

namespace Tales {


class LevelGraphicsHeader {
public:
  /**
   * Size in bytes of exported data.
   */
  const static int dataSize = 7;

  /**
   * Default constructor.
   */
  LevelGraphicsHeader();
  
  /**
   * Constructor from known values.
   */
  LevelGraphicsHeader(/*Taddress romExportAddress__,*/
                      Taddress vdpWriteAddress__,
                      int mapGraphicIndex__,
                      int objectGraphicsHeaderIndex__);
  
  /**
   * Writes to a string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Reads from a byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Write to a byte array.
   * @param data Byte array to write to. Size must be at least (dataSize)
   * bytes.
   * @param mapGraphicAddress Direct address of the map graphic.
   * This should be looked up using the contained map graphic index.
   * @param objectGraphicsHeaderAddress Direct address of the object
   * graphic header. This should be looked up using the contained index.
   * @return Number of bytes written.
   */
  int exportToData(Tbyte* data,
                   Taddress mapGraphicAddress,
                   Taddress objectGraphicsHeaderAddress);
  
  /**
   * Getter.
   */
//  Taddress romExportAddress() const;

  /**
   * Getter.
   */
  Taddress vdpWriteAddress() const;

  /**
   * Getter.
   */
  int mapGraphicIndex() const;

  /**
   * Getter.
   */
  int objectGraphicsHeaderIndex() const;
  
  /**
   * Setter.
   */
//  void setRomExportAddress(Taddress romExportAddress__);
  
  /**
   * Setter.
   */
  void setVdpWriteAddress(Taddress vdpWriteAddress__);
  
  /**
   * Setter.
   */
  void setMapGraphicIndex(int mapGraphicIndex__);
  
  /**
   * Setter.
   */
  void setObjectGraphicsHeaderIndex(int objectGraphicsHeaderIndex__);
  
protected:
  /**
   * ROM export address.
   */
//  Taddress romExportAddress_;

  /**
   * VDP write address.
   */
  Taddress vdpWriteAddress_;

  /**
   * Index number of the map graphic.
   */
  int mapGraphicIndex_;

  /**
   * Index number of the object graphics header.
   */
  int objectGraphicsHeaderIndex_;
  
};


};


#endif
