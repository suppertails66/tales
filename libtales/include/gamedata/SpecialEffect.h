#ifndef SPECIALEFFECT_H
#define SPECIALEFFECT_H


#include <string>

namespace Tales {


/**
 * Container for enum of special graphic effects.
 */
class SpecialEffects {
public:
  const static int specialEffectLimit = 0x14;

  /**
   * Enum of special graphic effects.
   */
  enum SpecialEffect {
    none                   = 0x00,  /**< No effect. */
    sparkFlash             = 0x01,  /**< Flash from "Spark" item. */
    torchCycle             = 0x02,  /**< Volcanic Tunnel/Polly Mt. 2 cycle. */
    lakeRockyCycle         = 0x03,  /**< Lake Rocky palette cycle. */
    lakeRockyUpperFlash1   = 0x04,  /**< Lake Rocky upper effect 1. */
    lakeRockyUpperFlash2   = 0x05,  /**< Lake Rocky upper effect 2. */
    lakeRockyBaseFade1     = 0x06,  /**< Lake Rocky base red fade effect. */
    lakeRockyBaseFade2     = 0x07,  /**< Lake Rocky base green fade effect. */
    lakeRockyBaseFlash     = 0x08,  /**< Lake Rocky base flash effect. */
    cavernIslandCycle      = 0x09,  /**< Cavern Island palette cycle. */
    lakeCrystalWater       = 0x0A,  /**< Lake Crystal waterfall effect. */
    poloyForestCycle       = 0x0B,  /**< Poloy Forest palette cycle. */
    finalBossUnlocked      = 0x0C,  /**< Part of final boss automation. */
    nullD                  = 0x0D,  /**< Does nothing. Used in BF flight 1. */
    nullE                  = 0x0E,  /**< Does nothing. Used in BF flight 2. */
    battleFortressConveyor = 0x0F,  /**< Battle Fortress conveyor. */
    rockyBossScroll        = 0x10,  /**< Lake Rocky boss scrolling effect. */
    unknown11              = 0x11,  /**< ? buggy split-scroll */
    cocoIslandCycle        = 0x12,  /**< Coco Island palette cycle. */
    worldMapCycle          = 0x13,  /**< World map palette cycle. */
    
    creditsSequence        = 0x18   /**< Credits sequence --  unintentional? */
  };
  
  static std::string nameOfEffect(SpecialEffect effect);
};


};


#endif
