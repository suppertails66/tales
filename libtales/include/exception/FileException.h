#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H


#include "exception/TalesException.h"
#include <string>

namespace Tales {

/**
 * Base class for all file-related exceptions.
 */
class FileException : public TalesException {
public:
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ Name of the function that triggered the exception.
   * @param filename__ Path to the file that triggered the exception.
   */
  FileException(const char* nameOfSourceFile__,
                int lineNum__,
                const std::string& source__,
                const std::string& filename__);
  
  /**
   * Override of std::exception::what().
   * @return String explaining the error.
   */
  const char* what() const throw();
  
  /**
   * Returns the path to the file that triggered the exception.
   * @return Path to the file that triggered the exception.
   */
  std::string filename() const;
  
protected:

  /**
   * Path to the file that triggered the exception.
   */
  std::string filename_;
  
};


}


#endif 
