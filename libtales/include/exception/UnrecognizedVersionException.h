#ifndef UNRECOGNIZEDVERSIONEXCEPTION_H
#define UNRECOGNIZEDVERSIONEXCEPTION_H


#include "exception/TalesException.h"
#include "structs/DataChunkID.h"

namespace Tales {


class UnrecognizedVersionException : public TalesException {
public:
  /**
   * Default constructor.
   */
  UnrecognizedVersionException();
  
  /**
   * Constructor.
   * @param nameOfSourceFile__ Name of the source file that triggered the
   * exception.
   * @param lineNum__ Number of the source file line at which the exception
   * was triggered.
   * @param source__ The function that triggered the exception.
   * @param readVersion__ The invalid version number read.
   * @param highestRecognizedVersion__ The highest readable version number.
   */
  UnrecognizedVersionException(const char* nameOfSourceFile__,
                 int lineNum__,
                 const std::string& source__,
                 DataChunkIDs::DataChunkID id__,
                 const std::string& chunkName__,
                 int readVersion__,
                 int highestRecognizedVersion__);
  
  /**
   * Override of std::exception::what().
   */
  const char* what() const throw();

  /**
   * Returns the ID of the chunk that triggered the exception.
   * @return The ID of the chunk that triggered the exception.
   */
  DataChunkIDs::DataChunkID id() const;
  
  /**
   * Returns the name of the chunk that triggered the exception.
   * @return The name of the chunk that triggered the exception.
   */
  std::string chunkName() const;
  
  /**
   * Returns the read version number that triggered the exception.
   * @return The read version number that triggered the exception.
   */
  int readVersion() const;
  
  /**
   * Returns the highest readable version number.
   * @return The highest readable version number.
   */
  int highestRecognizedVersion() const;
protected:

  DataChunkIDs::DataChunkID id_;
  
  std::string chunkName_;

  int readVersion_;
  
  int highestRecognizedVersion_;
};


};


#endif
