#include "exception/TGenericException.h"

namespace Tales {


TGenericException::TGenericException(const char* nameOfSourceFile__,
                                   int lineNum__,
                                   const std::string& source__,
                                   const std::string& problem__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    problem_(problem__) { };

const char* TGenericException::what() const throw() {
  return problem_.c_str();
}

std::string TGenericException::problem() const {
  return problem_;
}


}; 
