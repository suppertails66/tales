#include "exception/UnrecognizedVersionException.h"
#include "util/StringConversion.h"
#include <string>

using namespace Luncheon;

namespace Tales {


UnrecognizedVersionException::UnrecognizedVersionException(
                 const char* nameOfSourceFile__,
                 int lineNum__,
                 const std::string& source__,
                 DataChunkIDs::DataChunkID id__,
                 const std::string& chunkName__,
                 int readVersion__,
                 int highestRecognizedVersion__)
  : TalesException(nameOfSourceFile__,
                   lineNum__,
                   source__),
    id_(id__),
    chunkName_(chunkName__),
    readVersion_(readVersion__),
    highestRecognizedVersion_(highestRecognizedVersion__) { };

const char* UnrecognizedVersionException::what() const throw() {
  return (std::string("Chunk of type ")
            + StringConversion::toString(static_cast<int>(id_))
            + " (" + chunkName_ + ")"
            + " could not be read with version"
            + StringConversion::toString(readVersion_)
            + "; highest possible is "
            + StringConversion::toString(highestRecognizedVersion_)).c_str();
}

DataChunkIDs::DataChunkID UnrecognizedVersionException::id() const {
  return id_;
}
  
std::string UnrecognizedVersionException::chunkName() const {
  return chunkName_;
}

int UnrecognizedVersionException::readVersion() const {
  return readVersion_;
}

int UnrecognizedVersionException::highestRecognizedVersion() const {
  return highestRecognizedVersion_;
}


}
