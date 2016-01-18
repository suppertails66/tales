#ifndef SOUNDID_H
#define SOUNDID_H


#include <string>

namespace Tales {


class SoundIDs {
public:
  enum SoundID {
    null                       = 0x00,
    
    // Music
    trackPlaying               = 0x80,
    titleMusic                 = 0x81,
    poloyForestMusic           = 0x82,
    undergroundMusic           = 0x83,
    pollyMtnMusic              = 0x84,
    cocoIslandMusic            = 0x85,
    underwaterMusic            = 0x86,
    battleFortressMusic        = 0x87,
    worldMapMusic              = 0x88,
    tailsHouseMusic            = 0x89,
    passwordMusic              = 0x8A,
    seaFoxCutsceneMusic        = 0x8B,
    radioOnlyMusic             = 0x8C,
    bossMusic                  = 0x8D,
    finalBossMusic             = 0x8E,
    gameOverMusic              = 0x8F,
    deathMusic                 = 0x90,
    blankMusic1                = 0x91,
    introPart1Music            = 0x92,
    endingMusic                = 0x93,
    creditsMusic               = 0x94,
    caronForestMusic           = 0x95,
    blankMusic2                = 0x96,
    introPart2Music            = 0x97,
    introPart3Music            = 0x98,
    blankMusic3                = 0x99,
    introPart4Music            = 0x9A,
    
    // these are probably junk -- stop playing music
    // and generally play looping garbage
    se9B                       = 0x9B,
    se9C                       = 0x9C,
    se9D                       = 0x9D,
    se9E                       = 0x9E,
    se9F                       = 0x9F,
    
    // Sound effects
    nullSound                  = 0xA0,
    worldMapMove               = 0xA1,
    tailsHouseChooseOption     = 0xA2,
    tailsJump                  = 0xA3,
    seA4                       = 0xA4,
    seA5                       = 0xA5,
    tailsFly                   = 0xA6,
    seA7                       = 0xA7,
    ringCollect                = 0xA8,
    tailsHouseChooseItem       = 0xA9,
    seAA                       = 0xAA,
    seAB                       = 0xAB,
    seAC                       = 0xAC,
    seAD                       = 0xAD,
    seAE                       = 0xAE,
    seAF                       = 0xAF,
    tailsDamage                = 0xB0,
    seB1                       = 0xB1,
    waterSplash                = 0xB2,
    seB3                       = 0xB3,
    seB4                       = 0xB4,
    seB5                       = 0xB5,
    bombExplosion              = 0xB6,
    seB7                       = 0xB7,
    seB8                       = 0xB8,
    breakBlock                 = 0xB9,
    seBA                       = 0xBA,
    damageBoss                 = 0xBB,
    damageBossDupe             = 0xBC,
    seBD                       = 0xBD,
    seBE                       = 0xBE,
    seBF                       = 0xBF,
    itemRadar                  = 0xC0,
    bossLaugh                  = 0xC1, // ?
    waterSplashDupe            = 0xC2, // ??? slightly different?
    seC3                       = 0xC3,
    getEmerald                 = 0xC4,
    getItem                    = 0xC5,
    seC6                       = 0xC6,
    seC7                       = 0xC7,
    seC8                       = 0xC8,
    seC9                       = 0xC9,
    sonicCharge                = 0xCA,
    sonicRelease               = 0xCB,
    seCC                       = 0xCC,
    skid                       = 0xCD,
    seCE                       = 0xCE,
    titleOptionSelect          = 0xCF,
    seD0                       = 0xD0,
    seD1                       = 0xD1,
    seD2                       = 0xD2,
    seD3                       = 0xD3,
    greenDuckLaugh             = 0xD4,
    extraSpeed                 = 0xD5,
    
    // Music effects
    fadeOutSounds              = 0xE0,
    stopAllSounds              = 0xE1,
    stopSoundEffects           = 0xE2,
  };
  
  /**
   * Lowest valid music ID.
   */
  const static int musicLowerLimit = 0x80;
  
  /**
   * Highest valid music ID plus one.
   */
  const static int musicUpperLimit = 0x9B;
  
  /**
   * Returns the name corresponding to a music track.
   * @return The name corresponding to a music track.
   */
  static std::string nameOfMusicID(SoundID musicID);
};


};


#endif
