#ifndef MAPLAYOUT_H
#define MAPLAYOUT_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include <string>

namespace Tales {


/**
 * Represents the layout and basic attributes of a map.
 * This structure actually incorporates attributes from the level headers
 * in order to simplify the logical structure of the data. In "vanilla"
 * Tails Adventures, no level headers ever specify the same map with
 * different parameters (camera limits, metatile structures...). Thus, we 
 * don't lose any information by incorporating those into the map layout
 * itself. We do lose the potential to make such edits ourselves, but
 * since it's pretty much useless anyway it's probably worth the trade-off.
 */
class MapLayout {
public:
  /**
   * Size in bytes of uncompressed map data.
   */
  const static int dataSize = 4095;

  /**
   * Actual size of the uncompressed map data buffer.
   * Some map layouts actually specify more data than the map buffer
   * can fit, leaving the bottom part of the level unseen. Assigning extra
   * space lets us investigate that data.
   */
  const static int actualStorageSize = dataSize * 2;
  
  /**
   * Default constructor.
   */
  MapLayout();
  
  /**
   * Constructor from data.
   * @param rom ROM to load from.
   * @param address Address of the data to load.
   */
  MapLayout(LoadedROM& rom,
                    Taddress address__);
                    
  /**
   * Loads map from ROM.
   * @param rom ROM to load from.
   * @param address Address of the data to load.
   */
  void readFromData(LoadedROM& rom,
                    Taddress address__);
  
  /**
   * Saves map to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads map from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes loaded.
   */
  int load(const Tbyte* data);
  
  /**
   * Finds a free space in the ROM and saves map data to it.
   * When this function is called, it compresses the map and first tries
   * to write it to the position in ROM from which it was loaded. If the
   * compressed data will not fit in that location, the function will
   * try to find a free space from the WritableROM's free space list
   * that is large enough to hold it. If it succeeds, it writes the data
   * and updates the address_ and compressedSize_ parameters (for reference
   * when exporting level headers); if it fails, it throws a
   * NotEnoughSpaceException.
   * @param rom ROM to write to.
   * @throws NotEnoughSpaceException
   */
  void exportToFreeROM(WritableROM& rom);
  
  /**
   * Returns the metatile at the given position.
   * This corresponds to (x * y), but since the width is stored
   * externally, the caller is responsible for getting it right.
   * @param index Index into the layout array.
   * @return Value at the given index.
   */
  Tbyte getMetatile(int index) const;
  
  /**
   * Sets the metatile at the given position.
   * This corresponds to (x * y), but since the width is stored
   * externally, the caller is responsible for getting it right.
   * @param index Index into the layout array.
   * @param value Value to set at the index.
   */
  void setMetatile(int index, Tbyte value);
  
  /**
   * Access on layout array.
   * @param index Index into the layout array.
   * @return Reference to the given position in the layout array.
   */
  Tbyte& operator[](int index);
  
  /**
   * Const access on layout array.
   * @param index Index into the layout array.
   * @return Reference to the given position in the layout array.
   */
  const Tbyte& operator[](int index) const;
  
  /**
   * Returns the last known address of the compressed map data.
   * @return The last known address of the compressed map data.
   */
  Taddress address() const;
  
  /**
   * Returns the last known size of the compressed map data.
   * @return The last known size of the compressed map data.
   */
  Taddress compressedSize() const;
  
protected:
  
  /**
   * Raw layout data.
   */
  Tbyte layout_[actualStorageSize];
  
  /**
   * The address of this map in the ROM.
   * Note that this can change when the map is exported to ROM.
   * @see exportToROM()
   */
  Taddress address_;
  
  /**
   * The compressed length, in bytes, of this map in the ROM.
   * Note that this can change when the map is exported to ROM.
   * @see exportToROM()
   */
  int compressedSize_;
  
};


};


#endif 
