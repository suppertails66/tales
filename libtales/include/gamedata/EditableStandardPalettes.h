#ifndef EDITABLESTANDARDPALETTES_H
#define EDITABLESTANDARDPALETTES_H


#include "gamegear/GGPalette.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>

namespace Tales {


typedef std::vector<GGPalette> StandardPaletteCollection;
/*typedef std::vector<Taddress> StandardPaletteIndexMap;*/

/**
 * Storage for and access on standard palettes of 16 colors.
 */
class EditableStandardPalettes {
public:
  /**
   * Default constructor.
   */
  EditableStandardPalettes();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param baseAddress Address of palette data.
   * @param numEntries Number of palettes at the given address.
   */
  EditableStandardPalettes(LoadedROM& rom,
                           Taddress baseAddress__,
                           int numEntries);
  
  /**
   * Returns number of loaded palettes.
   * @return Number of loaded palettes.
   */
  int size() const;
  
  /**
   * Access on the palette at the given index.
   * @param index Index of the value to access.
   * @return Reference to the value at the given index.
   */
  GGPalette& palette(int index);
  
  /**
   * Const access on the palette at the given index.
   * @param index Index of the value to access.
   * @return Const reference to the value at the given index.
   */
  const GGPalette& palette(int index) const;
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return The number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports data to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
protected:

  /**
   * Address of the palette table for exporting.
   */
  Taddress baseAddress_;
  
  /**
   * Primary storage for palettes.
   */
  StandardPaletteCollection primaryStorage_;
  
  /**
   * Reads palettes from data.
   * @param data Data to read from.
   * @param numPalettes Number of palettes in the data.
   * @return The number of bytes read.
   */
  int readPalettesFromData(const Tbyte* data,
                           int numPalettes);

/*  StandardPaletteIndexMap indexToAddress_; */
  
};


};


#endif
