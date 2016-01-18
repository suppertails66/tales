#ifndef RLE8COMPRESSOR_H
#define RLE8COMPRESSOR_H


#include "util/RLE8CommandCollection.h"
#include "util/RLE8Command.h"

namespace Luncheon {


class RLE8Compressor {
public:
  virtual ~RLE8Compressor();
  
  static void compress(char* source,
                        int sourceSize,
                        RLE8CommandCollection& destination);
  
  static void decompress(RLE8CommandCollection& source,
                        char* destination,
                        int destinationSize);
                        
  static int calculateCompressedByteSize(RLE8CommandCollection& source);
  
  static void compressToBytes(RLE8CommandCollection& source,
                              char* destination,
                              int destinationSize);
  
  static void decompressToBytes(char* source,
                                int sourceSize,
                                char* destination,
                                int destinationSize);
protected:
  RLE8Compressor();
  
  // Number of consecutive bytes required to trigger
  // a repeat command
  const static int defaultRepeatTolerance = 3;
                                 
  static void compressionLoop(char* source,
                              int& sourceSize,
                              RLE8CommandCollection& destination,
                              int& pos,
                              int& absoluteRunStart,
                              int& repeatRunStart,
                              char& repeatCheck,
                              int& repeatCount);
  
  static void writeAbsoluteCommand(char* source,
                                   int length,
                                   RLE8CommandCollection& destination);
  
  static void writeRepeatCommand(char repeatChar,
                                 int length,
                                 RLE8CommandCollection& destination);
  
};


};


#endif 
