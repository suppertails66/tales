#include "util/GenericException.h"

namespace Luncheon {


GenericException::GenericException(const std::string& whatString__)
  : std::exception(),
    whatString_(whatString__) { };

const char* GenericException::what() const throw() {
  return whatString_.c_str();
}


};
