#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H


#include "exception/FileException.h"

namespace Tales {

/**
 * Exception to be thrown if a file does not exist.
 */
class FileNotFoundException : public FileException {
public:

  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param filename__ Path to the file that triggered the exception.
   */
  FileNotFoundException(const char* nameOfSourceFile__,
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
