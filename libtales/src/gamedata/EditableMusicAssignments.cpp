#include "gamedata/EditableMusicAssignments.h"
#include "util/StringConversion.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/TGenericException.h"
#include "exception/UnrecognizedVersionException.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableMusicAssignments::EditableMusicAssignments()
  : address_(0) { };
  
EditableMusicAssignments::EditableMusicAssignments(
                         LoadedROM& rom,
                         int address__)
  : address_(address__) {
  // Copy table from ROM
  std::memcpy(musicAssignments_,
              rom.directRead(address__),
              dataSize);
}

/*EditableMusicAssignments::EditableMusicAssignments(
      const EditableMusicAssignments& src) {
  // Copy table
  std::memcpy(musicAssignments_,
              src.musicAssignments_,
              dataSize);
} */

/*EditableMusicAssignments& EditableMusicAssignments::operator=(
      const EditableMusicAssignments& src) {
  
  // Call parent assignment operator
  TailsAdvInplaceEditable::operator=(*this);
  
  // Copy table
  std::memcpy(musicAssignments_,
              src.musicAssignments_,
              dataSize);

  // Return self-reference
  return *this;
} */

void EditableMusicAssignments::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::musicAssignments,
                   0);

  // Save address
  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  // Copy table to string
  for (int i = 0; i < numEntries; i++) {
    data += StringConversion::toString(musicAssignments_[i]);
  }
  
  saver.finalize();
}

int EditableMusicAssignments::load(const Tbyte* data) {
  // Count of bytes read
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableMusicAssignments::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::musicAssignments,
                                       "EditableMusicAssignments",
                                       loader.version(),
                                       0);
  }
  
  // Load address
  address_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;

  // Read assignments
  for (int i = 0; i < numEntries; i++) {
    musicAssignments_[i]
      = (Tbyte)(ByteConversion::fromBytes(data + byteCount,
                                          ByteSizes::uint8Size,
                                          EndiannessTypes::little,
                                          SignednessTypes::nosign));
    byteCount += ByteSizes::uint8Size;
  }
  
  // Return count of bytes read
  return byteCount;
}

void EditableMusicAssignments::exportToROM(WritableROM& rom) {
  // Copy table to address
  rom.directWrite(address_,
                  musicAssignments_,
                  dataSize);
}

Tbyte& EditableMusicAssignments::musicAssignment(unsigned int primaryMap) {
  // Throw if key is out of range
  if (primaryMap > (unsigned int)numEntries) {
    throw TGenericException(TALES_SRCANDLINE,
                           "EditableMusicAssignments::musicAssignments(int)",
                           std::string("Out of range index: ")
                           + StringConversion::toString(primaryMap));
  }
  
  return musicAssignments_[primaryMap];
}


}
