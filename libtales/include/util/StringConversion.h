#ifndef STRINGCONVERSION_H
#define STRINGCONVERSION_H


#include <string>
#include <sstream>

namespace Luncheon {


class StringConversion {
public:
  template<class T>
  static T fromString(const std::string& str) {
    std::istringstream iss;
    iss.str(str);
    T result;
    iss >> result;
    return result;
  }
  
  template<class T>
  static std::string toString(const T obj) {
    std::ostringstream oss;
    oss << obj;
    return oss.str();
  }
protected:
  
};


};


#endif 
