#ifndef OBJECTGRAPHICSUBHEADER_H
#define OBJECTGRAPHICSUBHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <string>

namespace Tales {


/**
 * Storage for and access on an object graphics subheader.
 * Allows graphic number and write address to be modified.
 */
class ObjectGraphicSubheader {
public:
  /**
   * Size in bytes of raw data representation.
   */
  const static int dataSize = 5;
  
  /**
   * Enum of substitution settings (horizontal flipping flag).
   * If enabled, the graphic assocated with this subheader will be flipped
   * horizontally before being loaded to VRAM.
   */
  enum SubstitutionOption {
    substitutionDisabled = 0,   /**< Horizontal flipping enabled. */
    substitutionEnabled = 1     /**< Horizontal flipping disabled. */
  };

  /**
   * Default constructor.
   */
  ObjectGraphicSubheader();
  
  /**
   * Constructor from known data.
   */
  ObjectGraphicSubheader(/*Taddress romExportAddress__,*/
                         Taddress vdpWriteAddress__,
                         int objectGraphicIndex__,
                         SubstitutionOption substitutionOption__);
  
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
   * @param objectGraphicAddress Direct address of the object graphic.
   * This should be looked up using the contained object graphic index.
   * @return Number of bytes written.
   */
  int exportToData(Tbyte* data,
                   Taddress objectGraphicAddress);
  
  /**
   * Getter.
   */
//  Taddress romExportAddress() const;

  int tileWriteIndex() const;

  void setTileWriteIndex(int tileWriteIndex);
  
  /**
   * Getter.
   */
  Taddress vdpWriteAddress() const;
  
  /**
   * Getter.
   */
  int objectGraphicIndex() const;
  
  /**
   * Getter.
   */
  SubstitutionOption substitutionOption() const;
  
  /**
   * Setter.
   */
//  void setRomExportAddress(Taddress romExportAddress_);
  
  /**
   * Setter.
   */
  void setVdpWriteAddress(Taddress vdpWriteAddress__);
  
  /**
   * Setter.
   */
  void setObjectGraphicIndex(int objectGraphicIndex__);
  
  /**
   * Setter.
   */
  void setSubstitutionOption(SubstitutionOption substitutionOption__);
  
protected:

  /**
   * Mask for substitution flag.
   */
  const static int substitutionMask = 0x80;

  /**
   * ROM export address.
   */
//  Taddress romExportAddress_;

  /**
   * VDP write address.
   */
  Taddress vdpWriteAddress_;
  
  /**
   * Object graphic index number.
   */
  int objectGraphicIndex_;
  
  /**
   * Horizontal flipping setting.
   */
  SubstitutionOption substitutionOption_;
  
};


};


#endif
