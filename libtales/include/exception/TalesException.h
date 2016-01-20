#ifndef TALESEXCEPTION_H
#define TALESEXCEPTION_H


// A simple macro that retrieves the file name and line number
// for use in exception throws
#define TALES_SRCANDLINE __FILE__,__LINE__

#include <exception>
#include <string>

namespace Tales {


/**
 * Base class for all library exceptions.
 */
class TalesException : public std::exception {
public:
  
  /**
   * Default constructor.
   */
  TalesException();
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ The function that triggered the exception.
   */
  TalesException(const char* nameOfSourceFile__,
                 int lineNum__,
                 const std::string& source__);
  
  /**
   * Retrieves name of the source file from which the exception was triggered.
   */
  const std::string& nameOfSourceFile() const;
  
  /**
   * Retrieves number of the line at which the exception was triggered.
   */
  int lineNum() const;
  
  /**
   * Retrieves the name of the function that triggered the exception.
   */
  const std::string& source() const;
  
protected:

  /**
   * The name of the source file from which the exception was triggered.
   */
  std::string nameOfSourceFile_;

  /**
   * The number of the line at which the exception was triggered.
   */
  int lineNum_;

  /**
   * The name of the function that triggered the exception.
   */
  std::string source_;
  
  
  
};


}


#endif
