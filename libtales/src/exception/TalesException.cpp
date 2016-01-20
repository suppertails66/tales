#include "exception/TalesException.h"

namespace Tales {


TalesException::TalesException()
  : nameOfSourceFile_("unknown source file"),
    lineNum_(-1),
    source_("unknown source") { };

TalesException::TalesException(const char* nameOfSourceFile__,
                               int lineNum__,
                               const std::string& source__)
  : nameOfSourceFile_(std::string(nameOfSourceFile__)),
    lineNum_(lineNum__),
    source_(source__) { };

const std::string& TalesException::nameOfSourceFile() const {
  return nameOfSourceFile_;
}

int TalesException::lineNum() const {
  return lineNum_;
}

const std::string& TalesException::source() const {
  return source_;
}


} 
