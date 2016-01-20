#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <string>

namespace Tales {


/**
 * Data for one of Tails' spawn points in a level.
 */
class SpawnPoint {
public:
  /**
   * Size of raw data representation.
   */
  const static int dataSize = 8;

  /**
   * Default constructor.
   */
  SpawnPoint();
  
  /**
   * Constructor from data.
   * @param data Byte array to read from.
   */
  SpawnPoint(const Tbyte* data);
  
  /**
   * Reads data from byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Writes data to byte array.
   * @param data Byte array to write to.
   * @return Number of bytes written.
   */
  void writeToData(Tbyte* data);
  
  /**
   * Loads from byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Saves to string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Getter.
   */
  int camX() const;
  
  /**
   * Getter.
   */
  int camY() const;
  
  /**
   * Getter.
   */
  int tailsX() const;
  
  /**
   * Getter.
   */
  int tailsY() const;
  
  /**
   * Setter.
   */
  void setCamX(int camX__);
  
  /**
   * Setter.
   */
  void setCamY(int camY__);
  
  /**
   * Setter.
   */
  void setTailsX(int tailsX__);
  
  /**
   * Setter.
   */
  void setTailsY(int tailsY__);
   
protected:

  /**
   * Camera starting x-position.
   */
  int camX_;
  
  /**
   * Camera starting y-position.
   */
  int camY_;
  
  /**
   * Tails starting x-position.
   */
  int tailsX_;
  
  /**
   * Tails starting y-position.
   */
  int tailsY_;
  
};


};


#endif
