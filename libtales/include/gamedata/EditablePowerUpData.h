#ifndef EDITABLEPOWERUPDATA_H
#define EDITABLEPOWERUPDATA_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


class EditablePowerUpData {
public:
  /**
   * Returns number of power-ups (Chaos Emeralds) in table.
   * @return Number of power-ups (Chaos Emeralds) in table.
   */
  int numPowerUps();
  
  /**
   * Returns maximum possible amount of health that can be specified.
   */
  const static unsigned int maxHealthTotal();
  
  /**
   * Returns maximum possible flight time that can be specified.
   */
  const static unsigned int maxFlightTimeTotal();

  /**
   * Default constructor.
   */
  EditablePowerUpData();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   */
  EditablePowerUpData(LoadedROM& rom,
                      Taddress powerUpTableAddress__);
  
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
  unsigned int& maxHealthPerPowerup(int powerups);
  
  /**
   * Returns reference to the flight time at the given powerup level.
   * @param powerups Number of power-ups.
   * @return Reference to the flight time at the given powerup level.
   */
  unsigned int& flightTimePerPowerup(int powerups);
  
protected:
  /**
   * Number of power-ups (Chaos Emeralds) in table.
   * There are 7 entries despite the fact that this game only has
   * 6 emeralds, so maybe they were thinking about having them all.
   */
  const static int numPowerUps_ = 7;
  
  /**
   * Maximum legal amount of health.
   * The health value for the HUD uses binary-coded decimal, so
   * the reasonable limit is 99 (the counter will spin infinitely
   * if HP exceeds this value). Technically it's possible to specify
   * higher values -- in fact, the game actually seems to have an
   * anti-cheating protection that prevents the ending from triggering
   * if the player has more than 248 health.
   */
  const static int maxHealthTotal_ = 99;
  
  /**
   * Maximum legal amount of flight time.
   * No joke -- going higher than this causes the routine that draws
   * the flight meter to go wacky and start corrupting graphics.
   */
  const static int maxFlightTimeTotal_ = 0x0C04;
  
  /**
   * Sets the max amount of health for each powerup level.
   * Entry 0 = power for 0 emeralds, 1 = 1 emerald, etc.
   */
  unsigned int maxHealthPerPowerup_[numPowerUps_];
  
  /**
   * Sets the starting flight time for each powerup level.
   * Entry 0 = flight time for 0 emeralds, 1 = 1 emerald, etc.
   */
  unsigned int flightTimePerPowerup_[numPowerUps_];
  
  Taddress powerUpTableAddress_;
};


};


#endif
