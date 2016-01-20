#ifndef TAILSADVBANK0HACKS_H
#define TAILSADVBANK0HACKS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"

namespace Tales {


class TailsAdvBank0Hacks {
public:
  /**
   * Adds the level header relocation hack to the given ROM.
   * This allows levels to be loaded from a location outside slots 1 and 2.
   * @param rom ROM to write to.
   * @param levelHeaderAddress Address of the level header table.
   * @param codeCopyBase Address to which to copy necessary code from bank 2.
   */
  static void addLevelHeaderHack(
                     WritableROM& rom,
                     Taddress levelHeaderAddress,
                     Taddress codeCopyBase);
  
  /**
   * Adds the double jump fix hack to the given ROM.
   * This fixes a bug in the game where jumping and falling for 256 frames
   * while holding the A button will cause Tails to "double jump" in midair.
   * @param rom ROM to write to.
   */
  static void addDoubleJumpFixHack(
                     WritableROM& rom);
  
  /**
   * Adds the Button 1 max jump height fix to the given ROM.
   * This fixes a bug in the game where holding Button 1 (the item button)
   * while jumping will cause Tails to always jump to the maximum height
   * possible.
   * @param rom ROM to write to.
   */
  static void addButton1MaxHeightFixHack(
                     WritableROM& rom);
  
  /**
   * Adds the bomb throw while jumping graphic fix to the given ROM.
   * This fixes a bug in the game that causes the last frame of Tails'
   * throwing-a-bomb-while-jumping animation to display incorrectly.
   * @param rom ROM to write to.
   */
  static void addBombWhileJumpingGraphicFixHack(
                     WritableROM& rom);
  
  /**
   * Adds the use all inventory hack to the given ROM.
   * This allows all obtained items to be used without having to equip them
   * at Tails' house first.
   * @param rom ROM to write to.
   */
  static void addUseAllInventoryHack(
                     WritableROM& rom);
  
  /**
   * Adds the full inventory hotswap hack to the given ROM.
   * This allows all obtained items to be used without having to equip them
   * at Tails' house first, and adds a "hotswap" system for switching
   * between them on the pause screen.
   * This is mutually exclusive with the addFullInventoryHotswapHack()
   * function, which does not allow use of all inventory items.
   * Do not use both on the same WritableROM.
   * @param rom ROM to write to.
   * @see addRegularInventoryHotswapHack()
   */
  static void addFullInventoryHotswapHack(
                     WritableROM& rom);
  
  /**
   * Adds the full inventory hotswap hack to the given ROM.
   * This adds a "hotswap" system for switching between items on the pause
   * screen.
   * This is mutually exclusive with the addRegularInventoryHotswapHack()
   * function, which does not allow use of all inventory items.
   * Do not use both on the same WritableROM.
   * @param rom ROM to write to.
   * @see addFullInventoryHotswapHack()
   */
  static void addRegularInventoryHotswapHack(
                     WritableROM& rom);
  
  /**
   * Adds the flight limiter hack to the given ROM.
   * Incompatible with addFlightDisableHack().
   * @param rom ROM to write to.
   */
  static void addFlightLimiterHack(
                     WritableROM& rom);
  
  /**
   * Adds the flight disable hack to the given ROM.
   * Incompatible with addFlightLimiterHack().
   * @param rom ROM to write to.
   */
  static void addFlightDisableHack(
                     WritableROM& rom);

protected:

  // Level header table relocation hack

  /**
   * "Base address" of hacks.
   * This is the address of the free space at the end of bank 0.
   */
  const static Taddress bank0FillerAddress = 0x7D09;
  
  // Level header hack consts
  
  /**
   * Address of the level header address table location hack.
   */
  const static Taddress levelHeaderHackAddress = bank0FillerAddress;
  
  /**
   * Length of the level header address table location hack.
   */
  const static Taddress levelHeaderHackLength = 11;
  
  /**
   * Data for the level header address table location hack.
   */
  const static Tbyte levelHeaderHackData[levelHeaderHackLength];
  
  /**
   * Return address of the level header address table location hack.
   */
  const static Taddress levelHeaderHackReturnAddress = 0x7432;
  
  /**
   * Offset in levelHeaderHackData of the new level header table bank.
   */
  const static Taddress levelHeaderHackBankOffset = 1;
  
  /**
   * Offset in levelHeaderHackData of the new level header table address.
   */
  const static Taddress levelHeaderHackAddressOffset = 6;
  
  /**
   * Address of the level header address table location hack trigger.
   */
  const static Taddress levelHeaderHackTriggerAddress = 0x742F;
  
  /**
   * Length of the level header address table location hack trigger.
   */
  const static Taddress levelHeaderHackTriggerLength = 3;
  
  /**
   * Data for the level header address table location hack trigger.
   */
  const static Tbyte levelHeaderHackTriggerData[levelHeaderHackTriggerLength];
  
  /**
   * Offset in levelHeaderHackTriggerData of the hack address.
   */
//  const static Taddress levelHeaderHackTriggerAddressOffset = 1;
  
  /**
   * 
   */
  const static Taddress levelHeaderHackSlotChangeJumpAddress = 0x7428;
  const static Taddress levelHeaderHackSlotChangeJumpAddressOffset = 1;
  
  const static Taddress levelHeaderHackSlotChangeJumpLength = 3;
  
  const static Tbyte levelHeaderHackSlotChangeJumpData[
                                levelHeaderHackSlotChangeJumpLength];
                                
                                
  
  const static Taddress levelHeaderHackSlotChangeBankAddress = 0x7428;
  
  /**
   * Length of the level header address table location hack.
   */
  const static Taddress levelHeaderHackSlotChangeBankLength = 8;
  
  /**
   * Data for the level header address table location hack.
   */
  const static Tbyte levelHeaderHackSlotChangeBankData[
                                levelHeaderHackSlotChangeBankLength];
  
  const static Taddress levelHeaderHackSlotChangeBankBankOffset = 1;
  
  const static Taddress levelHeaderHackSlotChangeBankAddressOffset = 6;
  
  
  
  /**
   * Length of the level header address table location hack.
   */
  const static Taddress levelHeaderHackSlotChangeBank2Length = 9;
  
  /**
   * Data for the level header address table location hack.
   */
  const static Tbyte levelHeaderHackSlotChangeBank2Data[
                                levelHeaderHackSlotChangeBank2Length];
  
  const static Taddress levelHeaderHackSlotChangeBank2AddressOffset = 7;
  
  
  
  /**
   * First copy address.
   */
  const static Taddress levelHeaderHackSlotChangeCopy1Address = 0x7428;
  
  const static Taddress levelHeaderHackSlotChangeCopy1EndAddress = 0x7480;
  
  /**
   * First copy length.
   */
  const static Taddress levelHeaderHackSlotChangeCopy1Length
    = levelHeaderHackSlotChangeCopy1EndAddress
        - levelHeaderHackSlotChangeCopy1Address;
        
  const static Taddress levelHeaderHackSlotChangeCopy1LevelHeaderOffset
      = 8;
  
  /**
   * Length of the level header address table location hack.
   */
  const static Taddress levelHeaderHackSlotChangeUnbankLength = 19;
  
  /**
   * Data for the level header address table location hack.
   */
  const static Tbyte levelHeaderHackSlotChangeUnbankData[
                                levelHeaderHackSlotChangeUnbankLength];
                                
  const static int levelHeaderHackSlotChangeUnbankBankOffset = 3;
                                
  const static int levelHeaderHackSlotChangeUnbankAddressOffset = 8;
                                
  const static int levelHeaderHackSlotChangeUnbankAddressOffsetJump
    = levelHeaderHackSlotChangeUnbankAddressOffset + 2;
  
  /**
   * Second copy address.
   */
  const static Taddress levelHeaderHackSlotChangeCopy2Address = 0x7481;
  
  const static Taddress levelHeaderHackSlotChangeCopy2AddressEnd = 0x74A3;
  
  /**
   * Second copy length.
   */
  const static Taddress levelHeaderHackSlotChangeCopy2Length
    = levelHeaderHackSlotChangeCopy2AddressEnd
        - levelHeaderHackSlotChangeCopy2Address;
  
  /**
   * Length of the level header address table location hack.
   */
  const static int levelHeaderHackSlotChangeLoopLength = 2;
  
  /**
   * Data for the level header address table location hack.
   */
  const static Tbyte levelHeaderHackSlotChangeLoopData[
                                levelHeaderHackSlotChangeLoopLength];
                                
  // Double jump fix
  
  const static Taddress doubleJumpFixHackAddress = 0x317DC;
  
  const static Taddress doubleJumpFixHackJumpHeightAddress = 0x317DF;
  
  const static int doubleJumpFixHackLength = 6;
  
  const static int doubleJumpFixHackJumpHeightOffset = 2;
  
  const static Tbyte doubleJumpFixHackData[
                           doubleJumpFixHackLength];
                                
  // Jump to max height when button 1 held fix
  
  const static Taddress button1MaxHeightFixHackAddress = 0x317D4;
  
  const static Taddress button1MaxHeightFixHackByteAddress = 0x317D5;
  
  const static int button1MaxHeightFixHackLength = 2;
  
  const static Tbyte button1MaxHeightFixHackData[
                           button1MaxHeightFixHackLength];
                           
  // Corrupted bomb-throwing while jumping frame fix
  
  const static Taddress bombWhileJumpingGraphicFixAddress = 0x38DEF;
  
  const static int bombWhileJumpingGraphicFixLength = 1;
  
  const static Tbyte bombWhileJumpingGraphicFixData
                            [bombWhileJumpingGraphicFixLength];
                           
  // Use all inventory items hack
  
//  const static int allInventoryHackMainLength = 214;

  const static int allInventoryHackMainLength = 217;
  
  const static Tbyte allInventoryHackMainData[
                        allInventoryHackMainLength];
  
  /**
   * Offset of the first table (inventory # to object ID) in the hack data.
   */
  const static int allInventoryHackMainTable1Offset = 0;
  
  /**
   * Offset of the first table reference in the hack data.
   */
  const static int allInventoryHackMainTable1ReferenceOffset = 129;
  
  /**
   * Offset of the second table (sea fox # to object ID) in the hack data.
   */
  const static int allInventoryHackMainTable2Offset = 24;
  
  /**
   * Offset of the first table reference in the hack data.
   */
  const static int allInventoryHackMainTable2ReferenceOffset = 203;
  
  /**
   * Offset of the code start in the hack data.
   */
  const static int allInventoryHackMainCodeStartOffset = 32;
  
  const static Taddress allInventoryHackTrigger1Address = 0x154A;
  
  const static int allInventoryHackTrigger1BankReferenceOffset = 7;
  
  const static int allInventoryHackTrigger1AddressReferenceOffset = 12;
  
  const static int allInventoryHackTrigger1Length = 14;
  
  const static Tbyte allInventoryHackTrigger1Data[
                        allInventoryHackTrigger1Length];
  
  const static Taddress allInventoryHackTrigger2Address = 0x15CB;
  
  const static int allInventoryHackTrigger2BankReferenceOffset = 1;
  
  const static int allInventoryHackTrigger2AddressReferenceOffset = 6;
  
  const static int allInventoryHackTrigger2Length = 10;
  
  const static Tbyte allInventoryHackTrigger2Data[
                        allInventoryHackTrigger2Length];
  
  const static Taddress allInventoryHackInitializer1Address = 0x26FE;
  
  const static int allInventoryHackInitializer1Length = 3;
  
  const static Tbyte allInventoryHackInitializer1Data[
                          allInventoryHackInitializer1Length];
  
  const static Taddress allInventoryHackInitializer2Address = 0x2705;
  
  const static int allInventoryHackInitializer2Length = 1;
  
  const static Tbyte allInventoryHackInitializer2Data[
                          allInventoryHackInitializer2Length];
  
  const static Taddress allInventoryHackInitializer3Address = 0x2715;
  
  const static int allInventoryHackInitializer3Length = 3;
  
  const static Tbyte allInventoryHackInitializer3Data[
                          allInventoryHackInitializer3Length];
  
  const static Taddress allInventoryHackInitializer4Address = 0x6C4;
  
  const static int allInventoryHackInitializer4Length = 17;
  
  const static Tbyte allInventoryHackInitializer4Data[
                          allInventoryHackInitializer4Length];
                          
  // Full inventory hotswap hack
  
  const static Taddress fullInventoryHotswapHackMainAddress = 0x7D0A;
  
  const static int fullInventoryHotswapHackMainLength = 739;
  
  const static Tbyte fullInventoryHotswapHackMainData[
                          fullInventoryHotswapHackMainLength];
  
  const static Taddress fullInventoryHotswapHackTriggerAddress = 0x12DB;
  
  const static int fullInventoryHotswapHackTriggerLength = 3;
  
  const static Tbyte fullInventoryHotswapHackTriggerData[
                          fullInventoryHotswapHackTriggerLength];
                          
  // Regular inventory hotswap hack
  
  const static Taddress regularInventoryHotswapHackMainAddress = 0x7D0A;
  
  const static int regularInventoryHotswapHackMainLength = 731;
  
  const static Tbyte regularInventoryHotswapHackMainData[
                          regularInventoryHotswapHackMainLength];
  
  const static Taddress regularInventoryHotswapHackTriggerAddress = 0x12DB;
  
  const static int regularInventoryHotswapHackTriggerLength = 3;
  
  const static Tbyte regularInventoryHotswapHackTriggerData[
                          regularInventoryHotswapHackTriggerLength];
                          
  // Flight limiter hack
  
  const static Taddress flightLimiterHackMain1Address = 0x6D5;
  
  const static int flightLimiterHackMain1Length = 20;
  
  const static Tbyte flightLimiterHackMain1Data
                          [flightLimiterHackMain1Length];
  
  const static Taddress flightLimiterHackMain2Address
    = flightLimiterHackMain1Address
        + flightLimiterHackMain1Length;
  
  const static int flightLimiterHackMain2Length = 9;
  
  const static Tbyte flightLimiterHackMain2Data
                          [flightLimiterHackMain2Length];
  
  const static Taddress flightLimiterHackTrigger1Address = 0x36B3;
  
  const static int flightLimiterHackTrigger1Length = 3;
  
  const static Tbyte flightLimiterHackTrigger1Data
                          [flightLimiterHackTrigger1Length];
  
  const static Taddress flightLimiterHackTrigger2Address = 0x35D8;
  
  const static int flightLimiterHackTrigger2Length = 3;
  
  const static Tbyte flightLimiterHackTrigger2Data
                          [flightLimiterHackTrigger2Length];
  
  const static Taddress flightLimiterHackTrigger3Address = 0x4496;
  
  const static int flightLimiterHackTrigger3Length = 9;
  
  const static Tbyte flightLimiterHackTrigger3Data
                          [flightLimiterHackTrigger3Length];
                          
  // Flight disable hack
  
  const static Taddress flightDisableHackMainAddress = 0x36B3;
  
  const static int flightDisableHackMainLength = 1;
  
  const static Tbyte flightDisableHackMainData
                          [flightDisableHackMainLength];
                                
public:

  /**
   * Number of bytes of space needed for the level header hack code.
   */
  const static int levelHeaderHackCodeDataSize
    = levelHeaderHackSlotChangeBank2Length
        + levelHeaderHackSlotChangeCopy1Length
        + levelHeaderHackSlotChangeUnbankLength
        + levelHeaderHackSlotChangeCopy2Length
        + levelHeaderHackSlotChangeLoopLength;

  /**
   * Number of bytes of space needed for the use all inventory items hack.
   */
  const static int allInventoryHackCodeDataSize
    = allInventoryHackMainLength;
  
};


};


#endif
