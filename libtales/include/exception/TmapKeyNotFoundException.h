#ifndef TMAPKEYNOTFOUNDEXCEPTION_H
#define TMAPKEYNOTFOUNDEXCEPTION_H


#include "exception/TalesException.h"
#include <string>

namespace Tales {


class TmapKeyNotFoundException : public TalesException {
public:
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ Name of the function that triggered the exception.
   * @param keyAsString__ Key that triggered the exception, stored as a string.
   */
  TmapKeyNotFoundException(const char* nameOfSourceFile__,
                           int lineNum__,
                           const std::string& source__,
                           const std::string& keyAsString__);
  
  /**
   * Override of std::exception::what().
   */
  const char* what() const throw();
  
  /**
   * Retrieve the name of the stack that triggered the exception.
   * @return The name of the stack that triggered the exception.
   */
  std::string keyAsString() const;
protected:

  /**
   * The key that was not found, converted to a string.
   */
  std::string keyAsString_;
  
};


};


#endif
