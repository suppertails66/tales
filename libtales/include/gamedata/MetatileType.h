#ifndef METATILETYPE_H
#define METATILETYPE_H


#include <string>

namespace Tales {


/**
 * Container for enum of metatile types (behaviors).
 */
class MetatileTypes {
public:
  /**
   * Number of values in MetatileType enum.
   */
  const static int numMetatileTypes = 0x13;

  /**
   * Enum of metatile types (behaviors).
   */
  enum MetatileType {
    nullType          = 0x0,    /**< "Blank" tile (must be nonsolid) */
    climbable1        = 0x1,    /**< Climbable tile 1? */
    climbable2        = 0x2,    /**< Climbable tile 2? */
    nonclimbable      = 0x3,    /**< Nonclimbable tile */
    damaging          = 0x4,    /**< Damaging tile (hardcoded by tile ID) */
    instadeath        = 0x5,    /**< Instant death when stood on -- unused */
    water             = 0x6,    /**< Water tile */
    gust              = 0x7,    /**< Wind gust -- hardcoded, 0x78-0x7F */
    conveyorLeft      = 0x8,    /**< Leftward conveyor belt */
    crumbling         = 0x9,    /**< Crumbling tile */
    crumblingStart    = 0xA,    /**< Initial state of crumbling tile */
    bombable          = 0xB,    /**< Bombable tile (hardcoded by ID) */
    conveyorRight     = 0xC,    /**< Rightward conveyor belt */
    typeD             = 0xD,    /**< Handler is ret -- unused */
    napalm            = 0xE,    /**< Destroyable by napalm bomb */
    downOnly          = 0xF,    /**< One-way tile (down) -- ID A0 */
    type10            = 0x10,   /**< Handler is ret -- unused */
    bigGust           = 0x11,   /**< Blows upward w/o flight -- tile ID 9F */
    type12            = 0x12    /**< Handler is ret -- unused */
  };
  
  static std::string nameOfType(MetatileTypes::MetatileType metatileType);
  
protected:
  
};


};


#endif 
