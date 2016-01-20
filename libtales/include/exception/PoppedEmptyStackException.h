#ifndef POPPEDEMPTYSTACKEXCEPTION_H
#define POPPEDEMPTYSTACKEXCEPTION_H


#include "exception/TalesException.h"
#include <string>

namespace Tales {


/**
 * Exception thrown when an empty stack is popped.
 */
class PoppedEmptyStackException : public TalesException {
public:

  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ Name of the function that triggered the exception.
   * @param stackName__ Name of the stack that triggered the exception.
   */
  PoppedEmptyStackException(const char* nameOfSourceFile__,
                            int lineNum__,
                            const std::string& source__,
                            const std::string& stackName__);
  
  /**
   * Override of std::exception::what().
   */
  const char* what() const throw();
  
  /**
   * Retrieve the name of the stack that triggered the exception.
   * @return The name of the stack that triggered the exception.
   */
  std::string stackName() const;
protected:

  /**
   * The name of the stack that triggered the exception.
   */
  std::string stackName_;
  
};


};


#endif
