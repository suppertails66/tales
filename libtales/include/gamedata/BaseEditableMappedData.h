#ifndef BASEEDITABLEMAPPEDDATA_H
#define BASEEDITABLEMAPPEDDATA_H


#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/ConstSizeVector.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/KeyedTableBuilder.h"
#include <string>
#include <vector>
#include <iostream>

namespace Tales {


/**
 * Templated base class for storing and accessing generically tabled data.
 * @param T The primary storage class.
 * @param S A temporary storage class used during reading. Intended for reading
 * arrays into special vector-like classes that cannot be expanded. Defaults to
 * T if unspecified.
 */
template <class T, class S = T>
class BaseEditableMappedData {
protected:
  typedef Tmap<Taddress, int> AddressIndexMap;
  typedef std::vector<T> IndexDataMap;
  typedef typename AddressIndexMap::PairType AddressIndexPair;
//  typedef Tmap<Taddress, T> AddressDataMap;
//  typedef typename AddressDataMap::PairType AddressDataPair;
  
  /**
   * Returns the data size of a single storage element.
   */
  virtual int dataSizeOfOneElement() =0;
  
  /**
   * Reads (numElements) instances of an S from data and stores in dst.
   * @param dst S in which to place read data.
   * @param data Raw data source.
   * @param numElements Number of elements to read from data. Default is 1.
   * @return Number of bytes of data read.
   */
  virtual int readElements(S& dst,
                           const Tbyte* data,
                           int numElements = 1) =0;
  
  /**
   * Writes a T to a string.
   * @param data String to write to.
   * @param src T to write to data.
   */
  virtual void saveElement(std::string& data,
                            T& src) =0;
  
  /**
   * Reads an S from a previously saved byte array.
   * @param dst S to write to.
   * @param data Byte array to read from.
   */
  virtual int loadElement(S& dst,
                          const Tbyte* data) =0;
  
  /**
   * Exports a T to ROM.
   * @param rom ROM to write to.
   * @param address Address in ROM to write to.
   * @param src T to write to ROM.
   */
  virtual void exportElementToROM(WritableROM& rom,
                                  Taddress address,
                                  T& src) =0;
                                  
  /**
   * Reads the address table.
   * Default implementation is for "standard" arrangement of two tables,
   * the first one indexing into the second and the second indexing into
   * the table containing the actual content.
   * @param rom ROM to read from.
   * @param tableHeaderAddress Address of the header table.
   */
  virtual void readAddressTable(LoadedROM& rom,
                                Taddress tableHeaderAddress) =0;
  
  /**
   * Maps read addresses to indices and stores.
   * Should modify addressToIndex_ and primaryStorage_.
   */
  virtual void prepareIndices() =0;
  
  virtual DataChunkIDs::DataChunkID dataChunkID() =0;
  
  virtual std::string dataChunkName() =0;
  
  virtual int chunkVersionNumber() =0;
  
  virtual int maxRecognizedVersionNumber() =0;

  /**
   * This must be called in derived classes' constructors.
   * It constructs the object using the abstract read functions.
   * It can't be called from the base class's constructor because
   * that can't call virtual members. This leaves us with the option
   * of either declaring a new "intermediate" derived class serving
   * no purpose except to call this function in its constructor, or
   * to do what we are already doing and demand that the derived classes
   * call it, therefore throwing RAII out the window.
   * How is this any better than C???
   */
  virtual void readAndConstruct(LoadedROM& rom,
                        Taddress tableHeaderAddress,
                        Taddress tableEndAddress) {
//    std::cout << "TABLE HEADER: " << tableHeaderAddress << std::endl;
//    std::cout << "TABLE END: " << tableEndAddress << std::endl;
                        
    // Read address table
    readAddressTable(rom,
                     tableHeaderAddress);
                     
//    std::cout << "header: " << tableHeaderAddress << std::endl;
//    std::cout << "end: " << tableEndAddress << std::endl;
    
    prepareIndices();
    
    readAndConstructReadStep(rom,
                             tableEndAddress);
    
//    std::cout << "\n\n\n***DONE***\n\n\n";
  }
  
  virtual void readAndConstructReadStep(LoadedROM& rom,
                                        Taddress tableEndAddress) {
    // Iterate over primary storage addresses and read corresponding data
    for (typename AddressIndexMap::iterator it = addressToIndex_.begin();
         it != addressToIndex_.end();
         it++) {
//      std::cout << "start: " << it->first << std::endl;
         
      // Compute the size of the array using the start address of the next
      // array, or the end of the table header if at the last entry
      Taddress arrayStartAddress = it->first;
      Taddress arrayEndAddress = 0;
      
      // Check if at last entry of map
      typename AddressIndexMap::iterator nextEntry = it;
      ++nextEntry;
      // If at end, use table content end address as next address
      if (nextEntry == addressToIndex_.end()) {
        arrayEndAddress = tableEndAddress;
      }
      // Otherwise, use start address of next array
      else {
        arrayEndAddress = nextEntry->first;
      }
//      std::cout << '\t' << "end: " << arrayEndAddress << std::endl;
//      std::cout << '\t' << "end - start: " << (arrayEndAddress - arrayStartAddress) << std::endl;
      
      // Compute number of elements in array by dividing by dataSize
      int numElements = (arrayEndAddress - arrayStartAddress)
                          / dataSizeOfOneElement();
                          
//      std::cout << numElements << std::endl;
      
      // Read elements in array
      S dst;
      readElements(dst,
                   rom.directRead(arrayStartAddress),
                   numElements);
      
      // Add read elements to primary storage
      primaryStorage_[it->second] = T(dst);
    }
  }
  
public:
//  typedef typename std::vector<T> BaseDataCollection;
//  typedef typename ConstSizeVector<T> DataCollection;

  /**
   * Default constructor.
   */
  BaseEditableMappedData<T,S>() { };
  
  /**
   * Constructor from data.
   * @param rom ROM to load from.
   * @param tableHeaderAddress Direct address of the table header.
   * @param tableContentAddress Direct address of the table content.
   * @param tableEndAddress Direct address of one past the end of the table.
   * @param subKeyTable Subkey table to use when building address map.
   * @param numPrimaryKeys Number of primary keys in subtable.
   */
  BaseEditableMappedData<T,S>(LoadedROM& rom,
                        Taddress tableHeaderAddress,
                        Taddress tableEndAddress,
                        const int subKeyTable[],
                        int numPrimaryKeys)
  : mapnumToAddress_(subKeyTable,
                     numPrimaryKeys) {
    
  }
  
  void saveInternal(std::string& data) {
    // Write buffer
    Tbyte buffer[ByteSizes::uint32Size];
    
    // Write number of data elements
    ByteConversion::toBytes(primaryStorage_.size(),
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
  //  std::cout << "out numentries: " << primaryStorage_.size() << std::endl;
  
//    std::cout << "primary storage: " << primaryStorage_.size() << std::endl;
//    std::cout << "addr to index: " << addressToIndex_.size() << std::endl;

    // Write each data element
    for (typename AddressIndexMap::iterator it = addressToIndex_.begin();
         it != addressToIndex_.end();
         it++) {
      // Write address
      ByteConversion::toBytes(it->first,
                              buffer,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint32Size);
      
//      std::cout << it->first << std::endl;

//      std::cerr << it->second << std::endl;
      
      // Write element
      saveElement(data,
                  primaryStorage_[it->second]);
                  
//      for (int i = data.size() - 4; i < data.size(); i++) {
//        std::cout << (int)(data[i]) << " ";
//      }
//      std::cout  << std::endl;
    }
    
//    std::cout << "done" << std::endl << std::endl;
    
    // Write address table
    mapnumToAddress_.writeToData(data);
  }
  
  void loadInternal(const Tbyte* data,
                   int& byteCount) {
    // Clear existing data
    primaryStorage_.clear();
    addressToIndex_.clear();
    
    // Read number of data elements
    int numEntries
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::uint32Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
//    std::cout << "in numentries: " << numEntries << std::endl;
    
    // Read each data element
    for (int i = 0; i < numEntries; i++) {
      // Read address
      Taddress address
        = ByteConversion::fromBytes(data + byteCount,
                                    ByteSizes::uint32Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
      byteCount += ByteSizes::uint32Size;
      
//      std::cout << address << std::endl;

      // Read element
      S baseData;
//      std::cout << "before: " << byteCount << std::endl;
      byteCount += loadElement(baseData,
                               data + byteCount);
//      std::cout << "after: " << byteCount << std::endl;
      
      // Convert S to T
      T data(baseData);
      
      addressToIndex_.insert(
        AddressIndexPair(
          address,
          i));
          
      
      // Add to primary storage
      primaryStorage_.push_back(data);
    }
    
//    std::cout << "done" << std::endl << std::endl << std::endl;
    
    // Read address table
    byteCount += mapnumToAddress_.readFromData(data + byteCount);
  }
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data) {
    SaveHelper saver(data,
                     dataChunkID(),
                     chunkVersionNumber());
                     
    saveInternal(data);
    
    saver.finalize();
  }
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return The number of bytes read.
   */
  int load(const Tbyte* data) {
  //  mapnumToAddress_.clear();

    // Count of bytes read
    int byteCount = 0;
    LoadHelper loader(data,
                      byteCount);
                      
    if (loader.version() > maxRecognizedVersionNumber()) {
      throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                         "BaseEditableMappedData::load("
                                         "const Tbyte*)",
                                         dataChunkID(),
                                         dataChunkName(),
                                         loader.version(),
                                         maxRecognizedVersionNumber());
    }
    
    loadInternal(data,
                 byteCount);
    
    // Return number of bytes read
    return byteCount;
  }
  
  /**
   * Writes data to ROM.
   * @param rom ROM to write to.
   */
  virtual void exportToROM(WritableROM& rom) {
    // Export each data element to ROM
    for (typename AddressIndexMap::iterator it = addressToIndex_.begin();
         it != addressToIndex_.end();
         it++) {
      // Address to write to
      Taddress address = it->first;
      
      // Write data
      exportElementToROM(rom,
                         address,
                         primaryStorage_[it->second]);
    }
  }
  
  /**
   * Returns the number of elements in the internal data index.
   * @return The number of elements in the internal data index.
   */
  int size() {
    return primaryStorage_.size();
  }
  
  /**
   * Returns the internal index of the data for the given map.
   * @param primaryMapNum Primary map number.
   * @param subMapNum Submap number.
   * @return The internal index of the data for the given map.
   */
/*  int indexOfMapnum(int primaryMapNum,
                    int subMapNum) {
    // Retrieve corresponding address
    Taddress address
      = mapnumToAddress_.refDataByKeys(
          primaryMapNum,
          subMapNum);
    
    // Retrieve corresponding index
    return addressToIndex_.findValueOrThrow(address);
  } */
  
  /**
   * Returns a reference to the data for the given index.
   * @param dataIndex Internal index of the data to look up.
   * @return A reference to the data for the given index.
   */
  T& dataByIndex(int dataIndex) {
    // Use index to look up corresponding data
    return primaryStorage_[dataIndex];
  }
  
  /**
   * Returns a reference to the data for the given map.
   * @param primaryMapNum Primary map number.
   * @param subMapNum Submap number.
   * @return Reference to the data for the given map.
   */
/*  T& dataByMapnum(int primaryMapNum,
                  int subMapNum) {
    // Look up index
    int index = indexOfMapnum(primaryMapNum,
                              subMapNum);
    
    return dataByIndex(index);
  } */
  
protected:
  
  /**
   * Primary storage for content.
   */
  IndexDataMap primaryStorage_;
  
  AddressIndexMap addressToIndex_;
  
  /**
   * Map of (primary, sub) map numbers to their corresponding data in ROM.
   * Used to provide access on primaryStorage_ by key pairs.
   */
  TwoKeyedAddress mapnumToAddress_;
protected:
  
};


};


#endif
