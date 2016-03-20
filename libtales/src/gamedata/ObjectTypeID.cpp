#include "gamedata/ObjectTypeID.h"

namespace Tales {


std::string ObjectTypeIDs::nameOfObject(ObjectTypeID id) {
  switch (id) {
  case ObjectTypeIDs::null:
    return "Null";
  case ObjectTypeIDs::tails:
    return "Tails";
  case ObjectTypeIDs::remoteRobot:
    return "Remote Robot";
  case ObjectTypeIDs::extraArmorStars:
    return "Extra Armor stars";
  case ObjectTypeIDs::itemPickupLabel:
    return "Item pickup label";
  case ObjectTypeIDs::ring:
    return "Ring";
  // skip 1 unknown object
  case ObjectTypeIDs::debris:
    return "Debris";
  case ObjectTypeIDs::warp:
    return "Warp";
  case ObjectTypeIDs::waterSplash:
    return "Water entry splash";
  case ObjectTypeIDs::waterRipples:
    return "Water ripple effect";
  case ObjectTypeIDs::cutsceneAutomation:
    return "Cutscene automation object";
  case ObjectTypeIDs::tailsHouseClaw:
    return "Tails' lab claw machine";
  case ObjectTypeIDs::bombExplosion2:
    return "Bomb explosion (dupe 2)";
  case ObjectTypeIDs::bombExplosion:
    return "Bomb explosion";
  case ObjectTypeIDs::bombExplosion3:
    return "Bomb explosion (dupe 3)";
  
  // Weapons
  case ObjectTypeIDs::regularBomb:
    return "Regular Bomb (dupe 2)";
  case ObjectTypeIDs::crouchingRegularBomb:
    return "Regular Bomb";
  case ObjectTypeIDs::giantBomb:
    return "Large Bomb";
  case ObjectTypeIDs::remoteBomb:
    return "Remote Bomb";
  case ObjectTypeIDs::napalmBomb:
    return "Napalm Bomb";
  case ObjectTypeIDs::tripleBomb:
    return "Triple Bomb";
  case ObjectTypeIDs::hammer:
    return "Hammer";
  case ObjectTypeIDs::hammer2:
    return "Hammer (dupe 2)";
  case ObjectTypeIDs::hammer3:
    return "Hammer (dupe 3)";
  case ObjectTypeIDs::hammer4:
    return "Hammer (dupe 4)";
  case ObjectTypeIDs::hammer5:
    return "Hammer (dupe 5)";
  case ObjectTypeIDs::protonTorpedo:
    return "Proton Torpedo";
  case ObjectTypeIDs::protonTorpedo2:
    return "Proton Torpedo (dupe 2)";
  case ObjectTypeIDs::protonTorpedo3:
    return "Proton Torpedo (dupe 3)";
  case ObjectTypeIDs::protonTorpedo4:
    return "Proton Torpedo (dupe 4)";
  case ObjectTypeIDs::protonTorpedo5:
    return "Proton Torpedo (dupe 5)";
  case ObjectTypeIDs::protonTorpedo6:
    return "Proton Torpedo (dupe 6)";
  case ObjectTypeIDs::protonTorpedo7:
    return "Proton Torpedo (dupe 7)";
  case ObjectTypeIDs::protonTorpedo8:
    return "Proton Torpedo (dupe 8)";
  case ObjectTypeIDs::vulcanCannon:
    return "Vulcan Cannon";
  case ObjectTypeIDs::antiAirMissile:
    return "Anti-Air Missile";
  case ObjectTypeIDs::antiAirMissile2:
    return "Anti-Air Missile (dupe 2)";
  case ObjectTypeIDs::antiAirMissile3:
    return "Anti-Air Missile (dupe 3)";
  case ObjectTypeIDs::tailsMine:
    return "Mine weapon";
  case ObjectTypeIDs::tailsMine2:
    return "Mine weapon (dupe 2)";
  case ObjectTypeIDs::itemPickup2:
    return "Item pickup (dupe 2)";
  case ObjectTypeIDs::itemPickup3:
    return "Item pickup (dupe 3)";
  case ObjectTypeIDs::itemPickup4:
    return "Item pickup (dupe 4)";
  case ObjectTypeIDs::itemPickup5:
    return "Item pickup (dupe 5)";
  case ObjectTypeIDs::itemPickup6:
    return "Item pickup (dupe 6)";
  case ObjectTypeIDs::itemPickup7:
    return "Item pickup (dupe 7)";
  case ObjectTypeIDs::itemPickup:
    return "Item pickup";
  
  // Enemy objects
  case ObjectTypeIDs::flyingMechDuck:
    return "Flying mech duck";
  case ObjectTypeIDs::walkingMechDuck:
    return "Walking mech duck";
  case ObjectTypeIDs::deadDuck:
    return "Dead duck";
  case ObjectTypeIDs::bomberMouse:
    return "Bomber mouse";
  case ObjectTypeIDs::staticGun:
    return "Fixed-position gun";
  case ObjectTypeIDs::staticGun2:
    return "Fixed-position gun (dupe 2)";
  case ObjectTypeIDs::crouchingDuck:
    return "Crouching duck";
  case ObjectTypeIDs::drillRobot:
    return "Drill robot";
  case ObjectTypeIDs::flyingBat:
    return "Bat robot";
  case ObjectTypeIDs::runningBomberDuck:
    return "Running bomber duck";
  case ObjectTypeIDs::jumpingLava:
    return "Flame shooter/lava";
  case ObjectTypeIDs::gunnerDuck:
    return "Turret duck";
  case ObjectTypeIDs::leapingDuck:
    return "Leaping duck";
  case ObjectTypeIDs::shootingFleeingDuck:
    return "Underwater shooter duck";
  case ObjectTypeIDs::rockThrowingDuck:
    return "Rock-throwing duck";
  case ObjectTypeIDs::flyingShooterDuck:
    return "Fighter duck";
  case ObjectTypeIDs::flyingBomberDuck:
    return "Flying bomber duck";
  case ObjectTypeIDs::waterMine:
    return "Underwater mine hazard";
  case ObjectTypeIDs::waterMissileLauncher:
    return "Underwater missile launcher";
  case ObjectTypeIDs::miniDuck:
    return "Mini duck";
  case ObjectTypeIDs::conveyorBombSpawner:
    return "Conveyor belt bomb spawner";
  case ObjectTypeIDs::waterBirdLauncher:
    return "Robot bird launcher";
  case ObjectTypeIDs::conveyorDuck:
    return "Conveyor-riding duck";
  case ObjectTypeIDs::beehive:
    return "Beehive";
  case ObjectTypeIDs::robotKillBeams:
    return "Remote Robot killer beams";
  case ObjectTypeIDs::rovingLaser:
    return "Coco Island boss laser";
    
  // Obstacles
  case ObjectTypeIDs::trapRoomBossDoor:
    return "Coco Island boss barriers";
  case ObjectTypeIDs::electricField:
    return "Electric barrier";
  case ObjectTypeIDs::electricFieldSwitch:
    return "Electric barrier switch";
  case ObjectTypeIDs::seaFoxWeaponSmoke:
    return "Sea Fox weapon smoke puff";
  case ObjectTypeIDs::pushableRock:
    return "Boulder";
  case ObjectTypeIDs::windGustEffect:
    return "Wind gust visual effect";
  
  // World map objects
  case ObjectTypeIDs::worldMapTitleCard:
    return "World map: title card";
  case ObjectTypeIDs::worldMapBigClouds:
    return "World map: big clouds";
  case ObjectTypeIDs::worldMapSmallClouds:
    return "World map: small clouds";
  case ObjectTypeIDs::worldMapBirds:
    return "World map: birds";
  case ObjectTypeIDs::worldMapDolphins:
    return "World map: dolphins";
  case ObjectTypeIDs::worldMapTailsIcon:
    return "World map: Tails icon";
  // Skip 1 unknown object
  case ObjectTypeIDs::worldMapFortress:
    return "World map: Battle Fortress";
  case ObjectTypeIDs::worldMapEntrance:
    return "World map: level entrance flasher";
  case ObjectTypeIDs::worldMapCutsceneObjs2:
    return "World map: cutscene objects (dupe 2)";
  case ObjectTypeIDs::worldMapCutsceneObjs:
    return "World map: cutscene objects";
  
  // Misc
  case ObjectTypeIDs::rollingLogSpawner:
    return "Rolling log spawner";
  case ObjectTypeIDs::spring:
    return "Spring";
  case ObjectTypeIDs::elevator:
    return "Floating platform";
  
  // Bosses
  case ObjectTypeIDs::poloyForestBoss:
    return "Poloy Forest boss";
  case ObjectTypeIDs::cavernIslandBoss:
    return "Cavern Island boss";
  case ObjectTypeIDs::volcanicTunnelBoss:
    return "Volcanic Tunnel boss";
  case ObjectTypeIDs::lakeRockyBoss:
    return "Lake Rocky boss";
  case ObjectTypeIDs::cocoIslandBoss:
    return "Coco Island boss";
  case ObjectTypeIDs::pollyMt1Boss:
    return "Polly Mt 1 boss";
  case ObjectTypeIDs::battleFortressBoss1:
    return "Battle Fortress semifinal boss";
  case ObjectTypeIDs::battleFortressBoss2:
    return "Battle Fortress final boss";
  
  // ?
  // Skip 1 unknown object
  case ObjectTypeIDs::cutsceneFlicky:
    return "Intro/credits cutscene Flicky";
  // Skip 1 unknown object
  case ObjectTypeIDs::creditsRobot:
    return "Credits robot";
  case ObjectTypeIDs::lakeRockyBossBomb:
    return "Lake Rocky boss bomb";
    
  case ObjectTypeIDs::moribundObjectID:
    return "Moribund object identifier";
  case ObjectTypeIDs::deadObjectID:
    return "Dead object identifier";
  
  default:
    return "***ERROR TYPE***";
  }
}

bool ObjectTypeIDs::isObjectUsable(ObjectTypeID id) {
  // Disallow unused/reserved IDs
  if ((int)id >= objectTypeIDLimit) {
    return false;
  }

  switch (id) {
  // Disallow troublesome objects
  case tails:
  case remoteRobot:
  // Disallow duplicates
  case bombExplosion2:
  case bombExplosion3:
  case hammer2:
  case hammer3:
  case hammer4:
  case hammer5:
  case protonTorpedo2:
  case protonTorpedo3:
  case protonTorpedo4:
  case protonTorpedo5:
  case protonTorpedo6:
  case protonTorpedo7:
  case protonTorpedo8:
  case antiAirMissile2:
  case antiAirMissile3:
  case tailsMine2:
  case itemPickup2:
  case itemPickup3:
  case itemPickup4:
  case itemPickup5:
  case itemPickup6:
  case itemPickup7:
  case staticGun2:
  case worldMapCutsceneObjs2:
    return false;
  default:
    break;
  }

  switch ((int)id) {
  // Disallow unknown IDs
  case 0x00:
  case 0x06:
  case 0x10:
  case 0x56:
  case 0x5B:
  case 0x5F:
  case 0x68:
  case 0x6A:
    return false;
  default:
    break;
  }
  
  return true;
}


};
