#include "exception/InvalidFileException.h"

namespace Tales {


InvalidFileException::InvalidFileException(const char* nameOfSourceFile__,
                                           int lineNum__,
                                           const std::string& source__,
                                           const std::string& filename__)
  : FileException(nameOfSourceFile__,
                  lineNum__,
                  source__,
                  filename__) { };
  
const char* InvalidFileException::what() const throw() {
  return (std::string("Invalid file: ") + filename_).c_str();
}


}; 
