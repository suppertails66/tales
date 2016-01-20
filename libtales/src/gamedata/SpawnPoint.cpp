#include "gamedata/SpawnPoint.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


SpawnPoint::SpawnPoint()
  : camX_(0),
    camY_(0),
    tailsX_(0),
    tailsY_(0) { };

SpawnPoint::SpawnPoint(const Tbyte* data)
  : camX_(0),
    camY_(0),
    tailsX_(0),
    tailsY_(0) {
  readFromData(data);
}

int SpawnPoint::readFromData(const Tbyte* data) {
  // Read all fields
  camX_ = ByteConversion::fromBytes(
                  data + 0,
                  ByteSizes::int16Size,
                  EndiannessTypes::little,
                  SignednessTypes::sign);
  
  camY_ = ByteConversion::fromBytes(
                  data + 2,
                  ByteSizes::int16Size,
                  EndiannessTypes::little,
                  SignednessTypes::sign);
  
  tailsX_ = ByteConversion::fromBytes(
                  data + 4,
                  ByteSizes::int16Size,
                  EndiannessTypes::little,
                  SignednessTypes::sign);
  
  tailsY_ = ByteConversion::fromBytes(
                  data + 6,
                  ByteSizes::int16Size,
                  EndiannessTypes::little,
                  SignednessTypes::sign);
  
  return dataSize;
}

void SpawnPoint::writeToData(Tbyte* data) {
  // Write each field
  ByteConversion::toBytes(
                    camX_,
                    data + 0,
                    ByteSizes::int16Size,
                    EndiannessTypes::little,
                    SignednessTypes::sign);
                    
  ByteConversion::toBytes(
                    camY_,
                    data + 2,
                    ByteSizes::int16Size,
                    EndiannessTypes::little,
                    SignednessTypes::sign);
                    
  ByteConversion::toBytes(
                    tailsX_,
                    data + 4,
                    ByteSizes::int16Size,
                    EndiannessTypes::little,
                    SignednessTypes::sign);
                    
  ByteConversion::toBytes(
                    tailsY_,
                    data + 6,
                    ByteSizes::int16Size,
                    EndiannessTypes::little,
                    SignednessTypes::sign);
}

int SpawnPoint::load(const Tbyte* data) {
  readFromData(data);
  
  return dataSize;
}

void SpawnPoint::save(std::string& data) {
  // Output buffer
  Tbyte buffer[dataSize];
  
  // Get raw data
  writeToData(buffer);
  
  // Append to string
  data += std::string((char*)buffer, dataSize);
}

int SpawnPoint::camX() const {
  return camX_;
}

int SpawnPoint::camY() const {
  return camY_;
}

int SpawnPoint::tailsX() const {
  return tailsX_;
}

int SpawnPoint::tailsY() const {
  return tailsY_;
}

void SpawnPoint::setCamX(int camX__) {
  camX_ = camX__;
}

void SpawnPoint::setCamY(int camY__) {
  camY_ = camY__;
}

void SpawnPoint::setTailsX(int tailsX__) {
  tailsX_ = tailsX__;
}

void SpawnPoint::setTailsY(int tailsY__) {
  tailsY_ = tailsY__;
}


};
