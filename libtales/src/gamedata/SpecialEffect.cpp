#include "gamedata/SpecialEffect.h"

namespace Tales {


std::string SpecialEffects::nameOfEffect(SpecialEffect effect) {
  switch (effect) {
  case none:
    return "No effect";
    break;
  case sparkFlash:
    return "Flash from Spark weapon";
    break;
  case torchCycle:
    return "Torch palette cycle";
    break;
  case lakeRockyCycle:
    return "Lake Rocky cycle";
    break;
  case lakeRockyUpperFlash1:
    return "Lake Rocky upper cycle 1";
    break;
  case lakeRockyUpperFlash2:
    return "Lake Rocky upper cycle 2";
    break;
  case lakeRockyBaseFade1:
    return "Lake Rocky lower cycle 1";
    break;
  case lakeRockyBaseFade2:
    return "Lake Rocky lower cycle 2";
    break;
  case lakeRockyBaseFlash:
    return "Lake Rocky lower cycle 3";
    break;
  case cavernIslandCycle:
    return "Cavern Island cycle";
    break;
  case lakeCrystalWater:
    return "Lake Crystal animated water";
    break;
  case poloyForestCycle:
    return "Poloy Forest cycle";
    break;
  case finalBossUnlocked:
    return "Final boss trigger sequence";
    break;
  case nullD:
    return "Dummy 1";
    break;
  case nullE:
    return "Dummy 2";
    break;
  case battleFortressConveyor:
    return "Battle Fortress animated conveyor";
    break;
  case rockyBossScroll:
    return "Lake Rocky boss scrolling";
    break;
  case unknown11:
    return "Cavern Island boss split-scroll";
    break;
  case cocoIslandCycle:
    return "Coco Island cycle";
    break;
  case worldMapCycle:
    return "World map cycle";
    break;
  default:
    return "***ERROR EFFECT***";
    break;
  }
}


};
