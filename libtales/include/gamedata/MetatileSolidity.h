#ifndef METATILESOLIDITY_H
#define METATILESOLIDITY_H


namespace Tales {


/**
 * Container for enum of metatile solidity types.
 */
class MetatileSolidities {
public:
  /**
   * Enum of metatile solidity types.
   * These are an external representation of metatile solidity bitfields,
   * not actually used by the game.
   */
  enum MetatileSolidity {
    nonsolid    = 0,  /**< Nonsolid (fully passable). */
    solidOnTop  = 1,  /**< Passable from below/left/right, but not above. */
    fullySolid  = 2   /**< Solid on all sides. */
  };
};


};


#endif
