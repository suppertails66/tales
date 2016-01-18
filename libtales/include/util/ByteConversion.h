#ifndef BYTECONVERIONS_H
#define BYTECONVERIONS_H


#include "util/EndiannessType.h"
#include "util/SignednessType.h"

namespace Luncheon {


class ByteConversion {
public:
  static int fromBytes(const char* bytes,
                       int numBytes,
                       EndiannessTypes::EndiannessType endianness,
                       SignednessTypes::SignednessType signedness);
                       
  static void toBytes(int value,
                      char* dest,
                      int numBytes,
                      EndiannessTypes::EndiannessType endianness,
                      SignednessTypes::SignednessType signedness);
                      
  static int fromBytes(const unsigned char* bytes,
                       int numBytes,
                       EndiannessTypes::EndiannessType endianness,
                       SignednessTypes::SignednessType signedness);
                       
  static void toBytes(int value,
                      unsigned char* dest,
                      int numBytes,
                      EndiannessTypes::EndiannessType endianness,
                      SignednessTypes::SignednessType signedness);
protected:
};


};


#endif 
