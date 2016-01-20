#include "gamedata/SoundID.h"

namespace Tales {


std::string SoundIDs::nameOfMusicID(SoundID musicID) {
  switch (musicID) {
  case trackPlaying:
    return "Nothing/no change";
    break;
  case titleMusic:
    return "Title screen";
    break;
  case poloyForestMusic:
    return "Poloy Forest";
    break;
  case undergroundMusic:
    return "Volcanic Tunnel/Cavern Island";
    break;
  case pollyMtnMusic:
    return "Polly Mt. 1";
    break;
  case cocoIslandMusic:
    return "Coco Island";
    break;
  case underwaterMusic:
    return "Lake Rocky";
    break;
  case battleFortressMusic:
    return "Battle Fortress 2";
    break;
  case worldMapMusic:
    return "World map";
    break;
  case tailsHouseMusic:
    return "Tails' House";
    break;
  case passwordMusic:
    return "Password";
    break;
  case seaFoxCutsceneMusic:
    return "Lake Crystal/Battle Fortress 1";
    break;
  case radioOnlyMusic:
    return "Radio-only theme";
    break;
  case bossMusic:
    return "Boss";
    break;
  case finalBossMusic:
    return "Final boss";
    break;
  case gameOverMusic:
    return "Game over";
    break;
  case deathMusic:
    return "Death";
    break;
  case blankMusic1:
    return "Dummy 1";
    break;
  case introPart1Music:
    return "Intro part 1";
    break;
  case endingMusic:
    return "Ending";
    break;
  case creditsMusic:
    return "Credits";
    break;
  case caronForestMusic:
    return "Caron Forest";
    break;
  case blankMusic2:
    return "Dummy 2";
    break;
  case introPart2Music:
    return "Intro part 2";
    break;
  case introPart3Music:
    return "Intro part 3";
    break;
  case blankMusic3:
    return "Dummy 3";
    break;
  case introPart4Music:
    return "Intro part 4";
    break;
  default:
    return "***NOT MUSIC ID***";
    break;
  }
}


};
