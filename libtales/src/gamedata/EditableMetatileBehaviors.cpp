#include "gamedata/EditableMetatileBehaviors.h"
#include "exception/TGenericException.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include "structs/Tbyte.h"
#include "gamedata/TailsAdvAddresses.h"
#include <cstring>
#include <string>

using namespace Luncheon;

namespace Tales {


EditableMetatileBehaviors::EditableMetatileBehaviors()
  : address_(0) { };

/*EditableMetatileBehaviors::EditableMetatileBehaviors(
    const EditableMetatileBehaviors& src) {
  // Copy behavior table
  for (int i = 0; i < numEntries; i++) {
    metatileBehaviors_[i] = src.metatileBehaviors_[i];
  }
} */

/*EditableMetatileBehaviors& EditableMetatileBehaviors::operator=(
    const EditableMetatileBehaviors& src) {
  TailsAdvInplaceEditable::operator=(src);
    
  // Copy behavior table
  for (int i = 0; i < numEntries; i++) {
    metatileBehaviors_[i] = src.metatileBehaviors_[i];
  }
  
  // Return self-reference
  return *this;
} */
  
EditableMetatileBehaviors::EditableMetatileBehaviors(
                          LoadedROM& rom,
                          Taddress address__)
  : address_(address__) {
  for (int i = 0; i < numEntries; i++) {
    // Buffer to hold raw data
    Tbyte buffer[MetatileBehavior::dataSize];
    
    // Copy raw data
    std::memcpy(buffer,
                rom.directRead(address_ + (i * MetatileBehavior::dataSize)),
                MetatileBehavior::dataSize);
    
    // Convert to behavior entry
    metatileBehaviors_[i].readFromData(buffer);
  }
}

void EditableMetatileBehaviors::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::metatileBehaviors,
                   0);

  // Save address
  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  for (int i = 0; i < numEntries; i++) {
    // Temporary buffer to hold data
    Tbyte behavior[MetatileBehavior::dataSize];
    
    // Write data
    metatileBehaviors_[i].writeToData(behavior);
    
    // Append to string
    data += (std::string((char*)behavior, MetatileBehavior::dataSize));
  }
  
  saver.finalize();
}

int EditableMetatileBehaviors::load(const Tbyte* data) {
  // Count of bytes read
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableMetatileBehaviors::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::metatileBehaviors,
                                       "EditableMetatileBehaviors",
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
 
  for (int i = 0; i < numEntries; i++) {
    // Read each behavior from data
    metatileBehaviors_[i].readFromData(data + (byteCount));
    byteCount += MetatileBehavior::dataSize;
  }
  
  // Return count of bytes read
  return byteCount;
}

void EditableMetatileBehaviors::exportToROM(WritableROM& rom) {
  for (int i = 0; i < numEntries; i++) {
    // Write behaviors
    metatileBehaviors_[i].writeToData(
      rom.directWrite(address_ + (i * MetatileBehavior::dataSize)));
  }
}

MetatileBehavior& EditableMetatileBehaviors::metatileBehavior(
    unsigned int index) {
  // Throw if index out of range
  if (index > (unsigned int)numEntries) {
    throw TGenericException(TALES_SRCANDLINE,
                           "EditableMetatileBehaviors::metatileBehavior("
                           "unsigned int)",
                           std::string("Out-of-range index: ")
                           + StringConversion::toString(index));
  }
  
  // Return requested metatile
  return metatileBehaviors_[index];
}

const MetatileBehavior& EditableMetatileBehaviors
    ::metatileBehavior(unsigned int index) const {
  // Throw if index out of range
  if (index > (unsigned int)numEntries) {
    throw TGenericException(TALES_SRCANDLINE,
                           "EditableMetatileBehaviors::metatileBehavior("
                           "unsigned int) const",
                           std::string("Out-of-range index: ")
                           + StringConversion::toString(index));
  }
  
  // Return requested metatile
  return metatileBehaviors_[index];
}


}; 
