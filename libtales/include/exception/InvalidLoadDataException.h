#ifndef INVALIDLOADDATAEXCEPTION_H
#define INVALIDLOADDATAEXCEPTION_H


#include "exception/TalesException.h"

namespace Tales {


class InvalidLoadDataException : public TalesException {
public:
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ The function that triggered the exception.
   */
  InvalidLoadDataException(const char* nameOfSourceFile__,
                         int lineNum__,
                         const std::string& source__);
  
  /**
   * Override of std::exception::what().
   */
  const char* what() const throw();
  
protected:
  
};


};


#endif
