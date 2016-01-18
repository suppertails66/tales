#ifndef TMAP_H
#define TMAP_H


#include <map>
#include <utility>
#include <string>
#include "util/StringConversion.h"
#include "exception/TmapKeyNotFoundException.h"

using namespace Luncheon;

namespace Tales {


/**
 * Derived class of std::map with custom access operations.
 */
template < class Key,
           class T,
           class Compare = std::less<Key>,
           class Alloc = std::allocator<std::pair<const Key,T> >
           >
class Tmap : public std::map<Key,T,Compare,Alloc> {
public:
  /**
   * A convenience typedef for using pairs.
   */
  typedef std::pair<Key,T> PairType;
  
  /**
   * Finds the given key, or throws if it does not exist.
   * @return Iterator pointing to the target element.
   * @throws TmapKeyNotFoundException
   */
  typename std::map<Key,T,Compare,Alloc>::iterator findOrThrow(Key keyValue) {
    typename std::map<Key,T,Compare,Alloc>::iterator it = this->find(keyValue);
    
    // Return iterator on successful find
    if (it != this->end()) {
      return it;
    }
    // Throw on unsuccessful find
    else {
      throw TmapKeyNotFoundException(
                             TALES_SRCANDLINE,
                             "Tmap::findOrFail(Key)",
                             std::string("Could not find key: ")
                             + StringConversion::toString(keyValue));
    }
  }
  
  /**
   * Finds the given key, or throws if it does not exist.
   * @return Iterator pointing to the target element.
   * @throws TmapKeyNotFoundException
   */
  typename std::map<Key,T,Compare,Alloc>::const_iterator findOrThrow(
        Key keyValue) const {
    typename std::map<Key,T,Compare,Alloc>::const_iterator it
      = this->find(keyValue);
    
    // Return iterator on successful find
    if (it != this->cend()) {
      return it;
    }
    // Throw on unsuccessful find
    else {
      throw TmapKeyNotFoundException(
                             TALES_SRCANDLINE,
                             "Tmap::findOrFail(Key)",
                             std::string("Could not find key: ")
                             + StringConversion::toString(keyValue));
    }
  }
  
  /**
   * Finds the given key, or throws if it does not exist.
   * @return The value corresponding to the key.
   * @throws TmapKeyNotFoundException
   */
  T& findValueOrThrow(Key keyValue) {
    return this->findOrThrow(keyValue)->second;
  }
  
  /**
   * Finds the given key, or throws if it does not exist.
   * @return The value corresponding to the key.
   * @throws TmapKeyNotFoundException
   */
  const T& findValueOrThrow(Key keyValue) const {
    return this->findOrThrow(keyValue)->second;
  }
  
};

//template <class T, class U>
//class Tmap {
//public:
//  typedef std::map<T,U> Type;
  
//  typedef std::pair<T,U> PairType;
//};


};


#endif 
