#ifndef LEVELWIDTH_H
#define LEVELWIDTH_H


namespace Tales {


/**
 * Container for enum of allowed level widths.
 */
class LevelWidths {
public:
  /**
   * Enum of possible level widths.
   * Tails Adventures uses a rather inflexible format for level widths
   * -- in order to optimize metatile collision, the game uses lookup
   * tables of y-coordinates specifically produced for each possible
   * level width. These tables are hardcoded to appear in the first
   * two ROM banks, which they share with lots of other frequently
   * used data and code. Since trying to change this would be very
   * difficult, only these predefined level widths are possible.
   */
  enum LevelWidth {
    width16    = 16,    /**< 16 metatiles wide. */
    width32    = 32,    /**< 32 metatiles wide. */
    width48    = 48,    /**< 48 metatiles wide. */
    width64    = 64,    /**< 64 metatiles wide. */
    width80    = 80,    /**< 80 metatiles wide. */
    width96    = 96,    /**< 96 metatiles wide. */
    width128   = 128,   /**< 128 metatiles wide. */
    width256   = 256,   /**< 256 metatiles wide. */
  };
  
  /**
   * Convert an enumerated width value to its integer equivalent.
   */
  static int widthToInt(LevelWidths::LevelWidth width);
  
  /**
   * Convert an integer width value to its enumerated equivalent.
   */
  static LevelWidths::LevelWidth intToWidth(int width);
};


};


#endif 
