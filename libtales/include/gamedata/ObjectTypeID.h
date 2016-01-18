#ifndef OBJECTTYPEID_H
#define OBJECTTYPEID_H


#include <string>

namespace Tales {


/**
 * Storage for enum of Tails Adventure object type identifiers.
 */
class ObjectTypeIDs {
public:
  /**
   * Maximum ID of regular gameplay objects, plus one.
   */
  const static int objectTypeIDLimit = 0x6D;
  
  /**
   * Maximum possible object type ID plus one.
   */
  const static int realobjectTypeIDLimit = 0x100;

  /**
   * Enum of Tails Adventure object type identifiers.
   */
  enum ObjectTypeID {
    null                 = 0x00, /**< No object. */
    tails                = 0x01, /**< Tails. */
    remoteRobot          = 0x02, /**< Remote robot. */
    extraArmorStars      = 0x03, /**< Invincibility stars and effect. */
    itemPickupLabel      = 0x04, /**< Label for obtained items. */
    ring                 = 0x05, /**< Ring. */
//    unknown06       = 0x06, /**< Unknown, probably invalid. */
    debris               = 0x07, /**< Flying debris (from tile explosion?). */
    warp                 = 0x08, /**< Inter-map warp. */
    waterSplash          = 0x09, /**< Splash when entering water. */
    waterRipples         = 0x0A, /**< Waterline ripple effect. */
    cutsceneAutomation   = 0x0B, /**< Handles automation for some cutscenes. */
    tailsHouseClaw       = 0x0C, /**< Claw in dock at Tails' House. */
    bombExplosion2       = 0x0D, /**< Dupe of bombExplosion? */
    bombExplosion        = 0x0E, /**< Bomb explosion effect. */
    bombExplosion3       = 0x0F, /**< Dupe of bombExplosion? */

    // Weapons
    regularBomb          = 0x10, /**< Regular bomb. Spawns @ Tails. */
    crouchingRegularBomb = 0x11, /**< Regular bomb, thrown while crouching? */
    giantBomb            = 0x12, /**< Giant bomb. Spawns @ Tails. */
    remoteBomb           = 0x13, /**< Remote bomb. Spawns @ Tails. */
    napalmBomb           = 0x14, /**< Napalm bomb. Spawns @ Tails. */
    tripleBomb           = 0x15, /**< Triple bomb. Spawns @ Tails. */
    hammer               = 0x16, /**< Hammer. Spawns @ Tails. */
    hammer2              = 0x17, /**< Duplicate of hammer? */
    hammer3              = 0x18, /**< Duplicate of hammer? */
    hammer4              = 0x19, /**< Duplicate of hammer? */
    hammer5              = 0x1A, /**< Duplicate of hammer? */
    protonTorpedo        = 0x1B, /**< Proton torpedo. Spawns @ Tails. */
    protonTorpedo2       = 0x1C, /**< Dupe of proton torpedo? */
    protonTorpedo3       = 0x1D, /**< Dupe of proton torpedo? */
    protonTorpedo4       = 0x1E, /**< Dupe of proton torpedo? */
    protonTorpedo5       = 0x1F, /**< Dupe of proton torpedo? */
    protonTorpedo6       = 0x20, /**< Dupe of proton torpedo? */
    protonTorpedo7       = 0x21, /**< Dupe of proton torpedo? */
    protonTorpedo8       = 0x22, /**< Dupe of proton torpedo? */
    vulcanCannon         = 0x23, /**< Vulcan cannon gunfire. Spawns @ Tails. */
    antiAirMissile       = 0x24, /**< Anti-air missile. Spawns @ Tails. */
    antiAirMissile2      = 0x25, /**< Dupe of anti-air missile? */
    antiAirMissile3      = 0x26, /**< Dupe of anti-air missile? */
    tailsMine            = 0x27, /**< Mine. Spawns @ Tails. */
    tailsMine2           = 0x28, /**< Dupe of tailsMine? */
    itemPickup2          = 0x29, /**< Dupe of item pickup? */
    itemPickup3          = 0x2A, /**< Dupe of item pickup? */
    itemPickup4          = 0x2B, /**< Dupe of item pickup? */
    itemPickup5          = 0x2C, /**< Dupe of item pickup? */
    itemPickup6          = 0x2D, /**< Dupe of item pickup? */
    itemPickup7          = 0x2E, /**< Dupe of item pickup? */
    itemPickup           = 0x2F,  /**< Item pickup. */
    
    // Enemy objects
    flyingMechDuck        = 0x30, /**< Flying duck mech. */
    walkingMechDuck       = 0x31, /**< Walking duck mech. */
    deadDuck              = 0x32, /**< Defeated enemy duck. */
    bomberMouse           = 0x33, /**< Bomb-dropping mouse. */
    staticGun2            = 0x34, /**< Fixed-position gun. */
    staticGun             = 0x35, /**< Duplicate of staticGun? */
    crouchingDuck         = 0x36, /**< Duck that crouches, rises, shoots. */
    drillRobot            = 0x37, /**< Hiding drill robot. */
    flyingBat             = 0x38, /**< Flying bat. */
    runningBomberDuck     = 0x39, /**< Bomb-throwing, running duck. */
    jumpingLava           = 0x3A, /**< Jumping lava drop. */
    gunnerDuck            = 0x3B, /**< Turret-mounted duck. */
    leapingDuck           = 0x3C, /**< Duck that leaps. */
    shootingFleeingDuck   = 0x3D, /**< Duck that shoots and flees? */
    rockThrowingDuck      = 0x3E, /**< Duck that throws rocks. */
    flyingShooterDuck     = 0x3F, /**< Duck that flies, shoots, repeats. */
    flyingBomberDuck      = 0x40, /**< Duck that flies, bombs, escapes */
    waterMine             = 0x41, /**< Undersea mine. */
    waterMissileLauncher  = 0x42, /**< Undersea missile launcher (10 dmg). */
    miniDuck              = 0x43, /**< Small, running duck. */
    conveyorBombSpawner   = 0x44, /**< Conveyor belt bomb dropper (1 dmg). */
    waterBirdLauncher     = 0x45, /**< Spawns birds that fly and damage. */
    conveyorDuck          = 0x46, /**< Duck that follows conveyors. */
    beehive               = 0x47, /**< Beehive that spawns bees. */
    robotKillBeams        = 0x48, /**< Periodic "lethal" damage to remobot. */
    rovingLaser           = 0x49, /**< Back-and-forth, downward lasers. */

    // Obstacles
    trapRoomBossDoor      = 0x4A, /**< Door blocking trap room boss exit. */
    electricField         = 0x4B, /**< Path-blocking electric field. */
    electricFieldSwitch   = 0x4C, /**< Switch for electric field. */
    seaFoxWeaponSmoke     = 0x4D, /**< Smoke puff when Sea Fox weapon used. */
    pushableRock          = 0x4E, /**< A pushable rock. */
    windGustEffect        = 0x4F, /**< A visual gust of wind. */
    
    // World map objects
    worldMapTitleCard     = 0x50, /**< World map level name box. */
    worldMapBigClouds     = 0x51, /**< World map big scenery clouds. */
    worldMapSmallClouds   = 0x52, /**< World map small scenery clouds. */
    worldMapBirds         = 0x53, /**< World map scenery birds. */
    worldMapDolphins      = 0x54, /**< World map scenery dolphins. */
    worldMapTailsIcon     = 0x55, /**< World map Tails head icon. */
//  unknown56     = 0x56, /**< Unknown. Tails in Sea Fox icon. Invalid? */
    worldMapFortress      = 0x57, /**< World map battle fortress scenery. */
    worldMapEntrance      = 0x58, /**< World map entrance flasher. */
    worldMapCutsceneObjs2 = 0x59, /**< Dupe of WM cutscene objects? */
    worldMapCutsceneObjs  = 0x5A, /**< World map cutscene objects. */
//  unknown5B     = 0x5B, /**< Unknown, probably invalid. */
    
    // Misc
    rollingLogSpawner     = 0x5C, /**< Rolling log/duck spawner. */
    spring                = 0x5D, /**< Spring. */
    elevator              = 0x5E, /**< Elevator that rises when stood on. */
//  unknown5F     = 0x5F, /**< Unknown, probably invalid. */
    
    // Bosses
    poloyForestBoss       = 0x60, /**< Poloy Forest walker mech boss. */
    cavernIslandBoss      = 0x61, /**< Cavern Island boss. */
    volcanicTunnelBoss    = 0x62, /**< Volcanic tunnel boss. */
    lakeRockyBoss         = 0x63, /**< Lake Rocky ship boss. */
    cocoIslandBoss        = 0x64, /**< Coco Island trap room boss. */
    pollyMt1Boss          = 0x65, /**< Polly Mt. 1 flying boss. */
    battleFortressBoss1   = 0x66, /**< Battle Fortress semifinal boss. */
    battleFortressBoss2   = 0x67, /**< Final boss. */
    
    // ?
//    unknown68     = 0x68, /**< Unknown, probably invalid. */
    cutsceneFlicky        = 0x69, /**< Flicky from intro/credits cutscenes. */
//    unknown6A     = 0x6A, /**< Unknown, probably invalid. */
    creditsRobot          = 0x6B, /**< Robot from the credits cutscene. */
    lakeRockyBossBomb     = 0x6C, /**< Lake Rocky boss bomb. */

    /* IDs 0x6D-0xFD = invalid? */
    
    /* There's some code that checks if object ID >= F0
       -- check more values */
    
    moribundObjectID      = 0xFE, /**< Object that needs to be killed. */
    deadObjectID          = 0xFF  /**< Dead object. */
  };
  
  /**
   * Returns a string identifier for a given object ID.
   * @return A string identifier for a given object ID.
   */
  static std::string nameOfObject(ObjectTypeID id);
  
  /**
   * Return true if the given object ID should be treated as valid.
   * @return True if the given object ID should be treated as valid.
   */
  static bool isObjectUsable(ObjectTypeID id);
  
protected:
  
};


};


#endif
