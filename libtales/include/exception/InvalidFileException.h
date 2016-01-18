#ifndef INVALIDFILEEXCEPTION_H
#define INVALIDFILEEXCEPTION_H


#include "exception/FileException.h"

namespace Tales {

/**
 * Exception to be thrown if a file is not in the expected format.
 */
class InvalidFileException : public FileException {
public:
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param filename__ Path to the file that triggered the exception.
   */
  InvalidFileException(const char* nameOfSourceFile__,
                       int lineNum__,
                       const std::string& source__,
                       const std::string& filename__);
  
  /**
   * Override of std::exception::what().
   * @return String explaining the error.
   */
  const char* what() const throw();
  
protected:
  
};


};


#endif 
