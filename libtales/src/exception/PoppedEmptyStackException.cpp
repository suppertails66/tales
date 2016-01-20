#include "exception/PoppedEmptyStackException.h"

namespace Tales {


PoppedEmptyStackException::PoppedEmptyStackException(
      const char* nameOfSourceFile__,
      int lineNum__,
      const std::string& source__,
      const std::string& stackName__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    stackName_(stackName__) { };

const char* PoppedEmptyStackException::what() const throw() {
  return (std::string("Popped empty stack: ") + stackName_).c_str();
}
  
std::string PoppedEmptyStackException::stackName() const {
  return stackName_;
}


};
