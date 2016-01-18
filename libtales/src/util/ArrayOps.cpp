#include "util/ArrayOps.h"

namespace Luncheon {


void ArrayOps::reverseArray(char* src, int len) {
  char temp;
  
  char* f = src;
  char* l = src + len - 1;
  
  while (f < l) {
    temp = *f;
    *(f++) = *l;
    *(l--) = temp;
  }
}

void ArrayOps::reverseArray(unsigned char* src, int len) {
  reverseArray((char*)src, len);
}


};
