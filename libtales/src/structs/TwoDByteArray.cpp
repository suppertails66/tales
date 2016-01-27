#include "structs/TwoDByteArray.h"

namespace Tales {


TwoDByteArray::TwoDByteArray()
  : TwoDArray<Tbyte>() { };

TwoDByteArray::TwoDByteArray(int w__, int h__)
  : TwoDArray<Tbyte>(w__, h__) { };

void TwoDByteArray::clear() {
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
      data_[i][j] = 0;
    }
  }
}


};
