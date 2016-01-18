#ifndef CONSTSIZEVECTOR_H
#define CONSTSIZEVECTOR_H


#include <vector>

namespace Tales {

/**
 * Class that allows write access to a vector, but not resizing.
 */
template <class T>
class ConstSizeVector {
public:

  /**
   * Typedef of std::vector<T>::iterator for convenient usage.
   */
  typedef typename std::vector<T>::iterator iterator;

  /**
   * Typedef of std::vector<T>::const_iterator for convenient usage.
   */
  typedef typename std::vector<T>::const_iterator const_iterator;
  
  /**
   * Default constructor.
   */
  ConstSizeVector<T>() { };
  
  /**
   * Constructor.
   * @param source Source vector to copy data from.
   */
  ConstSizeVector<T>(const std::vector<T>& source)
    : vec_(source) { };
  
  /**
   * Returns number of elements in the vector.
   * @return Number of elements in the vector.
   */
  typename std::vector<T>::size_type size() const {
    return vec_.size();
  }
  
  /**
   * Access the nth element of the vector.
   * @return Reference to the nth element of the vector.
   */
  T& operator[](int n) {
    return vec_[n];
  }
  
  /**
   * Access the nth element of the vector (const).
   * @return Const reference to the nth element of the vector.
   */
  const T& operator[](int n) const {
    return vec_[n];
  }
  
  /**
   * Returns iterator to start of vector.
   * @return Iterator to start of vector.
   */
  typename std::vector<T>::iterator begin() {
    return vec_.begin();
  }
  
  /**
   * Returns iterator to end of vector.
   * @return Iterator to end of vector.
   */
  typename std::vector<T>::iterator end() {
    return vec_.end();
  }
  
  /**
   * Returns const_iterator to start of vector.
   * @return const_iterator to start of vector.
   */
  typename std::vector<T>::const_iterator cbegin() {
    return vec_.cbegin();
  }
  
  /**
   * Returns const_iterator to end of vector.
   * @return const_iterator to end of vector.
   */
  typename std::vector<T>::const_iterator cend() {
    return vec_.cend();
  }
  
protected:
  
  /**
   * The contained data.
   */
  std::vector<T> vec_;
  
};


};


#endif
