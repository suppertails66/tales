#ifndef EDITABLEMUSICASSIGNMENTS_H
#define EDITABLEMUSICASSIGNMENTS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/PrimaryMaps.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


/**
 * Music assignment table.
 * Maps primary map numbers to sound IDs.
 */
class EditableMusicAssignments {
public:
  /**
   * Number of entries.
   * There seem to be an extra 0xE entries beyond the used primary
   * map keys, all 0x8D (boss music).
   */
//  const static int numEntries = PrimaryMaps::primaryMapTableSize;
  const static int numEntries = 0x25;
  const static int numUsedEntries = PrimaryMaps::primaryMapTableSize;
  
  /**
   * Length of data in bytes.
   */
  const static int dataSize = numEntries;

  /**
   * Default constructor.
   */
  EditableMusicAssignments();

  /**
   * Constructor.
   * @param rom ROM from which to load data.
   * @param address__ Direct (unbanked) address of the data to load.
   */
  EditableMusicAssignments(LoadedROM& rom,
                           int address__);
                           
  /**
   * Copy constructor.
   * @param src Source of copy.
   */
//  EditableMusicAssignments(const EditableMusicAssignments& src);
                           
  /**
   * Copy assignment.
   * @param src Source of copy.
   */
//  EditableMusicAssignments& operator=(const EditableMusicAssignments& src);
  
  /**  
   * Appends a loadable representation of edited state to the given string.
   * @param data A string to which the representation of the altered state
   * should be appended.
   * @see load()
   */
  void save(std::string& data);
  
  /**  
   * Loads edited state from a block of data written using save().
   * @param data A block of raw data corresponding to a previous call to
   * save().
   * @return The number of bytes loaded from the data.
   * @see save()
   */
  int load(const Tbyte* data);
  
  /**  
   * Writes the contained data to a WritableROM.
   * @param rom WritableROM to write data to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Accessor for music assignments.
   * @param primaryMap Number of the primary map to get music assignment for.
   */
  Tbyte& musicAssignment(unsigned int primaryMap);
  
protected:

  Taddress address_;

  /**
   * Array of music assignments.
   * Each position corresponds to a primary map number, with the value being
   * the ID of the sound to play on maps with that primary map number.
   */
  Tbyte musicAssignments_[numEntries];
  
};


};


#endif 
