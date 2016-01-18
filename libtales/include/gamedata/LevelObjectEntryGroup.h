#ifndef LEVELOBJECTENTRYGROUP_H
#define LEVELOBJECTENTRYGROUP_H


#include "gamedata/LevelObjectEntry.h"
#include "structs/Tbyte.h"
#include <string>
#include <list>

namespace Tales {


// Level objects are kept in a list rather than a vector mostly for editing
// convenience. Using ID numbers like with most other classes doesn't make
// sense here, since this class allows removal of arbitrary elements. Since
// that would invalidate some of the ID numbers, we use a linked list and
// require use of iterators/references instead.
typedef std::list<LevelObjectEntry> LevelObjectEntryCollection;

/**
 * Storage for and access on the LevelObjectEntries for a level.
 * This class only permits restricted access and update operations to keep
 * the objects within the engine limitations (i.e. no more than 64 objects
 * total in any given group).
 */
class LevelObjectEntryGroup {
public:
  /**
   * Maximum group size -- that is, the maximum number of objects in a level.
   * The limiting factor here is the spawned object table, which only has
   * room for 64 entries.
   */
  const static int maxGroupSize = 64;

  /**
   * Default constructor.
   */
  LevelObjectEntryGroup();
  
  /**
   * Constructor from existing data.
   * @param data Byte array to read from.
   */
  LevelObjectEntryGroup(const Tbyte* data);
  
  /**
   * Returns the size in bytes of a list's raw data representation.
   */
  int rawSize();
  
  /**
   * Saves to a string.
   * @data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes to a byte array.
   * @data Byte array to save to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
  
  /**
   * Reads from a byte array.
   * @data Byte array to load from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Appends an entry to the end of the group.
   * @param entry Entry to add to the group.
   */
  void addEntry(const LevelObjectEntry& entry);
  
  /**
   * Erases an entry from the group.
   * @param entryIt Iterator pointing to the entry to remove.
   */
  void eraseEntry(LevelObjectEntryCollection::iterator entryIt);
  
  /**
   * Returns the number of entries in the group.
   * @return The number of entries in the group.
   */
  int size() const;
  
  /**
   * Returns an iterator to the beginning of the group.
   * @return An iterator to the beginning of the group.
   */
  LevelObjectEntryCollection::iterator begin();
  
  /**
   * Returns an iterator to the end of the group.
   * @return An iterator to the end of the group.
   */
  LevelObjectEntryCollection::iterator end();
  
  /**
   * Returns a const_iterator to the beginning of the group.
   * @return A const_iterator to the beginning of the group.
   */
  LevelObjectEntryCollection::const_iterator cbegin() const;
  
  /**
   * Returns a const_iterator to the end of the group.
   * @return A const_iterator to the end of the group.
   */
  LevelObjectEntryCollection::const_iterator cend() const;
  
protected:
  /**
   * Raw list terminator token.
   */
  const static Tbyte terminatorToken = 0xFF;

  /**
   * Storage for object entries.
   */
  LevelObjectEntryCollection entries_;
  
};


};


#endif
