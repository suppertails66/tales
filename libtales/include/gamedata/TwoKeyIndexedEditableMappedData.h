#ifndef TWOKEYINDEXEDEDITABLEMAPPEDDATA_H
#define TWOKEYINDEXEDEDITABLEMAPPEDDATA_H


#include "TwoKeyEditableMappedData.h"
#include "gamegear/LoadedROM.h"
#include "structs/Taddress.h"

namespace Tales {


/**
 * Storage/access for indexed data, accessible by map keys.
 */
template <class T, class S = T>
class TwoKeyIndexedEditableMappedData
  : public TwoKeyEditableMappedData<T, S> {
public:
  
  TwoKeyIndexedEditableMappedData()
    : TwoKeyEditableMappedData<T, S>() { };
  
  TwoKeyIndexedEditableMappedData(LoadedROM& rom,
                           Taddress tableHeaderAddress,
                           Taddress tableContentAddress,
                           Taddress tableEndAddress,
                           int numEntries,
                           const int subKeyTable[],
                           int numPrimaryMaps)
  : TwoKeyEditableMappedData<T, S>(rom,
                                 tableHeaderAddress,
                                 tableEndAddress,
                                 subKeyTable,
                                 numPrimaryMaps) { };
  
protected:

  virtual void readAndConstructReadStep(LoadedROM& rom,
                                        Taddress tableEndAddress) {
    // Don't need this due to our read method
  }
  
  /**
   * This should be called in derived classes' constructors.
   */
  virtual void readAllDataAndConstruct(
                        LoadedROM& rom,
                        Taddress tableHeaderAddress,
                        Taddress tableContentAddress,
                        Taddress tableEndAddress,
                        int numEntries) {
  //    std::cout << "TABLE HEADER: " << tableHeaderAddress << std::endl;
  //    std::cout << "TABLE END: " << tableEndAddress << std::endl;
                        
    // Read address table
    TwoKeyEditableMappedData<T, S>
        ::readAddressTable(rom,
                         tableHeaderAddress);
                     
  //    std::cout << "header: " << tableHeaderAddress << std::endl;
  //    std::cout << "end: " << tableEndAddress << std::endl;
    
  //  prepareIndices();

    // Read all data
    Taddress dataReadAddress = tableContentAddress;
    for (int i = 0; i < numEntries; i++) {
      // Insert address to index mapping
      BaseEditableMappedData<T, S>::addressToIndex_.insert(
        typename BaseEditableMappedData<T, S>::AddressIndexPair(
          dataReadAddress,
          BaseEditableMappedData<T, S>::primaryStorage_.size()));
          
      // Read element
      T obj;
//      std::cerr << dataReadAddress << std::endl;
      int readAmount = this->readElements(obj,
                   rom.directRead(dataReadAddress),
                   1);
      dataReadAddress += readAmount;
//      std::cerr << dataReadAddress << std::endl;
//      std::cerr << i << std::endl;
//      dataReadAddress += this->dataSizeOfOneElement();
      
      // Add to storage
      BaseEditableMappedData<T, S>::primaryStorage_.push_back(obj);
    }
    
//    std::cerr << "done1" << std::endl;
    
    // Read the entries
//    readAndConstructReadStep(rom,
//                             tableEndAddress);
    
//    std::cerr << "done2" << std::endl;
    
  //    std::cout << "\n\n\n***DONE***\n\n\n";
  }
};


};


#endif
