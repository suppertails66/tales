#ifndef NOTENOUGHSPACEEXCEPTION_H
#define NOTENOUGHSPACEEXCEPTION_H


#include "exception/TalesException.h"

namespace Tales {


class NotEnoughSpaceException : public TalesException {
public:
  /**
   * Default constructor.
   */
  NotEnoughSpaceException();
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ The function that triggered the exception.
   * @param needed__ The number of bytes the triggering function needed.
   */
  NotEnoughSpaceException(const char* nameOfSourceFile__,
                 int lineNum__,
                 const std::string& source__,
                 int needed__);
  
  /**
   * Override of std::exception::what().
   */
  const char* what() const throw();
  
  /**
   * Returns the number of bytes needed by the triggered function.
   * @return The number of bytes needed by the triggered function.
   */
  int needed();
protected:

  int needed_;
  
};


};


#endif
