#include "util/MiscMath.h"

namespace Luncheon {


unsigned int MiscMath::fromBCD(unsigned int bcdValue) {
/*  int digits = 0;
  unsigned int digitsCheck = bcdValue;
  while (digitsCheck > 0) {
    digitsCheck /= 0x10;
    ++digits;
  }
  
  unsigned int result = 0;
  int placeMult = 1;
  for (int i = 0; i < digits; i++) {
    unsigned int digit = (bcdValue & 0x0F);
    bcdValue >>= 4;
    
    result += (digit * placeMult);
    
    placeMult *= 10;
  } */
  
  unsigned int result = 0;
  int placeMult = 1;
  
  while (bcdValue > 0) {
    result += ((bcdValue & 0x0F) * placeMult);
    bcdValue >>= 4;
    placeMult *= 10;
  }
  
  return result;
}

unsigned int MiscMath::toBCD(unsigned int intValue) {
  int result = 0;
  int shift = 0;
  
  while (intValue > 0) {
    int digit = intValue % 10;
    intValue /= 10;
    
    result |= (digit << shift);
    
    shift += 4;
  }
  
  return result;
}


}; 
