#ifndef TWODARRAY_H
#define TWODARRAY_H


#include "exception/OutOfRangeIndexException.h"
#include "structs/Tbyte.h"
#include <cstdlib>

namespace Tales {


template <class T>
class TwoDArray {
public:
  TwoDArray<T>()
    : data_(NULL),
      w_(0),
      h_(0) { };
  
  TwoDArray<T>(int w__, int h__)
    : data_(NULL),
      w_(w__),
      h_(h__) {
    reinitializeArray(w__, h__);
  }
  
  ~TwoDArray<T>() {
    destroyArray();
  }
  
  void resize(int w__, int h__) {
    reinitializeArray(w__, h__);
  }
    
  int w() const {
    return w_;
  }
  
  int h() const {
    return h_;
  }
  
  T& data(int x, int y) {
    if ((x < 0) || (x >= w_)) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                     "TwoDArray::data(int,int) const [x]",
                                     x);
    }
    
    if ((y < 0) || (y >= h_)) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                     "TwoDArray::data(int,int) const [y]",
                                     y);
    }
  
    return data_[x][y];
  }
  
  const T& data(int x, int y) const {
    if ((x < 0) || (x >= w_)) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                     "TwoDArray::data(int,int) [x]",
                                     x);
    }
    
    if ((y < 0) || (y >= h_)) {
      throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                     "TwoDArray::data(int,int) [y]",
                                     y);
    }
    
    return data_[x][y];
  }
protected:
  void destroyArray() {
    if (data_ == NULL) {
      return;
    }
    
    for (int i = 0; i < w_; i++) {
      delete[] data_[i];
    }
    
    delete[] data_;
  }

  void reinitializeArray(int w__, int h__) {
    destroyArray();
    
    data_ = new T*[w__];
    
    for (int i = 0; i < w__; i++) {
      data_[i] = new T[h__];
    }
  
    w_ = w__;
    h_ = h__;
  }

  T** data_;
  
  int w_;
  int h_;
};


};


#endif