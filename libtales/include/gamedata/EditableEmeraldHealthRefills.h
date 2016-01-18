#ifndef EDITABLEEMERALDHEALTHREFILLS_H
#define EDITABLEEMERALDHEALTHREFILLS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


class EditableEmeraldHealthRefills {
public:
  /**
   * Returns number of entries in table.
   * @return Number of entries in table.
   */
  int numEntries();

  /**
   * Default constructor.
   */
  EditableEmeraldHealthRefills();

  /**
   * Constructor from ROM.
   * @param rom ROM to read from.
   * @param emeraldHealthRefillTableAddress__ Address of table.
   */
  EditableEmeraldHealthRefills(LoadedROM& rom,
                               Taddress emeraldHealthRefillTableAddress__);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Reads from a raw byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports data to ROM.
   * @param rom WritableROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns reference to the maximum health at the given powerup level.
   * @param powerups Number of power-ups.
   * @return Reference to the maximum health at the given powerup level.
   */
  unsigned int& healthRefillPerEmerald(int powerups);
protected:
  /**
   * Number of power-ups (Chaos Emeralds) in table.
   * Inexplicably, there are 11 entries for the 6 emeralds in the game.
   */
  const static int numEntries_ = 11;
  
  unsigned int healthRefillPerEmerald_[numEntries_];
  
  Taddress emeraldHealthRefillTableAddress_;
  
};


};


#endif
