#include "exception/FileNotFoundException.h"

namespace Tales {


FileNotFoundException::FileNotFoundException(const char* nameOfSourceFile__,
                                             int lineNum__,
                                             const std::string& source__,
                                             const std::string& filename__)
  : FileException(nameOfSourceFile__,
                  lineNum__,
                  source__,
                  filename__) { };
  
const char* FileNotFoundException::what() const throw() {
  return (std::string("File \"") + filename_ + "\" not found").c_str();
}


}; 
