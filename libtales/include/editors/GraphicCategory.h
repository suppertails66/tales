#ifndef GRAPHICCATEGORY_H
#define GRAPHICCATEGORY_H


#include <string>

namespace Tales {


class GraphicCategories {
public:
  enum GraphicCategory {
    enemy,
    boss,
    obstacle,
    effect,
    weapon,
    cutscene,
    level,
    interface,
    misc,
    tails,
    remoteRobot,
    titleCard,
    itemLabel
  };
  
  static std::string nameOfCategory(GraphicCategory category);
};


};


#endif
