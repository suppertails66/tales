#include "gamedata/MetatileStructure.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


MetatileStructure::MetatileStructure() { };

MetatileStructure::MetatileStructure(
                          unsigned int upperLeft__,
                          unsigned int upperRight__,
                          unsigned int lowerLeft__,
                          unsigned int lowerRight__)
  : upperLeft_(upperLeft__),
    upperRight_(upperRight__),
    lowerLeft_(lowerLeft__),
    lowerRight_(lowerRight__) { };

MetatileStructure::MetatileStructure(
                          TileReference upperLeft__,
                          TileReference upperRight__,
                          TileReference lowerLeft__,
                          TileReference lowerRight__)
  : upperLeft_(upperLeft__),
    upperRight_(upperRight__),
    lowerLeft_(lowerLeft__),
    lowerRight_(lowerRight__) { };

void MetatileStructure::writeToData(Tbyte* data) {
  // Output value
  unsigned int output = 0;
  
  // Convert upper-left tile to VRAM identifier
  output = upperLeft_.toRawIdentifier();
  
//  std::cerr << "ul: " << output << std::endl;
  
  // Write to data
  ByteConversion::toBytes(output,
                          data + 0,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
                          
  // Repeat for other tiles
  
  output = upperRight_.toRawIdentifier();
  ByteConversion::toBytes(output,
                          data + 2,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
//  std::cerr << "ur: " << output << std::endl;
                          
  output = lowerLeft_.toRawIdentifier();
  ByteConversion::toBytes(output,
                          data + 4,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
//  std::cerr << "ll: " << output << std::endl;
                          
  output = lowerRight_.toRawIdentifier();
  ByteConversion::toBytes(output,
                          data + 6,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
//  std::cerr << "lr: " << output << std::endl;
}

int MetatileStructure::readFromData(const Tbyte* data) {
  // Read each VRAM indicator
  
  unsigned int ul = ByteConversion::fromBytes(
                        data + 0,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  unsigned int ur = ByteConversion::fromBytes(
                        data + 2,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  unsigned int ll = ByteConversion::fromBytes(
                        data + 4,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  unsigned int lr = ByteConversion::fromBytes(
                        data + 6,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  // Assign to tiles
  upperLeft_ = TileReference(ul);
  upperRight_ = TileReference(ur);
  lowerLeft_ = TileReference(ll);
  lowerRight_ = TileReference(lr);
  
  return dataSize;
}

TileReference& MetatileStructure::upperLeft() {
  return upperLeft_;
}

TileReference& MetatileStructure::upperRight() {
  return upperRight_;
}

TileReference& MetatileStructure::lowerLeft() {
  return lowerLeft_;
}

TileReference& MetatileStructure::lowerRight() {
  return lowerRight_;
}

/*TileReference MetatileStructure::upperLeft() const {
  return upperLeft_;
}

TileReference MetatileStructure::upperRight() const {
  return upperRight_;
}

TileReference MetatileStructure::lowerLeft() const {
  return lowerLeft_;
}

TileReference MetatileStructure::lowerRight() const {
  return lowerRight_;
}

void MetatileStructure::setUpperLeft(TileReference upperLeft__) {
  upperLeft_ = upperLeft__;
}

void MetatileStructure::setUpperRight(TileReference upperRight__) {
  upperRight_ = upperRight__;
}

void MetatileStructure::setLowerLeft(TileReference lowerLeft__) {
  lowerLeft_ = lowerLeft__;
}

void MetatileStructure::setLowerRight(TileReference lowerRight__) {
  lowerRight_ = lowerRight__;
} */


}; 
