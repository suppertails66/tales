#ifndef EDITABLEMETATILEBEHAVIORS_H
#define EDITABLEMETATILEBEHAVIORS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/MetatileBehavior.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


class EditableMetatileBehaviors {
public:
  /**
   * Number of entries in the metatile behavior table.
   */
  const static int numEntries = 0x100;
  
  /**
   * Total size of the metatile behavior table.
   */
  const static int dataSize = numEntries * MetatileBehavior::dataSize;

  /**
   * Default constructor.
   */
  EditableMetatileBehaviors();
  
  /**
   * Copy constructor.
   * @param src Source of copy.
   */
//  EditableMetatileBehaviors(const EditableMetatileBehaviors& src);
                           
  /**
   * Copy assignment.
   * @param src Source of copy.
   */
//  EditableMetatileBehaviors& operator=(const EditableMetatileBehaviors& src);

  /**
   * Construct from ROM data.
   * @param rom ROM to load from.
   * @param address Address of metatile behavior table content.
   */
  EditableMetatileBehaviors(LoadedROM& rom,
                            Taddress address__);
  
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
   * Accessor for metatile behaviors.
   */
  MetatileBehavior& metatileBehavior(unsigned int index);
  
  /**
   * Const accessor for metatile behaviors.
   */
  const MetatileBehavior& metatileBehavior(unsigned int index) const;
 
protected:

  Taddress address_;
  
  /**
   * Table of metatile behaviors, keyed by metatile ID.
   */
  MetatileBehavior metatileBehaviors_[numEntries];
  
};


};


#endif 
