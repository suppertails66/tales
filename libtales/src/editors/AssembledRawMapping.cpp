#include "editors/AssembledRawMapping.h"

namespace Tales {


AssembledRawMapping::AssembledRawMapping()
  : offsetX_(0),
    offsetY_(0) { };

AssembledRawMapping::AssembledRawMapping(
                    const TwoDByteArray& data__,
                    int offsetX__,
                    int offsetY__)
  : data_(data__),
    offsetX_(offsetX__),
    offsetY_(offsetY__) { };

TwoDByteArray& AssembledRawMapping::data() {
  return data_;
}

int AssembledRawMapping::offsetX() const {
  return offsetX_;
}

int AssembledRawMapping::offsetY() const {
  return offsetY_;
}

void AssembledRawMapping::setData(const TwoDByteArray& data__) {
  data_ = data__;
}

void AssembledRawMapping::setOffsetX(int offsetX__) {
  offsetX_ = offsetX__;
}

void AssembledRawMapping::setOffsetY(int offsetY__) {
  offsetY_ = offsetY__;
}


};
