#ifndef TWOKEYEDDATA_H
#define TWOKEYEDDATA_H


#include "exception/TGenericException.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/StringConversion.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


/**
 * Templated class for mapping pieces of data to pairs of keys.
 */
template<class T>
class TwoKeyedData {
public:
  /**
   * Base number for primary keys.
   */
  const static int primaryKeyBase = 0;
  
  /**
   * Base number for subkeys.
   */
  const static int subKeyBase = 1;

  /**
   * Default constructor.
   * Initializes tables to NULL and numPrimaryKeys_ to zero.
   */
  TwoKeyedData<T>()
    : data_(NULL),
      subKeyTable_(NULL),
      numPrimaryKeys_(0) { }
  
  /**
   * Constructor.
   * @param subKeyTable An array with (numPrimaryKeys) keys in which each entry
   * gives the number of subkeys for the primary key.
   * @param numPrimaryKeys Number of entries in subKeyTable.
   */
  TwoKeyedData<T>(const int subKeyTable__[],
                      int numPrimaryKeys__)
    : subKeyTable_(new int[numPrimaryKeys__]),
      numPrimaryKeys_(numPrimaryKeys__) {
    
    // Copy subkey table
    std::memcpy(subKeyTable_,
                subKeyTable__,
                sizeof(int) * numPrimaryKeys__);
    
    // Initialize data array
    data_ = new T*[numPrimaryKeys__];
    
    // Initialize each subarray to the size given in subKeyTable__
    // plus one (subkeys are expected to be 1-based)
    for (int i = 0; i < numPrimaryKeys__; i++) {
      // Only create arrays with at least one subkey
      if (subKeyTable__[i] > 0) {
        data_[i] = new T[subKeyTable__[i] + subKeyBase];
      }  
      else {
        data_[i] = NULL;
      }
    }
  }
  
  /**
   * Destructor.
   */
  virtual ~TwoKeyedData<T>() {
    // Deallocate everything
    deallocateMemory();
  }
  
  /**
   * Copy constructor.
   * @param twoKeyMappedData Source from which to copy data.
   */
  TwoKeyedData<T>(const TwoKeyedData<T>& twoKeyMappedData)
    : subKeyTable_(NULL),
      numPrimaryKeys_(twoKeyMappedData.numPrimaryKeys_) {
    
    // Allocate and copy
    cloneAllocate(twoKeyMappedData);
    
  }
  
  /**
   * Copy assignment.
   * @param twoKeyMappedData Source from which to copy data.
   */
  TwoKeyedData<T>& operator=(const TwoKeyedData<T>& twoKeyMappedData) {
    
    // Delete everything
    deallocateMemory();
    
    // Reallocate at new size
    cloneAllocate(twoKeyMappedData);
    
    // Return reference
    return *this;
  }
  
  /**
   * Returns the number of primary keys.
   * @return Number of primary keys.
   */
  int numPrimaryKeys() const {
    return numPrimaryKeys_;
  }
  
  /**
   * Returns the subkey table.
   * @return The subkey table.
   */
  const int* subKeyTable() const {
    return subKeyTable_;
  }
  
  /**
   * Returns a reference to the data identified by the given key pair.
   * @param primaryKey The primary key of the data to look up.
   * @param subKey The subkey of the data to look up.
   */
  T& refDataByKeys(int primaryKey,
                   int subKey) {
    // Throw if primary key is out of range
    if ((unsigned int)primaryKey >= (unsigned int)numPrimaryKeys_
                                        + primaryKeyBase) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                             "TwoKeyedData<T>::operator[]"
                             "(int,int) [PRIMARY]",
                             primaryKey);
    }
    
    // Throw if subkey is out of range
    if ((unsigned int)subKey >= (unsigned int)(subKeyTable_[primaryKey]
                                    + subKeyBase)) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                             "TwoKeyedData<T>::operator[]"
                             "(int,int) [SUB]",
                             subKey);
    }
    
    // Return the requested data
    return data_[primaryKey][subKey];
  }
  
  /**
   * Returns a const reference to the data identified by the given key pair.
   * @param primaryKey The primary key of the data to look up.
   * @param subKey The subkey of the data to look up.
   */
  const T& refDataByKeys(int primaryKey,
                         int subKey) const {
    // Throw if primary key is out of range
    if ((unsigned int)primaryKey >= (unsigned int)numPrimaryKeys_
                                        + primaryKeyBase) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                             "TwoKeyedData<T>::operator[]"
                             "(int,int) const [PRIMARY]",
                             primaryKey);
    }
    
    // Throw if subkey is out of range
    if ((unsigned int)subKey >= (unsigned int)(subKeyTable_[primaryKey])
                                    + subKeyBase) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                             "TwoKeyedData<T>::operator[]"
                             "(int,int) const [SUB]",
                             subKey);
    }
    
    // Return the requested data
    return data_[primaryKey][subKey];
  }
protected:

  /**
   * Clone and allocate memory.
   * @param twoKeyMappedData Source from which to copy data.
   */
  void cloneAllocate(const TwoKeyedData<T>& twoKeyMappedData) {
    numPrimaryKeys_ = twoKeyMappedData.numPrimaryKeys_;
    
    subKeyTable_ = new int[twoKeyMappedData.numPrimaryKeys_];
    
    // Copy subkey table
    std::memcpy(subKeyTable_,
                twoKeyMappedData.subKeyTable_,
                sizeof(int) * twoKeyMappedData.numPrimaryKeys_);
    
    // Initialize data array
    data_ = new T*[twoKeyMappedData.numPrimaryKeys_];
    
    // Initialize each subarray to the size given in subKeyTable__
    // plus one (subkeys are expected to be 1-based)
    for (int i = 0; i < twoKeyMappedData.numPrimaryKeys_; i++) {
      // Only create arrays with at least one subkey
      if (subKeyTable_[i] > 0) {
        data_[i] = new T[subKeyTable_[i] + subKeyBase];
        
        // Copy each item in the subarray
        for (int j = 0; j < subKeyTable_[i]; j++) {
          data_[i][j] = twoKeyMappedData.data_[i][j];
        }
      }  
      else {
        data_[i] = NULL;
      }
    }
  }
  
  /**
   * Deallocate all memory.
   */
  void deallocateMemory() {
    // Delete each subarray
    for (int i = 0; i < numPrimaryKeys_; i++) {
      delete[] data_[i];
    }
    
    // Delete data array
    delete[] data_;
    
    // Delete subkey table
    delete subKeyTable_;
  }
  
  T** data_;
  
  int* subKeyTable_;
  
  int numPrimaryKeys_;
  
};


};


#endif 
