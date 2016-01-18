#ifndef TWOKEYEDITABLEMAPPEDDATA_H
#define TWOKEYEDITABLEMAPPEDDATA_H


#include "gamedata/BaseEditableMappedData.h"

namespace Tales {


template <class T, class S = T>
class TwoKeyEditableMappedData
    : public BaseEditableMappedData<T,S> {
protected:
  /**
   * Convenience typedef.
   */
  typedef BaseEditableMappedData<T,S> ParentType;
public:
                                  
  /**
   * Reads the address table.
   * Default implementation is for "standard" arrangement of two tables,
   * the first one indexing into the second and the second indexing into
   * the table containing the actual content.
   * @param rom ROM to read from.
   * @param tableHeaderAddress Address of the header table.
   */
  virtual void readAddressTable(LoadedROM& rom,
                                Taddress tableHeaderAddress) {
    // Read address table
    KeyedTableBuilder::buildKeyedAddressTable(
      rom,
      tableHeaderAddress,
      ParentType::mapnumToAddress_);
  }
  
  /**
   * Maps read addresses to indices and stores.
   * Should modify addressToIndex_ and primaryStorage_.
   */
  virtual void prepareIndices() {
    // Iterate over each read address
    for (int i = 0; i < ParentType::mapnumToAddress_.numPrimaryKeys(); i++) {
      for (int j = 0; j < ParentType::mapnumToAddress_.subKeyTable()[i]; j++) {
        // Get the address of the target array
        Taddress address
          = ParentType::mapnumToAddress_.refDataByKeys(
                                           i + TwoKeyedAddress::primaryKeyBase,
                                           j + TwoKeyedAddress::subKeyBase);
                                           
//        std::cout << address << std::endl;
        
        // Add stub entry to primary storage.
        // Since primaryStorage_ is a map, this sorts by address
        // and eliminates duplicate entries
        bool insertSuccessful = (ParentType::addressToIndex_.insert(
          typename ParentType::AddressIndexPair(
            address,
            ParentType::primaryStorage_.size()))).second;
            
        // If insert was successful (not a duplicate), add stub entry to
        // primary storage
        if (insertSuccessful) {
          ParentType::primaryStorage_.push_back(T());
        }
      }
    }
  }
  
public:
//  typedef typename std::vector<T> BaseDataCollection;
//  typedef typename ConstSizeVector<T> DataCollection;

  /**
   * Default constructor.
   */
  TwoKeyEditableMappedData<T,S>()
    : BaseEditableMappedData<T,S>() { };
  
  /**
   * Constructor from data.
   * @param rom ROM to load from.
   * @param tableHeaderAddress Direct address of the table header.
   * @param tableContentAddress Direct address of the table content.
   * @param tableEndAddress Direct address of one past the end of the table.
   * @param subKeyTable Subkey table to use when building address map.
   * @param numPrimaryKeys Number of primary keys in subtable.
   */
  TwoKeyEditableMappedData<T,S>(LoadedROM& rom,
                        Taddress tableHeaderAddress,
                        Taddress tableEndAddress,
                        const int subKeyTable[],
                        int numPrimaryKeys)
  : BaseEditableMappedData<T,S>(rom,
                                tableHeaderAddress,
                                tableEndAddress,
                                subKeyTable,
                                numPrimaryKeys) {
    
  }
  
  /**
   * Returns the internal index of the data for the given map.
   * @param primaryMapNum Primary map number.
   * @param subMapNum Submap number.
   * @return The internal index of the data for the given map.
   */
  int indexOfMapnum(int primaryMapNum,
                    int subMapNum) {
    // Retrieve corresponding address
    Taddress address
      = ParentType::mapnumToAddress_.refDataByKeys(
          primaryMapNum,
          subMapNum);
    
    // Retrieve corresponding index
    return ParentType::addressToIndex_.findValueOrThrow(address);
  }
  
  /**
   * Returns a reference to the data for the given map.
   * @param primaryMapNum Primary map number.
   * @param subMapNum Submap number.
   * @return Reference to the data for the given map.
   */
  T& dataByMapnum(int primaryMapNum,
                  int subMapNum) {
    // Look up index
    int index = indexOfMapnum(primaryMapNum,
                              subMapNum);
    
    return ParentType::dataByIndex(index);
  }
  
protected:
  
  
  
};


};


#endif
