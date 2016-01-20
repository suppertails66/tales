#ifndef EDITABLELEVELOBJECTENTRYGROUPS_H
#define EDITABLELEVELOBJECTENTRYGROUPS_H


#include "structs/Taddress.h"
#include "gamedata/LevelObjectEntryGroup.h"
#include "gamedata/TwoKeyIndexedEditableMappedData.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <vector>

namespace Tales {


class EditableLevelObjectEntryGroups
    : public TwoKeyIndexedEditableMappedData<LevelObjectEntryGroup> {
public:
  /**
   * Default constructor.
   */
  EditableLevelObjectEntryGroups();
  
  /**
   * Constructor.
   */
  EditableLevelObjectEntryGroups(LoadedROM& rom,
                           Taddress tableHeaderAddress,
                           Taddress tableContentAddress,
                           Taddress tableEndAddress,
                           int numEntries);
  
  /**
   * Returns the maximum total number of objects allowed.
   * This is limited by the capacity of a single ROM bank; we must
   * have enough room for both the address table and all the object entries
   * in each group.
   */
  static int maxTotalEntries();
  
  /**
   * Returns the total number of objects in all groups.
   * @return The total number of objects in all groups.
   */
  int totalEntries();
  
  /**
   * Returns the number of objects in a groups.
   * @param groupIndex Index number of the group.
   * @return The number of objects in a groups.
   */
  int groupSize(int groupIndex);
  
  /**
   * Adds an entry to the group with the specified index.
   * @param groupIndex Index number of the group.
   * @param entry Entry to add to the group.
   */
  void addEntry(int groupIndex,
                const LevelObjectEntry& entry);
  
  /**
   * Erases an entry from the group with the specified index.
   * @param groupIndex Index number of the group.
   * @param entryIt Iterator pointing to entry to remove.
   */
  void eraseEntry(int groupIndex,
                  const LevelObjectEntryCollection::iterator& entryIt);
                  
  LevelObjectEntryGroup& group(int groupIndex);
  
  const LevelObjectEntryGroup& group(int groupIndex) const;
  
  /**
   * Returns a LevelObjectEntryCollection::iterator to the start of a group.
   * @param groupIndex Index number of the group.
   * @return A LevelObjectEntryCollection::iterator to the start of a group.
   */
  LevelObjectEntryCollection::iterator groupBegin(int groupIndex);
  
  /**
   * Returns a LevelObjectEntryCollection::iterator to the end of a group.
   * @param groupIndex Index number of the group.
   * @return A LevelObjectEntryCollection::iterator to the end of a group.
   */
  LevelObjectEntryCollection::iterator groupEnd(int groupIndex);
  
  /**
   * Returns a const_iterator to the start of a group.
   * @param groupIndex Index number of the group.
   * @return A const_iterator to the start of a group.
   */
  LevelObjectEntryCollection::const_iterator groupCbegin(int groupIndex)
      const;
  
  /**
   * Returns a const_iterator to the end of a group.
   * @param groupIndex Index number of the group.
   * @return A const_iterator to the end of a group.
   */
  LevelObjectEntryCollection::const_iterator groupCend(int groupIndex)
      const;
  
//  virtual void prepareIndices();
               
//  LevelObjectEntryGroup& groupsByMapnum(int primaryMapNum,
//                                      int subMapNum);

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
   * Writes data to ROM.
   * Re-implemented from BaseEditableMappedData. Since we allow groups to be
   * expanded, we have to rewrite the address table and/or shift the table
   * in ROM to accomodate the expanded size, which the basic implementation
   * doesn't do.
   * TODO: implement this
   * @param rom ROM to write to.
   */
  virtual void exportToROM(WritableROM& rom);
  
protected:

  /**
   * Maximum number of object entries allowed in total.
   * To skip more extensive hacking, we copy the code
   * and data in the first 0x54E bytes of the bank.
   * The table header takes 0x7A bytes of space, and each of the 0x27
   * lists requires one extra byte apiece for its terminator.
   * That totals to 0x1EF used bytes, leaving us with 0x3A11 bytes
   * of free space for objects, or 0x673 total entries (1651 base 10).
   * We leave some wiggle room "just in case".
   */
  const static int maxTotalEntries_ = 1645;

  /**
   * The highest allowable primary map number, plus one.
   */
  const static int primaryMapLimit = 0x16;
  
  /**
   * The address in ROM of a byte indicating the bank number of this table.
   * Specifically, this is the address of the instruction that sets the bank
   * number when the game needs to examine the object list.
   * We need to update this if we move the table during export to ROM.
   *
   * This refers to a section of code arbitrarily termed "C1", which appears
   * at 0x70000 in ROM and refers to the object table.
   */
  const static Taddress callReferenceToC1Bank = 0x131D;
  
  /**
   * Address of code containing address of "C1" code segment.
   */
  const static Taddress callReferenceToC1Address = 0x1322;
  
  /**
   * Address of code containing bank number of "C3" code segment.
   * This refers to a section of code arbitrarily termed "C3", which appears
   * at 0x71FF3 in ROM and refers to the object table.
   */
  const static Taddress callReferenceToC3Bank = 0x62B7;
  
  /**
   * Address of code containing address of "C3" code segment.
   */
  const static Taddress callReferenceToC3Address = 0x62B3;
  
  /**
   * Address of "C1" code segment.
   */
  const static Taddress addressOfC1Segment = 0x70000;
  
  /**
   * Length of "C1" code segment.
   */
//  const static Taddress lengthOfC1Segment = 0xD6;
  const static Taddress lengthOfC1Segment = 0x54F;
  
  /**
   * Address of "C3" code segment.
   */
  const static Taddress addressOfC3Segment = 0x71FF3;
  
  /**
   * Length of "C3" code segment.
   */
  const static Taddress lengthOfC3Segment = 0xFD;
  
  /**
   * Offset from start of "C1" segment referring to the object table.
   * This address must be adjusted if C1 is moved.
   */
  const static int offsetOfTableReferenceInC1
    = 0x70008 - addressOfC1Segment;
  
  /**
   * Offset from start of "C3" segment referring to the object table.
   * This address must be adjusted if C3 is moved.
   */
  const static int offsetOfTableReferenceInC3
    = 0x71FFB - addressOfC3Segment;
  
  /**
   * Address of explicit JP instruction in "C3" code segment.
   * If we move C3, we have to modify this instruction to jump
   * to the new location.
   */
  const static Taddress addressOfJpAddressInC3 = 0x72038;
  
  /**
   * Offset of addressOfJpAddressInC3.
   */
  const static int offsetOfJpInC3
    = addressOfJpAddressInC3 - addressOfC3Segment;
  
  /**
   * Base address from which to jump from addressOfJpAddressInC3.
   * This is the address of the next instruction after the JP, i.e.
   * the base point for the jump.
   */
  const static int baseOffsetOfJpInC3
    = 0x7203A - addressOfC3Segment;
  
  /**
   * Target of jump given by addressOfJpAddressInC3.
   */
  const static int targetOffsetOfJpInC3
    = 0x72017 - addressOfC3Segment;
  
  /**
   * Absolute (non-negative) length of the jump in "C3" code segment.
   */
  const static int absoluteLengthOfJpInC3
      = baseOffsetOfJpInC3 - targetOffsetOfJpInC3;
      
  /**
   * Copy of "C1" for exporting.
   */
  Tbyte codeSegmentC1[lengthOfC1Segment];
      
  /**
   * Copy of "C2" for exporting.
   */
  Tbyte codeSegmentC3[lengthOfC3Segment];
  
  /**
   * The address in ROM of the first byte of the source bank for this table.
   */
//  const static Taddress bankDataCopyAddress = 0x70000;
  
  /**
   * The amount of data in bytes to copy when moving to a new bank.
   */
//  const static int bankDataCopyLength = 0x14F;
  
  /**
   * Offset from start of bank at which to write table in new bank.
   */
//  const static int bankTableWriteOffset = 0x54F;
  
  bool movedToNewBank_;
  
  int tableHeaderSize_;
  
  int initialTableAddress_;
  
  int initialTableContentSize_;
  
  /**
   * Moves to a new bank.
   * @param rom ROM to write changes to.
   * @return The new export address of the address table.
   */
  Taddress moveToNewBank(WritableROM& rom);
  
  void exportTable(Taddress exportAddress,
                   WritableROM& rom);
  
  /**
   * Returns the total exported size of all object entry groups.
   * @return The total exported size of all object entry groups.
   */
  int totalExportedSize();

  virtual void readAndConstructReadStep(LoadedROM& rom,
                                        Taddress tableEndAddress);

  /**
   * Returns the data size of a single storage element.
   * @return The data size of a single storage element.
   */
  // TODO: remove; this is unused and doesn't need to be here
  virtual int dataSizeOfOneElement();
  
  /**
   * Reads (numElements) instances of an S from data and stores in dst.
   * @param dst S in which to place read data.
   * @param data Raw data source.
   * @param numElements Number of elements to read from data. Default is 1.
   * @return Number of bytes of data read.
   */
  virtual int readElements(LevelObjectEntryGroup& dst,
                           const Tbyte* data,
                           int numElements = 1);
  
  /**
   * Writes a T to a string.
   * @param data String to write to.
   * @param src T to write to data.
   */
  virtual void saveElement(std::string& data,
                           LevelObjectEntryGroup& src);
  
  /**
   * Reads an S from a previously saved byte array.
   * @param dst S to write to.
   * @param data Byte array to read from.
   */
  virtual int loadElement(LevelObjectEntryGroup& dst,
                          const Tbyte* data);
  
  /**
   * Exports a T to ROM.
   * @param rom ROM to write to.
   * @param address Address in ROM to write to.
   * @param src T to write to ROM.
   */
  virtual void exportElementToROM(WritableROM& rom,
                                  Taddress address,
                                  LevelObjectEntryGroup& src);
  
  virtual DataChunkIDs::DataChunkID dataChunkID();
  
  virtual std::string dataChunkName();
  
  virtual int chunkVersionNumber();
  
  virtual int maxRecognizedVersionNumber();
  
};


};


#endif
