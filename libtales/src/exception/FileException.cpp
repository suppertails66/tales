#include "exception/FileException.h"

namespace Tales {


FileException::FileException(const char* nameOfSourceFile__,
                             int lineNum__,
                             const std::string& source__,
                             const std::string& filename__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    filename_(filename__) { };
  
const char* FileException::what() const throw() {
  return (std::string("File-related exception involving: ")
            + filename_).c_str();
}
  
std::string FileException::filename() const {
  return filename_;
}


} 
