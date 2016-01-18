#ifndef RAWSPRITEMAPPING_H
#define RAWSPRITEMAPPING_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"

namespace Tales {


class RawSpriteMapping {
public:
  /**
   * Default constructor.
   */
  RawSpriteMapping();
  
  /**
   * Constructor from raw data.
   * @param data Raw data to load from.
   */
  RawSpriteMapping(const Tbyte* data);
  
  /**
   * Getter.
   */
  int numSprites() const;
  
  /**
   * Getter.
   */
  int collisionXLength() const;
  
  /**
   * Getter.
   */
  int collisionYLength() const;
  
  /**
   * Getter.
   */
  Taddress coordinateTableBankedAddress() const;
  
  /**
   * Getter.
   */
  int offsetY() const;
  
  /**
   * Getter.
   */
  int offsetX() const;
  
  /**
   * Getter.
   */
  Taddress tileIndexTableBankedAddress() const;
  
protected:
  
  int numSprites_;
  
  int collisionXLength_;
  
  int collisionYLength_;
  
  Taddress coordinateTableBankedAddress_;
  
  int offsetY_;
  
  int offsetX_;
  
  Taddress tileIndexTableBankedAddress_;
  
};


};


#endif
