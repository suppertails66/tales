#ifndef PRIMARYMAPS_H
#define PRIMARYMAPS_H


namespace Tales {


/**
 * Container for primary map data.
 */
class PrimaryMaps {
public:

  /**
   * The highest valid primary map number, plus one.
   * Used to determine the size of certain internally used tables.
   */
  const static int primaryMapTableSize = 0x16;

  /**
   * Enum of valid primary map numbers.
   * Primary map numbers are used, often with a submap number, to look
   * up information on a particular map from many of the game's tables.
   */
  enum PrimaryMap {
    /* 0x00 = not used, but generally handled as 0x01 */
    poloyForest           = 0x01,
    caronForest           = 0x02,
    volcanicTunnel        = 0x03,
    pollyMtn1             = 0x04,
    pollyMtn2             = 0x05,
    lakeRocky             = 0x06,
    lakeCrystal           = 0x07,
    greenIsland           = 0x08,
    cavernIsland          = 0x09,
    cocoIsland            = 0x0A,
    battleFortressFlight  = 0x0B,
    battleFortress        = 0x0C,
    /* 0x0D = not used */
    /* 0x0E = not used */
    /* 0x0F = not used */
    worldMap              = 0x10,
    tailsHouse            = 0x11,
    /* 0x12 = not used? Assigned music 92, intro part 1 (world map) */
    introForest           = 0x13,
    leaveDock             = 0x14,
    returnToDock          = 0x15,
    /* Is this used? It's assigned music 8B, same as the dock cutscenes */
//    dockSomething          = 0x16
  };
  
protected:
  
};


};


#endif 
