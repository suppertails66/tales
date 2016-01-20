#include "gamedata/LengthMapValue.h"
#include <iostream>

namespace Tales {


LengthMapValue::LengthMapValue()
  : magnitude_(0),
    direction_(backward) { };

LengthMapValue::LengthMapValue(Tbyte byteValue)
  : magnitude_(
          (byteValue & byteMagnitudeMask)
            >> byteMagnitudeShift),
    direction_(
          (byteValue & byteDirectionMask)
          ? forward
          : backward) { };
    

LengthMapValue::LengthMapValue(
               int magnitude__,
               MagnitudeDirection direction__)
  : magnitude_(magnitude__),
    direction_(direction__) { };

Tbyte LengthMapValue::toByte() {
  Tbyte output = 0x00;
  
  // Set direction bit (set = forward growth, unset = backward growth)
  if (direction_ == forward) {
    output |= byteDirectionMask;
  }
  
  // Set magnitude bits, reducing to valid range first
  output |= 
    ((magnitude_ & byteMagnitudeMask) << byteMagnitudeShift);
  
  return output;
}

int LengthMapValue::magnitude() {
  return magnitude_;
}

LengthMapValue::MagnitudeDirection LengthMapValue::direction() {
  return direction_;
}

void LengthMapValue::setMagnitude(int magnitude__) {
  magnitude_ = magnitude__;
}

void LengthMapValue::setDirection(MagnitudeDirection direction__) {
  direction_ = direction__;
}


};
