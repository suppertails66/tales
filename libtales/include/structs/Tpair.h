#ifndef TPAIR_H
#define TPAIR_H


#include <utility>

namespace Tales {


/**
 * Simulated typedef of std::pair.
 */
template <class T, class U>
class Tpair {
public:
  /**
   * Simulated typedef of std::pair.
   */
  typedef std::pair<T,U> Type;
};


};


#endif 
