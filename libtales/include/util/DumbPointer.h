#ifndef DUMBPOINTER_H
#define DUMBPOINTER_H


namespace Luncheon {


// Container for a pointer which is to be stored and accessed,
// but not deleted
template <class T>
class DumbPointer {
public:
  DumbPointer()
    : pointer_(0) { };
    
  DumbPointer(T* pointer__)
    : pointer_(pointer__) { };
    
  T& reference() {
    return *pointer_;
  }
protected:
  T* pointer_;
};


};


#endif 
