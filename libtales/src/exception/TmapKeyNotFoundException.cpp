#include "exception/TmapKeyNotFoundException.h"

namespace Tales {


TmapKeyNotFoundException::TmapKeyNotFoundException(
                          const char* nameOfSourceFile__,
                          int lineNum__,
                          const std::string& source__,
                          const std::string& keyAsString__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    keyAsString_(keyAsString__) { };

const char* TmapKeyNotFoundException::what() const throw() {
  return (std::string("Could not find key: ")
            + keyAsString_).c_str();
}

std::string TmapKeyNotFoundException::keyAsString() const {
  return keyAsString_;
}


};
