#ifndef LENGTHMAPVALUE_H
#define LENGTHMAPVALUE_H


#include "structs/Tbyte.h"

namespace Tales {


/**
 * A value in a length map.
 * Consists of a magnitude and a direction.
 */
class LengthMapValue {
protected:
  /**
   * Shift to retrieve the direction bit from a byte representation.
   */
  const static int byteDirectionShift = 6;
  
  /**
   * Mask to retrieve the magnitude bits from a byte representation.
   */
  const static int byteMagnitudeShift = 0;

  /**
   * Mask to retrieve the direction bit from a byte representation.
   */
  const static int byteDirectionMask = 0x1 << byteDirectionShift;
  
  /**
   * Mask to retrieve the magnitude bits from a byte representation.
   */
  const static int byteMagnitudeMask = 0x3F << byteMagnitudeShift;

public:
  /**
   * Size in bytes of an exported value.
   */
  const static int dataSize = 1;
  
  /**
   * Minimum possible magnitude value.
   */
  const static int minMagnitude = 0x00;
  
  /**
   * Maximum "regular" magnitude value.
   * Normally, length maps do not exceed either dimension of a metatile,
   * but the data format actually allows for more than this.
   */
  const static int maxRegularMagnitude = 0x10;
  
  /**
   * Maximum possible magnitude value.
   */
  const static int maxMagnitude = byteMagnitudeMask
                                    >> byteMagnitudeShift;

  /**
   * Direction of growth of a mapped value.
   */
  enum MagnitudeDirection {
    backward = 0, /**< Grows in negative direction. */
    forward = 1   /**< Grows in positive direction. */
  };
  
  /**
   * Default constructor.
   */
  LengthMapValue();
  
  /**
   * Constructor from byte value.
   * @param byteValue Exported byte value.
   */
  LengthMapValue(Tbyte byteValue);
  
  /**
   * Constructor from existing values.
   * @param magnitude__ Value magnitude.
   * @param direction__ Value direction.
   */
  LengthMapValue(int magnitude__,
                 MagnitudeDirection direction__);
  
  /**
   * Get the exported representation of this value.
   */
  Tbyte toByte();
  
  /**
   * Getter.
   */
  int magnitude();
  
  /**
   * Getter.
   */
  MagnitudeDirection direction();
  
  /**
   * Setter.
   */
  void setMagnitude(int magnitude__);
  
  /**
   * Setter.
   */
  void setDirection(MagnitudeDirection direction__);
  
protected:
  
  /**
   * Magnitude of the mapped value.
   */
  int magnitude_;
  
  /**
   * Direction of the mapped value.
   */
  MagnitudeDirection direction_;
  
};


};


#endif 
