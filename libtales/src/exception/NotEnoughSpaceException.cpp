#include "exception/NotEnoughSpaceException.h"
#include "util/StringConversion.h"
#include <string>

using namespace Luncheon;

namespace Tales {


NotEnoughSpaceException::NotEnoughSpaceException()
  : TalesException(),
    needed_(0) { };

NotEnoughSpaceException::NotEnoughSpaceException(
               const char* nameOfSourceFile__,
               int lineNum__,
               const std::string& source__,
               int needed__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    needed_(needed__) { };

const char* NotEnoughSpaceException::what() const throw() {
  return (std::string("Unable to find ")
            + StringConversion::toString(needed_)
            + " bytes of free space").c_str();
}
    
int NotEnoughSpaceException::needed() {
  return needed_;
}


};
