#include "exception/ColorOutOfRangeException.h"
#include <string>

namespace Tales {


ColorOutOfRangeException::ColorOutOfRangeException(
      const char* nameOfSourceFile__,
      int lineNum__,
      const std::string& source__,
      int invalidIndex__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    invalidIndex_(invalidIndex__) { };

const char* ColorOutOfRangeException::what() const throw() {
  return "Tried to access color at invalid index";
}

int ColorOutOfRangeException::invalidIndex() const {
  return invalidIndex_;
}



}; 
