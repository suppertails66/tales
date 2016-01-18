#include "editors/GraphicCategory.h"

namespace Tales {


std::string GraphicCategories::nameOfCategory(GraphicCategory category) {
  switch (category) {
  case enemy:
    return "Enemy";
    break;
  case boss:
    return "Boss";
    break;
  case obstacle:
    return "Obstacle";
    break;
  case effect:
    return "Effect";
    break;
  case weapon:
    return "Weapon";
    break;
  case cutscene:
    return "Cutscene";
    break;
  case level:
    return "Level";
    break;
  case interface:
    return "Interface";
    break;
  case misc:
    return "Misc";
    break;
  case tails:
    return "Tails";
    break;
  case remoteRobot:
    return "Remote Robot";
    break;
  case titleCard:
    return "Title card";
    break;
  case itemLabel:
    return "Item label";
    break;
  default:
    return "**BAD CATEGORY**";
    break;
  };
}


}; 
