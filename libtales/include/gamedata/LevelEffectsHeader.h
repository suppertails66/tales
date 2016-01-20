#ifndef LEVELEFFECTSHEADER_H
#define LEVELEFFECTSHEADER_H


#include "gamedata/SpecialEffect.h"
#include "structs/Tbyte.h"
#include <string>

namespace Tales {


/**
 * Container for and access on level special effect settings.
 */
class LevelEffectsHeader {
public:
  /**
   * Size of raw data representation in bytes.
   */
  const static int dataSize = 4;
  
  /**
   * The number of effects in a header.
   */
  const static int numEffects = 4;

  /**
   * Default constructor.
   */
  LevelEffectsHeader();
  
  /**
   * Constructor from raw data.
   * @param data Byte array to read from.
   */
  LevelEffectsHeader(const Tbyte* data);
  
  /**
   * Saves to a string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes to a byte array.
   * @param data Byte array to write to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Accessor on effects_.
   * @param index Index of the effect to retrieve.
   * @return Reference to the effect at the given index.
   */
  SpecialEffects::SpecialEffect& effect(int index);
  
  /**
   * Const accessor on effects_.
   * @param index Index of the effect to retrieve.
   * @return Const reference to the effect at the given index.
   */
  const SpecialEffects::SpecialEffect& effect(int index) const;
  
protected:
  
  /**
   * Array of effects.
   */
  SpecialEffects::SpecialEffect effects_[numEffects];
  
};


};


#endif
