#include "exception/InvalidLoadDataException.h"

namespace Tales {


InvalidLoadDataException::InvalidLoadDataException(
                       const char* nameOfSourceFile__,
                       int lineNum__,
                       const std::string& source__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__) { };

const char* InvalidLoadDataException::what() const throw() {
  return "Tried to load invalid data";
}


};
