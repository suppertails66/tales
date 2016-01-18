#ifndef WARPDESTINATION_H
#define WARPDESTINATION_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamedata/PrimaryMaps.h"
#include "gamegear/LoadedROM.h"
#include <string>

namespace Tales {


class WarpDestination {
public:
  /**
   * Size of raw data representation.
   */
  const static int dataSize = 5;
  
  /**
   * Number of unlockable levels.
   * Levels unlocked by a warp are stored in a 16-bit bitfield, so the
   * maximum representable value is 15. Higher values are invalid.
   * Note that the practical limit is 12, as the valid primary map numbers
   * are 1 through 11, inclusive.
   */
  const static int numUnlockableLevels = 0x10;
  
  /**
   * Index of the minimum unlockable level.
   */
  const static int minUnlockableLevel
    = static_cast<int>(PrimaryMaps::poloyForest);
  
  /**
   * Index of the maximum unlockable level.
   */
  const static int maxUnlockableLevel
    = static_cast<int>(PrimaryMaps::battleFortress);
  
  /**
   * Default constructor.
   */
  WarpDestination();
  
  /**
   * Constructor from byte array
   * @param data Byte array to load from
   */
  WarpDestination(const Tbyte* data);
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param address Address in ROM to load from.
   */
  WarpDestination(LoadedROM& rom,
                  Taddress address);
  
  /**
   * Reads data from byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Writes data to byte array.
   * @param data Byte array to write to.
   * @return Number of bytes written.
   */
  void writeToData(Tbyte* data);
  
  /**
   * Loads from byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Saves to string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Returns true if the given level is to be unlocked.
   * @param primaryMapNum Number of the primary map to check.
   * @return True if the given level is to be unlocked.
   */
  bool levelUnlocked(PrimaryMaps::PrimaryMap primaryMapNum) const;
  
  /**
   * Sets whether the given level is to be unlocked.
   * @param primaryMapNum Number of the primary map to alter.
   * @param unlockStatus True if the level should be unlocked when this
   * warp is taken, false otherwise.
   */
  void setLevelUnlocked(PrimaryMaps::PrimaryMap primaryMapNum,
                        bool unlockStatus);
  
  /**
   * Getter.
   */
  PrimaryMaps::PrimaryMap primaryMapDestination() const;
  
  /**
   * Getter.
   */
  int subMapDestination() const;
  
  /**
   * Getter.
   */
  int destinationSpawnIndex() const;
  
  /**
   * Setter.
   */
  void setPrimaryMapDestination(
    PrimaryMaps::PrimaryMap primaryMapDestination__);
  
  /**
   * Setter.
   */
  void setSubMapDestination(int subMapDestination__);
  
  /**
   * Setter.
   */
  void setDestinationSpawnIndex(int destinationSpawnIndex__);
  
protected:

  /**
   * Primary map number to go to when this warp is taken.
   */
  PrimaryMaps::PrimaryMap primaryMapDestination_;

  /**
   * Submap number to go to when this warp is taken.
   */
  int subMapDestination_;

  /**
   * Index of the spawn position for the specified map to start at.
   */
  int destinationSpawnIndex_;

  /**
   * Array of levels to be unlocked when this warp is taken.
   * These are indexed by primary map numbers minus one. "true" indicates
   * the level is to be unlocked, "false" means it remains in its current state
   * (locked or unlocked).
   */
  bool levelsUnlocked_[numUnlockableLevels];
  
};


};


#endif
