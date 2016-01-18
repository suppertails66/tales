#ifndef COLOROUTOFRANGEEXCEPTION_H
#define COLOROUTOFRANGEEXCEPTION_H


#include "exception/TalesException.h"

namespace Tales {


/**
 * Exception triggered by trying to access a color at an invalid index.
 */
class ColorOutOfRangeException : public TalesException {
public:
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ Name of the function that triggered the exception.
   * @param invalidIndex__ The out-of-range index that caused the exception.
   */
  ColorOutOfRangeException(const char* nameOfSourceFile__,
                           int lineNum__,
                           const std::string& source__,
                           int invalidIndex__);
  
  /**
   * Override of std::exception::what().
   * @return C-string explaining the exception.
   */
  const char* what() const throw();
  
  /**
   * Retrieve the out-of-range index that caused the exception.
   * @return The out-of-range index that caused the exception.
   */
  int invalidIndex() const;
protected:

  /**
   * The out-of-range index that caused the exception.
   */
  int invalidIndex_;
  
};


};


#endif
