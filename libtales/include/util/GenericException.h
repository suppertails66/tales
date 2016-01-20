#ifndef GENERICEXCEPTION_H
#define GENERICEXCEPTION_H


#include <exception>
#include <string>

namespace Luncheon {


class GenericException : public std::exception {
public:
  GenericException(const std::string& whatString__);

  virtual const char* what() const throw();
protected:
  std::string whatString_;
};


};


#endif 
