#include "exception/OutOfRangeIndexException.h"
#include <string>

namespace Tales {


OutOfRangeIndexException::OutOfRangeIndexException(
      const char* nameOfSourceFile__,
      int lineNum__,
      const std::string& source__,
      int invalidIndex__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    invalidIndex_(invalidIndex__) { };

const char* OutOfRangeIndexException::what() const throw() {
  return "Tried to access invalid index";
}

int OutOfRangeIndexException::invalidIndex() const {
  return invalidIndex_;
}



};  
