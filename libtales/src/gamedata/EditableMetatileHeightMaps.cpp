#include "gamedata/EditableMetatileHeightMaps.h"
#include "exception/UnrecognizedVersionException.h"

namespace Tales {


EditableMetatileHeightMaps::EditableMetatileHeightMaps()
  : EditableMetatileLengthMaps() { };
  
/**
 * Constructor from ROM data.
 * @param rom ROM to load from.
 * @param address Address of metatile length maps.
 * @param numMaps Number of metatile length maps.
 */
EditableMetatileHeightMaps::EditableMetatileHeightMaps(
                        LoadedROM& rom,
                        Taddress baseAddress,
                        int numMaps)
  : EditableMetatileLengthMaps(rom,
                               baseAddress,
                               numMaps) { };

/**
 * Saves to a string.
 * @param data String to save to.
 */
void EditableMetatileHeightMaps::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::metatileHeightMaps,
                   0);
                   
  saveInternal(data);
  
  saver.finalize();
}

/**
 * Loads from a byte array.
 * @param data Byte array to load from.
 * @return The number of bytes read.
 */
int EditableMetatileHeightMaps::load(const Tbyte* data) {
  // Count of loaded bytes
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableMetatileHeightMaps::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::metatileHeightMaps,
                                       "EditableMetatileHeightMaps",
                                       loader.version(),
                                       0);
  }
  
  loadInternal(data,
               byteCount);
  
  return byteCount;
}


};
