#include "editors/GraphicToInfo.h"

namespace Tales {


GraphicInfo GraphicToInfo::compressedGraphicInfo(int index) {
  return compressedGraphicInfos[index];
}
  
std::string GraphicToInfo::nameOfCompressedGraphic(int index) {
  return compressedGraphicInfo(index).name();
}
  
GraphicCategories::GraphicCategory
    GraphicToInfo::categoryOfCompressedGraphic(int index) {
  return compressedGraphicInfo(index).graphicCategory();
}

GraphicInfo GraphicToInfo::uncompressedGraphicInfo(int index) {
  return uncompressedGraphicInfos[index];
}
  
std::string GraphicToInfo::nameOfUncompressedGraphic(int index) {
  return uncompressedGraphicInfo(index).name();
}
  
GraphicCategories::GraphicCategory
    GraphicToInfo::categoryOfUncompressedGraphic(int index) {
  return uncompressedGraphicInfo(index).graphicCategory();
}

const GraphicInfo GraphicToInfo
    ::compressedGraphicInfos[numCompressedGraphicInfos] = {
  // 0
  GraphicInfo("HUD", GraphicCategories::interface),
  GraphicInfo("Regular bomb", GraphicCategories::weapon),
  GraphicInfo("Item pickup", GraphicCategories::misc),
  GraphicInfo("Flying mech duck", GraphicCategories::enemy),
  GraphicInfo("Walking mech duck", GraphicCategories::enemy),
  GraphicInfo("Bomber mouse", GraphicCategories::enemy),
  GraphicInfo("Fixed-position gun", GraphicCategories::enemy),
  GraphicInfo("Crouching duck", GraphicCategories::enemy),
  GraphicInfo("Drill robot", GraphicCategories::enemy),
  GraphicInfo("Leaf", GraphicCategories::effect),
  // 10
  GraphicInfo("Spring", GraphicCategories::obstacle),
  GraphicInfo("Bat robot", GraphicCategories::enemy),
  GraphicInfo("Running bomber duck", GraphicCategories::enemy),
  GraphicInfo("Leaping duck", GraphicCategories::enemy),
  GraphicInfo("Underwater shooter duck", GraphicCategories::enemy),
  GraphicInfo("Rock thrower duck", GraphicCategories::enemy),
  GraphicInfo("Flying bomber duck", GraphicCategories::enemy),
  GraphicInfo("Underwater mine hazard", GraphicCategories::enemy),
  GraphicInfo("Underwater missile", GraphicCategories::enemy),
  GraphicInfo("Mini duck", GraphicCategories::enemy),
  // 20
  GraphicInfo("Underwater bird missile", GraphicCategories::enemy),
  GraphicInfo("Turret duck", GraphicCategories::enemy),
  GraphicInfo("Boulder", GraphicCategories::obstacle),
  GraphicInfo("Remote Robot killer beams", GraphicCategories::enemy),
  GraphicInfo("Conveyor bomb", GraphicCategories::enemy),
  GraphicInfo("Conveyor-riding duck", GraphicCategories::enemy),
  GraphicInfo("Water entry splash", GraphicCategories::effect),
  GraphicInfo("Coco Island boss laser", GraphicCategories::enemy),
  GraphicInfo("Coco Island boss barriers", GraphicCategories::obstacle),
  GraphicInfo("Electric barrier", GraphicCategories::obstacle),
  // 30
  GraphicInfo("Electric barrier switch", GraphicCategories::obstacle),
  GraphicInfo("Flame shooter/lava", GraphicCategories::enemy),
  GraphicInfo("Beehive", GraphicCategories::enemy),
  GraphicInfo("Polly Mt 2 fire wind", GraphicCategories::effect),
  GraphicInfo("World map objects", GraphicCategories::misc),
  GraphicInfo("Sea Fox smoke puff", GraphicCategories::effect),
  GraphicInfo("Water ripple effect", GraphicCategories::effect),
  GraphicInfo("Dead duck", GraphicCategories::misc),
  GraphicInfo("Log roller duck", GraphicCategories::enemy),
  // 40
  GraphicInfo("Fighter duck", GraphicCategories::enemy),
  GraphicInfo("Fighter duck, no bullets", GraphicCategories::enemy),
  GraphicInfo("Floating platform", GraphicCategories::obstacle),
  GraphicInfo("Poloy Forest boss", GraphicCategories::boss),
  GraphicInfo("Coco Island boss", GraphicCategories::boss),
  GraphicInfo("Polly Mt 1 boss", GraphicCategories::boss),
  GraphicInfo("Remote Robot (cutscene)", GraphicCategories::cutscene),
  GraphicInfo("Remote Robot transform", GraphicCategories::cutscene),
  GraphicInfo("Flicky", GraphicCategories::cutscene),
  GraphicInfo("Burnt Flicky", GraphicCategories::cutscene),
  GraphicInfo("Credits robot", GraphicCategories::cutscene),
  // 50
  GraphicInfo("Volcanic Tunnel boss projectiles", GraphicCategories::boss),
  GraphicInfo("Cavern Island boss", GraphicCategories::boss),
  GraphicInfo("Cavern Island boss pieces", GraphicCategories::boss),
  GraphicInfo("Lake Rocky boss", GraphicCategories::boss),
  GraphicInfo("Battle Fortress boss 1", GraphicCategories::boss),
  GraphicInfo("Tails' House grabber claw", GraphicCategories::misc),
  GraphicInfo("Item pickup 2", GraphicCategories::misc),
  GraphicInfo("Tails' House item icons", GraphicCategories::interface),
  GraphicInfo("Remote Robot item icon", GraphicCategories::interface),
  GraphicInfo("Destructible tile debris", GraphicCategories::effect),
  // 60
  GraphicInfo("Destructible tile debris 2", GraphicCategories::effect),
  GraphicInfo("Destructible tile debris 3", GraphicCategories::effect),
  GraphicInfo("Destructible tile debris 4", GraphicCategories::effect),
  GraphicInfo("Sega logo", GraphicCategories::interface),
  GraphicInfo("Level select font [unused]", GraphicCategories::interface),
  GraphicInfo("Forest level graphics", GraphicCategories::level),
  GraphicInfo("Mountain level graphics", GraphicCategories::level),
  GraphicInfo("Title screen graphics", GraphicCategories::interface),
  GraphicInfo("World map level graphics", GraphicCategories::misc),
  GraphicInfo("Tails' House level graphics", GraphicCategories::interface),
  // 70
  GraphicInfo("Tunnel level graphics", GraphicCategories::level),
  GraphicInfo("Cavern Island boss graphics", GraphicCategories::level),
  GraphicInfo("Water level graphics", GraphicCategories::level),
  GraphicInfo("Password", GraphicCategories::interface),
  GraphicInfo("Password selector", GraphicCategories::interface),
  GraphicInfo("Game over", GraphicCategories::interface),
  GraphicInfo("Fortress level graphics", GraphicCategories::level),
  GraphicInfo("Flight level graphics", GraphicCategories::level),
  GraphicInfo("Credits", GraphicCategories::interface),
  GraphicInfo("Lake Rocky boss level graphics", GraphicCategories::level),
  // 80
  GraphicInfo("Tails' House English",  GraphicCategories::interface)
};

const GraphicInfo GraphicToInfo::uncompressedGraphicInfos[
    numUncompressedGraphicInfos] =
  {
    // 0
    GraphicInfo("Tails (Sonic item, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (ledge dangle, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (ledge dangle, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (ledge dangle, 3)", GraphicCategories::tails),
    GraphicInfo("Tails (idle, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (damaged, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (regular flight, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (regular flight, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (regular flight, 3)", GraphicCategories::tails),
    GraphicInfo("Tails (full-power flight, 1)", GraphicCategories::tails),
    // 10
    GraphicInfo("Tails (full-power flight, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (full-power flight, 3)", GraphicCategories::tails),
    GraphicInfo("Tails (equipping Helmet, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (equipping Helmet, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (under Helmet, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (under Helmet, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (under Helmet, 3)", GraphicCategories::tails),
    GraphicInfo("Tails (under Helmet, 4)", GraphicCategories::tails),
    GraphicInfo("Tails (under Helmet, 5)", GraphicCategories::tails),
    GraphicInfo("Tails (using Wrench, 1)", GraphicCategories::tails),
    // 20
    GraphicInfo("Tails (using Wrench, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (using Wrench, 3)", GraphicCategories::tails),
    GraphicInfo("Tails (skidding, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (skidding, 2)", GraphicCategories::tails),
    GraphicInfo("Tails (jumping, 1)", GraphicCategories::tails),
    GraphicInfo("Tails (throw object while jumping?, 1)",
                GraphicCategories::tails),
    GraphicInfo("Tails (throw object while jumping?, 2)",
                GraphicCategories::tails),
    GraphicInfo("Tails (throw object while jumping?, 3)",
                GraphicCategories::tails),
    GraphicInfo("Tails (throw bomb while jumping, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throw bomb while jumping, 2)",
                 GraphicCategories::tails),
    // 30
    GraphicInfo("Tails (throw bomb while jumping, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throw bomb while jumping, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (rotating fall, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 2)",
                 GraphicCategories::tails),
    // 40
    GraphicInfo("Tails (spinning in circle, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (spinning in circle, 7)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (looking up, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (repairing credits robot, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (repairing credits robot, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (picking up item, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (picking up item, 2)",
                 GraphicCategories::tails),
    // 50
    GraphicInfo("Tails (picking up item, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (balancing on ledge, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (balancing on ledge, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (balancing on ledge, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (pushing, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (pushing, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (pushing, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (running, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (running, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (running, 3)",
                 GraphicCategories::tails),
    // 60
    GraphicInfo("Tails (running, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (running, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (running, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dying, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dying, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dying, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (using Remote Robot, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (using Remote Robot, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (using Remote Robot, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (Sonic item, 2)",
                 GraphicCategories::tails),
    // 70
    GraphicInfo("Tails (Sonic item, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (Sonic item, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (Sonic item, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (Sonic item, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (crouching, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (standing, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (climbing ledge, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (climbing ledge, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (climbing ledge, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (climbing ledge, 4)",
                 GraphicCategories::tails),
    // 80
    GraphicInfo("Tails (throwing bomb while standing, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing bomb while standing, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing bomb while standing, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing bomb while standing, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (picking up with Super Glove, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (picking up with Super Glove, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (picking up with Super Glove, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (tired flight, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (tired flight, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (tired flight, 3)",
                 GraphicCategories::tails),
    // 90
    GraphicInfo("Tails (throwing with Super Glove, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing with Super Glove, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing with Super Glove, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (throwing with Super Glove, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dropping bomb while flying, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dropping bomb while flying, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (dropping bomb while flying, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (carrying with Super Glove, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (carrying with Super Glove, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (carrying with Super Glove, 3)",
                 GraphicCategories::tails),
    // 100
    GraphicInfo("Tails (carrying with Super Glove, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (carrying with Super Glove, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (carrying with Super Glove, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (walking, 6)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (blinking, 1)",
                 GraphicCategories::tails),
    // 110
    GraphicInfo("Tails (blinking, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 4)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 5)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 6)",
                 GraphicCategories::tails),
    GraphicInfo("? [unused?]",
                 GraphicCategories::tails),
    GraphicInfo("Tails (idling, 7)",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (idling, 1)",
                 GraphicCategories::tails),
    // 120
    GraphicInfo("Sea Fox (idling, 2)",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turn down, 1 [unused])",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turn down, 2 [unused])",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turn up, 1 [unused])",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turn up, 2 [unused])",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turning, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Sea Fox (turning, 2 [unused])",
                 GraphicCategories::tails),
    GraphicInfo("Tails (grabbed by final boss, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (burnt, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (burnt, 2)",
                 GraphicCategories::tails),
    // 130
    GraphicInfo("Tails (burnt, 3)",
                 GraphicCategories::tails),
    GraphicInfo("Tails (sleeping, 1)",
                 GraphicCategories::tails),
    GraphicInfo("Remote Robot (walking, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (walking, 2)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (walking, 3)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (walking, 4)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (standing, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (blinking, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (blinking, 2)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (blinking, 3)",
                 GraphicCategories::remoteRobot),
    // 140
    GraphicInfo("Remote Robot (?, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (?, 2)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 2)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 3)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 4)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 5)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 6)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 7)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 8)",
                 GraphicCategories::remoteRobot),
    // 150
    GraphicInfo("Remote Robot (entering flight mode, 9)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (entering flight mode, 10)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (flying, 1)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Remote Robot (flying, 2)",
                 GraphicCategories::remoteRobot),
    GraphicInfo("Proton Torpedo",
                 GraphicCategories::weapon),
    GraphicInfo("Mine item",
                 GraphicCategories::weapon),
    GraphicInfo("Vulcan Cannon",
                 GraphicCategories::weapon),
    GraphicInfo("Flight meter 12/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 11/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 10/12",
                 GraphicCategories::interface),
    // 160
    GraphicInfo("Flight meter 9/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 8/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 7/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 6/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 5/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 4/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 3/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 2/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 1/12",
                 GraphicCategories::interface),
    GraphicInfo("Flight meter 0/12",
                 GraphicCategories::interface),
    // 170
    GraphicInfo("Empty inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Regular Bomb inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Large Bomb inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Remote Bomb inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Napalm Bomb inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Triple Bomb inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Wrench inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Helmet inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Item Radar inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Radio inventory icon",
                 GraphicCategories::interface),
    // 180
    GraphicInfo("Hammer inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Teleport Device inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Night Vision inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Speed Boots inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Super Glove inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Fang inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Knuckles inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Sonic inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Proton Torpedo inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Vulcan Cannon inventory icon",
                 GraphicCategories::interface),
    // 190
    GraphicInfo("Extra Speed inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Extra Armor inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Anti-Air Missile inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Spark inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Mine inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Rocket Booster inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Remote Robot inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Flipping inventory icon 1",
                 GraphicCategories::interface),
    GraphicInfo("Flipping inventory icon 2",
                 GraphicCategories::interface),
    GraphicInfo("Flipping inventory icon 3",
                 GraphicCategories::interface),
    // 200
    GraphicInfo("Regular Bomb",
                 GraphicCategories::interface),
    GraphicInfo("Napalm Bomb",
                 GraphicCategories::interface),
    GraphicInfo("Anti-Air Missile",
                 GraphicCategories::interface),
    GraphicInfo("Hammer",
                 GraphicCategories::interface),
    GraphicInfo("Tails' House title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Poloy Forest title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Caron Forest title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Volcanic Tunnel title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Polly Mt. 1 title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Polly Mt. 2 title card (JP)",
                 GraphicCategories::interface),
    // 210
    GraphicInfo("Lake Rocky title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Lake Crystal title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Green Island title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Cavern Island title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Coco Island title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Battle Fortress 1 title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Battle Fortress 2 title card (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Final boss",
                 GraphicCategories::boss),
    GraphicInfo("Final boss bombs",
                 GraphicCategories::boss),
    GraphicInfo("Extra armor stars",
                 GraphicCategories::boss),
    // 220
    GraphicInfo("Green Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("White Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Red Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Blue Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Purple Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Yellow Chaos Emerald inventory icon",
                 GraphicCategories::interface),
    GraphicInfo("Lake Crystal water cycle 1",
                 GraphicCategories::level),
    GraphicInfo("Lake Crystal water cycle 2",
                 GraphicCategories::level),
    GraphicInfo("Lake Crystal water cycle 3",
                 GraphicCategories::level),
    GraphicInfo("Lake Crystal water cycle 4",
                 GraphicCategories::level),
    // 230
    GraphicInfo("Conveyor cycle 1",
                 GraphicCategories::level),
    GraphicInfo("Conveyor cycle 2",
                 GraphicCategories::level),
    GraphicInfo("Speed Boots item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Chaos Emerald item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Triple Bomb item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Spark item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Fang item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Large Bomb item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Hammer item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Helmet item label (JP)",
                 GraphicCategories::interface),
    // 240
    GraphicInfo("Item Radar item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Extra Speed item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Mine item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Knuckles item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Extra Armor item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Vulcan Missile item label (JP) [unused]",
                 GraphicCategories::interface),
    GraphicInfo("Napalm Bomb item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Proton Torpedo item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Radio item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Remote Bomb item label (JP)",
                 GraphicCategories::interface),
    // 250
    GraphicInfo("Rocket Booster item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Night Vision item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Sonic item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Wrench item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Super Glove item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Teleport Device item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Anti-Air Missile item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Remote Robot item label (JP)",
                 GraphicCategories::interface),
    GraphicInfo("Tails' House title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Poloy Forest title card (EN)",
                 GraphicCategories::interface),
    // 260
    GraphicInfo("Caron Forest title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Volcanic Tunnel title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Polly Mt. 1 title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Polly Mt. 2 title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Lake Rocky title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Lake Crystal title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Green Island title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Cavern Island title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Coco Island title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Battle Fortress 1 title card (EN)",
                 GraphicCategories::interface),
    // 270
    GraphicInfo("Battle Fortress 2 title card (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Cavern Island boss graphics?",
                 GraphicCategories::boss),
    GraphicInfo("Remote Robot transformation dupe?",
                 GraphicCategories::misc),
    GraphicInfo("Speed Boots item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Chaos Emerald item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Triple Bomb item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Spark item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Fang item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Large Bomb item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Hammer item label (EN)",
                 GraphicCategories::interface),
    // 280
    GraphicInfo("Helmet item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Item Radar item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Extra Speed item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Mine item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Knuckles item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Extra Armor item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Vulcan Missile item label (EN) [unused]",
                 GraphicCategories::interface),
    GraphicInfo("Napalm Bomb item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Proton Torpedo item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Radio item label (EN)",
                 GraphicCategories::interface),
    // 290
    GraphicInfo("Remote Bomb item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Rocket Booster item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Night Vision item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Sonic item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Wrench item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Super Glove item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Teleport Device item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Anti-Air Missile item label (EN)",
                 GraphicCategories::interface),
    GraphicInfo("Remote Robot item label (EN)",
                 GraphicCategories::interface),
    
  };
  
/*const std::string GraphicToInfo
    ::compressedGraphicNames[numCompressedGraphicNames] = {
  // 0
  "HUD",
  "Regular bomb",
  "Item pickup",
  "Flying mech duck",
  "Walking mech duck",
  "Bomber mouse",
  "Fixed-position gun",
  "Crouching duck",
  "Drill robot",
  "Leaf",
  // 10
  "Spring",
  "Bat robot",
  "Running bomber duck",
  "Leaping duck",
  "Underwater shooter duck",
  "Rock thrower duck",
  "Flying bomber duck",
  "Underwater mine hazard",
  "Underwater missile",
  "Mini duck",
  // 20
  "Underwater bird missile",
  "Turret duck",
  "Pushable boulder",
  "Remote Robot killer beams",
  "Conveyor bomb",
  "Conveyor duck",
  "Water splash",
  "Coco Island boss laser",
  "Coco Island boss barriers",
  "Electric barrier",
  // 30
  "Electric barrier switch",
  "Flame shooter",
  "Beehive",
  "Polly Mt 2 fire wind",
  "World map objects",
  "Sea Fox smoke puff",
  "Water ripple effect",
  "Dead duck",
  "Log roller duck",
  // 40
  "Cavern Island boss",
  "Cavern Island boss 2",
  "Floating platform",
  "Poloy Forest boss",
  "Coco Island boss",
  "Polly Mt 1 boss",
  "Remote Robot (cutscene)",
  "Remote Robot transform",
  "Flicky",
  "Burnt Flicky",
  "Credits robot",
  // 50
  "Volcanic Tunnel boss projectiles",
  "Cavern Island boss",
  "Cavern Island boss pieces",
  "Lake Rocky boss",
  "Battle Fortress boss 1",
  "Tails' House grabber claw",
  "Item pickup 2",
  "Tails' House item icons",
  "Remote Robot item icon",
  "Destructable tile debris",
  // 60
  "Destructable tile debris 2",
  "Destructable tile debris 3",
  "Destructable tile debris 4",
  "Sega logo",
  "Level select font [unused]",
  "Forest level graphics",
  "Mountain level graphics",
  "Title screen graphics",
  "World map level graphics",
  "Tails' House level graphics",
  // 70
  "Tunnel level graphics",
  "Tunnel level graphics 2",
  "Water level graphics",
  "Password",
  "Password selector",
  "Game over",
  "Fortress level graphics",
  "Flight level graphics",
  "Credits",
  "forgot",
  // 80
  "Tails' House English"
}; */


}; 
