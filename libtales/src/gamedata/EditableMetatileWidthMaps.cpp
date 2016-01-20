#include "gamedata/EditableMetatileWidthMaps.h"
#include "exception/UnrecognizedVersionException.h"

namespace Tales {


EditableMetatileWidthMaps::EditableMetatileWidthMaps()
  : EditableMetatileLengthMaps() { };
  
/**
 * Constructor from ROM data.
 * @param rom ROM to load from.
 * @param address Address of metatile length maps.
 * @param numMaps Number of metatile length maps.
 */
EditableMetatileWidthMaps::EditableMetatileWidthMaps(
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
void EditableMetatileWidthMaps::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::metatileWidthMaps,
                   0);
                   
  saveInternal(data);
  
  saver.finalize();
}

/**
 * Loads from a byte array.
 * @param data Byte array to load from.
 * @return The number of bytes read.
 */
int EditableMetatileWidthMaps::load(const Tbyte* data) {
  // Count of loaded bytes
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableMetatileWidthMaps::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::metatileWidthMaps,
                                       "EditableMetatileWidthMaps",
                                       loader.version(),
                                       0);
  }
  
  loadInternal(data,
               byteCount);
  
  return byteCount;
}


};
