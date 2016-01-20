#include "util/RLE8Compressor.h"
#include <iostream>

namespace Luncheon {


RLE8Compressor::~RLE8Compressor() { };

RLE8Compressor::RLE8Compressor() { };
  
void RLE8Compressor::compress(char* source,
                              int sourceSize,
                              RLE8CommandCollection& destination) {
  int pos = 0;
  int absoluteRunStart = 0;
  int repeatRunStart = 0;
  char repeatCheck;
  if (sourceSize > 0) {
    repeatCheck = source[0];
    ++pos;
  }
  int repeatCount = 0;
  
  while (pos < sourceSize) {
  
    compressionLoop(source,
                    sourceSize,
                    destination,
                    pos,
                    absoluteRunStart,
                    repeatRunStart,
                    repeatCheck,
                    repeatCount);
  
    repeatCheck = source[pos];
    ++pos;
  }
  
  // write out anything remaining
  
  // repeat + absolute
  if (repeatCount >= defaultRepeatTolerance - 1) {
    writeAbsoluteCommand(source + absoluteRunStart,
                         repeatRunStart - absoluteRunStart,
                         destination);
    writeRepeatCommand(source[repeatRunStart],
                       pos - repeatRunStart,
                       destination);
  }
  // absolute only
  else {
    repeatRunStart = pos;
    writeAbsoluteCommand(source + absoluteRunStart,
                         repeatRunStart - absoluteRunStart,
                         destination);
  }
  
/*  compressionLoop(source,
                  sourceSize,
                  destination,
                  pos,
                  absoluteRunStart,
                  repeatRunStart,
                  repeatCheck,
                  repeatCount); */
  
}
  
void RLE8Compressor::decompress(RLE8CommandCollection& source,
                      char* destination,
                      int destinationSize) {
  int pos = 0;
  for (RLE8CommandCollection::iterator it = source.begin();
       it != source.end();
       ++it) {
    switch (it->commandType()) {
    case RLE8CommandTypes::absolute:
      for (RLE8ValueCollection::iterator sit = it->values().begin();
           sit != it->values().end();
           ++sit) {
         destination[pos++] = *sit;
      }
      break;
    case RLE8CommandTypes::repeat:
      for (int i = 0; i < it->quantity(); i++) {
         destination[pos++] = *(it->values().begin());
      }
      break;
    default:
      break;
    }
    
  }
}
  
void RLE8Compressor::compressToBytes(RLE8CommandCollection& source,
                                     char* destination,
                                     int destinationSize) {
  int pos = 0;
  for (RLE8CommandCollection::iterator it = source.begin();
       it != source.end();
       ++it) {
       
//    std::cerr << "type: " << it->commandType() << std::endl;
//    std::cerr << "quantity: " << it->quantity() << std::endl;
//    std::cerr << "values.size(): " << it->values().size() << std::endl;
       
    char commandByte = 0;
       
    switch (it->commandType()) {
    case RLE8CommandTypes::absolute:
      commandByte = static_cast<char>(it->values().size());
      break;
    case RLE8CommandTypes::repeat:
      commandByte = static_cast<char>(it->quantity());
      commandByte |= 0x80;
      break;
    default:
      break;
    }
    
    destination[pos++] = commandByte;
       
    switch (it->commandType()) {
    case RLE8CommandTypes::absolute:
      for (RLE8ValueCollection::iterator sit = it->values().begin();
           sit != it->values().end();
           ++sit) {
        destination[pos++] = *sit;
      }
      break;
    case RLE8CommandTypes::repeat:
      destination[pos++] = *(it->values().begin());
      break;
    default:
      break;
    }
  }
}
  
void RLE8Compressor::decompressToBytes(
                              char* source,
                              int sourceSize,
                              char* destination,
                              int destinationSize) {
  int getPos = 0;
  int putPos = 0;
  while (getPos < sourceSize) {
    char command = source[getPos++];
    
    // repeat
    if (command & 0x80) {
      int total = (int)((unsigned char)(command & 0x7F));
      char target = source[getPos++];
      for (int i = 0; i < total; i++) {
        destination[putPos++] = target;
      }
    }
    // absolute
    else {
      int total = (int)((unsigned char)(command));
      for (int i = 0; i < total; i++) {
        destination[putPos++] = source[getPos++];
      }
    }
  }
}
                        
int RLE8Compressor::calculateCompressedByteSize(RLE8CommandCollection& source) {
  int total = 0;
    
  for (RLE8CommandCollection::iterator it = source.begin();
       it != source.end();
       ++it) {
    // size of command byte
    total += 1;
    
    // size of run
    total += it->values().size();
    
/*    switch (it->commandType()) {
    case RLE8CommandTypes::absolute:
      total += it->values().size();
      break;
    case RLE8CommandTypes::repeat:
      total += 1;
      break;
    default:
      break;
    } */
  }
  return total;
}
                                 
void RLE8Compressor::compressionLoop(char* source,
                                     int& sourceSize,
                                     RLE8CommandCollection& destination,
                                     int& pos,
                                     int& absoluteRunStart,
                                     int& repeatRunStart,
                                     char& repeatCheck,
                                     int& repeatCount) {
  
  // repeat run
  if (source[pos] == repeatCheck) {
    ++repeatCount;
    
    // if maximum repeat reached, write everything out and reset
    if (repeatCount == 127) {
      writeAbsoluteCommand(source + absoluteRunStart,
                           repeatRunStart - absoluteRunStart,
                           destination);
      writeRepeatCommand(source[repeatRunStart],
                         pos - repeatRunStart,
                         destination);
      absoluteRunStart = pos;
      repeatRunStart = pos;
      repeatCount = 0;
    }
  }
  // repeat ended
  else {
    // repeat command triggered
    if (repeatCount >= defaultRepeatTolerance - 1) {
      writeAbsoluteCommand(source + absoluteRunStart,
                           repeatRunStart - absoluteRunStart,
                           destination);
      writeRepeatCommand(source[repeatRunStart],
                         pos - repeatRunStart,
                         destination);
      absoluteRunStart = pos;
      repeatRunStart = pos;
      repeatCount = 0;
    }
    // no repeat: extend absolute run
    else {
      // start checking for new repeat at current position
      repeatRunStart = pos;
      repeatCount = 0;

      // maximum absolute size reached
      if (repeatRunStart - absoluteRunStart == 127) {
        writeAbsoluteCommand(source + absoluteRunStart,
                             repeatRunStart - absoluteRunStart,
                             destination);
        absoluteRunStart = pos;
      }
    }
  }
  
/*  std::cout << "pos: " << pos << std::endl;
  std::cout << "absoluteRunStart: " << absoluteRunStart << std::endl;
  std::cout << "repeatRunStart: " << repeatRunStart << std::endl;
  std::cout << "repeatCheck: " << (int)repeatCheck << std::endl;
  std::cout << "repeatCount: " << repeatCount << std::endl;
  std::cout << std::endl; */
}

void RLE8Compressor::writeAbsoluteCommand(char* source,
                                          int length,
                                          RLE8CommandCollection& destination) {
  if (length == 0) {
    return;
  }
//  std::cout << "absolute" << std::endl;
  
  RLE8Command absoluteRun;
  absoluteRun.setCommandType(RLE8CommandTypes::absolute);
  absoluteRun.setQuantity(length);
  for (int i = 0; i < length; i++) {
    absoluteRun.values().insert(absoluteRun.values().end(),
                                source[i]);
  }
  destination.insert(destination.end(),
                     absoluteRun);
}

void RLE8Compressor::writeRepeatCommand(char repeatChar,
                                          int length,
                                          RLE8CommandCollection& destination) {
  if (length == 0) {
    return;
  }
//  std::cout << "repeat" << std::endl;
  
  // write repeat run
  RLE8Command repeatRun;
  repeatRun.setCommandType(RLE8CommandTypes::repeat);
  repeatRun.setQuantity(length);
  repeatRun.values().insert(repeatRun.values().end(),
                            repeatChar);
  destination.insert(destination.end(),
                     repeatRun);
}

}; 
