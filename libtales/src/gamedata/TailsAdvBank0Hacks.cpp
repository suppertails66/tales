#include "gamedata/TailsAdvBank0Hacks.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/NotEnoughSpaceException.h"
#include <cstring>
#include <iostream>

using namespace Luncheon;

namespace Tales {


void TailsAdvBank0Hacks::addLevelHeaderHack(
                   WritableROM& rom,
                   Taddress levelHeaderAddress,
                   Taddress codeCopyBase) {
  // Write hack
/*  rom.directWrite(levelHeaderHackAddress,
                  levelHeaderHackData,
                  levelHeaderHackLength);
  
  // Get banked address of level headers
  Taddress levelHeaderBankNum
    = LoadedROM::directToBankNum(levelHeaderAddress);
  Taddress levelHeaderBankedAddress
    = LoadedROM::directToBankedAddress(levelHeaderAddress);
  
  // We need a slot 1 address instead of slot 2
  levelHeaderBankedAddress -= LoadedROM::slot2StartAddress;
  levelHeaderBankedAddress += LoadedROM::slot1StartAddress;
    
  // Fill in address
  ByteConversion::toBytes(levelHeaderBankNum,
                          rom.directWrite(levelHeaderHackAddress
                                            + levelHeaderHackBankOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  ByteConversion::toBytes(levelHeaderBankedAddress,
                          rom.directWrite(levelHeaderHackAddress
                                            + levelHeaderHackAddressOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Add trigger
  rom.directWrite(levelHeaderHackTriggerAddress,
                  levelHeaderHackTriggerData,
                  levelHeaderHackTriggerLength); */
                  
//  std::cout << levelHeaderAddress << std::endl;
  
  // Get banked address of level headers
  Taddress levelHeaderBankNum
    = LoadedROM::directToBankNum(levelHeaderAddress);
  Taddress levelHeaderSlot2BankedAddress
    = LoadedROM::directToBankedAddress(levelHeaderAddress);
  
  Taddress codeCopyBaseBankedAddress
    = LoadedROM::directToBankedAddress(codeCopyBase);
  
  // We need a slot 1 address as well as slot 2
  Taddress levelHeaderSlot1BankedAddress
    = levelHeaderSlot2BankedAddress
        - LoadedROM::slot2StartAddress
        + LoadedROM::slot1StartAddress;
        
  // Make a copy of some code we'll be modifying, but will need unmodified
  // later on
  Tbyte codeCopy1Buffer[levelHeaderHackSlotChangeCopy1Length];
  std::memcpy(codeCopy1Buffer,
              rom.directRead(levelHeaderHackSlotChangeCopy1Address),
              levelHeaderHackSlotChangeCopy1Length);
              
  // 1. Modify the routine to load the bank containing our code into
  // slot 2
  
  rom.directWrite(levelHeaderHackSlotChangeBankAddress,
                  levelHeaderHackSlotChangeBankData,
                  levelHeaderHackSlotChangeBankLength);
  // Fill in bank change
  ByteConversion::toBytes(levelHeaderBankNum,
                          rom.directWrite(levelHeaderHackSlotChangeBankAddress
                            + levelHeaderHackSlotChangeBankBankOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  ByteConversion::toBytes(codeCopyBaseBankedAddress,
                          rom.directWrite(levelHeaderHackSlotChangeBankAddress
                            + levelHeaderHackSlotChangeBankAddressOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
                          
  // 2. At codeCopyBase, add instructions to change slot 1 to the same bank we
  // are executing from, then jump to our "next" instruction in slot 1
  
  Taddress writeAddress = codeCopyBase;
  
  Taddress slotChangeBank2Start = writeAddress;
  
  rom.directWrite(writeAddress,
                  levelHeaderHackSlotChangeBank2Data,
                  levelHeaderHackSlotChangeBank2Length);
  writeAddress += levelHeaderHackSlotChangeBank2Length;
  
  // Get address to jump to (must be slot 1, not slot 2)
  Taddress bankedWriteSlot2Address
    = LoadedROM::directToBankedAddress(writeAddress);
  
  // We need a slot 1 address instead of slot 2
  Taddress bankedWriteSlot1Address
    = bankedWriteSlot2Address
        - LoadedROM::slot2StartAddress
        + LoadedROM::slot1StartAddress;
  
  // Fill in address in instruction
  ByteConversion::toBytes(bankedWriteSlot1Address,
                          rom.directWrite(slotChangeBank2Start
                            + levelHeaderHackSlotChangeBank2AddressOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);

  // 3. Copy instructions we saved earlier into the new routine
  
  rom.directWrite(writeAddress,
                  codeCopy1Buffer,
                  levelHeaderHackSlotChangeCopy1Length);
  
  // Fill in new address of the level header table (slot 1)
  ByteConversion::toBytes(levelHeaderSlot1BankedAddress,
                          rom.directWrite(writeAddress
                            + levelHeaderHackSlotChangeCopy1LevelHeaderOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    
  writeAddress += levelHeaderHackSlotChangeCopy1Length;
  
  // 4. Add new instructions to change to old bank when exiting loop
  
  rom.directWrite(writeAddress,
                  levelHeaderHackSlotChangeUnbankData,
                  levelHeaderHackSlotChangeUnbankLength);
                  
  // Fill in bank to change to
  ByteConversion::toBytes(levelHeaderBankNum,
                          rom.directWrite(writeAddress
                            + levelHeaderHackSlotChangeUnbankBankOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Fill in jump address (to jump to the next instruction in slot 2
  // instead of slot 1, since we need to change slot 1 to bank 1)
  ByteConversion::toBytes(LoadedROM::directToBankedAddress(
                           writeAddress
                           + levelHeaderHackSlotChangeUnbankAddressOffsetJump),
                          rom.directWrite(writeAddress
                            + levelHeaderHackSlotChangeUnbankAddressOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  writeAddress += levelHeaderHackSlotChangeUnbankLength;
  
  // 5. Copy the second block of code
  
  rom.directWrite(writeAddress,
                  rom.directRead(levelHeaderHackSlotChangeCopy2Address),
                  levelHeaderHackSlotChangeCopy2Length);
  writeAddress += levelHeaderHackSlotChangeCopy2Length;
  
  // 6. Update relative jump at end of routine to go to correct location
  rom.directWrite(writeAddress,
                  levelHeaderHackSlotChangeLoopData,
                  levelHeaderHackSlotChangeLoopLength);
  writeAddress += levelHeaderHackSlotChangeLoopLength;
  
/*  // 1. Add JP instruction to new code location
  
  // Write raw instruction (JP 0000h)
  rom.directWrite(levelHeaderHackSlotChangeJumpAddress,
                  levelHeaderHackSlotChangeJumpData,
                  levelHeaderHackSlotChangeJumpLength);
  
  // Fill in our target address (JP XXXXh)
  Taddress codeCopyBaseBankedAddress
    = LoadedROM::directToBankedAddress(codeCopyBase);
  ByteConversion::toBytes(codeCopyBaseBankedAddress,
                          rom.directWrite(levelHeaderHackSlotChangeJumpAddress
                             + levelHeaderHackSlotChangeJumpAddressOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  
  // Our current write address
  Taddress codeWriteAddress = codeCopyBase;
  
  // 2. Add bank change and other new code at jump target
  
  rom.directWrite(codeWriteAddress,
                  levelHeaderHackSlotChangeBankData,
                  levelHeaderHackSlotChangeBankLength);
  // Fill in bank change
  ByteConversion::toBytes(levelHeaderBankNum,
                          rom.directWrite(codeWriteAddress
                            + levelHeaderHackSlotChangeBankBankOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  codeWriteAddress += levelHeaderHackSlotChangeBankLength;
                  
  // 3. Copy first block of code
  
  rom.directWrite(codeWriteAddress,
                  rom.directRead(levelHeaderHackSlotChangeCopy1Address),
                  levelHeaderHackSlotChangeCopy1Length);
  codeWriteAddress += levelHeaderHackSlotChangeCopy1Length;
  
  // 4. Add new instructions to change to old bank when exiting loop
  
  rom.directWrite(codeWriteAddress,
                  levelHeaderHackSlotChangeUnbankData,
                  levelHeaderHackSlotChangeUnbankLength);
  codeWriteAddress += levelHeaderHackSlotChangeUnbankLength;
                  
  // 5. Copy second block of code
  
  rom.directWrite(codeWriteAddress,
                  rom.directRead(levelHeaderHackSlotChangeCopy2Address),
                  levelHeaderHackSlotChangeCopy2Length);
  codeWriteAddress += levelHeaderHackSlotChangeCopy2Length;
  
  // 6. Update JR at end of code to go to correct location
  
  rom.directWrite(codeWriteAddress,
                  levelHeaderHackSlotChangeLoopData,
                  levelHeaderHackSlotChangeLoopLength);
  codeWriteAddress += levelHeaderHackSlotChangeLoopLength; */
}

void TailsAdvBank0Hacks::addDoubleJumpFixHack(
                   WritableROM& rom) {
  // Copy the original jump height
  Tbyte jHeight[1];
  std::memcpy(jHeight,
              rom.directRead(doubleJumpFixHackJumpHeightAddress),
              1);
  
  // Decrement jump height by 1 for hack
  jHeight[0] = (jHeight[0] - 1);
                   
  // Write fix to ROM
  rom.directWrite(doubleJumpFixHackAddress,
                  doubleJumpFixHackData,
                  doubleJumpFixHackLength);
                  
  // Copy jump height + 1
  rom.directWrite(doubleJumpFixHackAddress
                    + doubleJumpFixHackJumpHeightOffset,
                  jHeight,
                  1);
}

void TailsAdvBank0Hacks::addButton1MaxHeightFixHack(
                   WritableROM& rom) {
  rom.directWrite(button1MaxHeightFixHackAddress,
                  button1MaxHeightFixHackData,
                  button1MaxHeightFixHackLength);
}

void TailsAdvBank0Hacks::addBombWhileJumpingGraphicFixHack(
                   WritableROM& rom) {
  rom.directWrite(bombWhileJumpingGraphicFixAddress,
                  bombWhileJumpingGraphicFixData,
                  bombWhileJumpingGraphicFixLength);
}

void TailsAdvBank0Hacks::addUseAllInventoryHack(
                   WritableROM& rom) {
  // Find free space
  FreeSpaceList::iterator spaceIt
    = rom.freeSpace().getFreeSpace(allInventoryHackCodeDataSize);
  
  // Throw if not enough space
  if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
    throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                  "TailsAdvBank0Hacks::addUseAllInventoryHack("
                                  "WritableROM&)",
                                  allInventoryHackCodeDataSize);
  }
  
  Taddress writeAddress = spaceIt->address();
  
  rom.freeSpace().claimSpace(spaceIt,
                             allInventoryHackCodeDataSize);
                             
//  std::cout << writeAddress << std::endl;
  
  // Write main code and data
  rom.directWrite(writeAddress,
                  allInventoryHackMainData,
                  allInventoryHackMainLength);
  
  // Fill in addresses of data tables
  
  ByteConversion::toBytes(LoadedROM::directToBankedAddress(writeAddress
                            + allInventoryHackMainTable1Offset),
                          rom.directWrite(writeAddress
                            + allInventoryHackMainTable1ReferenceOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(LoadedROM::directToBankedAddress(writeAddress
                            + allInventoryHackMainTable2Offset),
                          rom.directWrite(writeAddress
                            + allInventoryHackMainTable2ReferenceOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Add trigger 1
  
  rom.directWrite(allInventoryHackTrigger1Address,
                  allInventoryHackTrigger1Data,
                  allInventoryHackTrigger1Length);
                  
  // Fill in bank
  ByteConversion::toBytes(LoadedROM::directToBankNum(writeAddress
                            + allInventoryHackMainCodeStartOffset),
                          rom.directWrite(
                            allInventoryHackTrigger1Address
                            + allInventoryHackTrigger1BankReferenceOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  
  // Fill in address
  ByteConversion::toBytes(LoadedROM::directToBankedAddress(writeAddress
                            + allInventoryHackMainCodeStartOffset),
                          rom.directWrite(
                            allInventoryHackTrigger1Address
                            + allInventoryHackTrigger1AddressReferenceOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Add trigger 2
  
  rom.directWrite(allInventoryHackTrigger2Address,
                  allInventoryHackTrigger2Data,
                  allInventoryHackTrigger2Length);
                  
  // Fill in bank
  ByteConversion::toBytes(LoadedROM::directToBankNum(writeAddress
                            + allInventoryHackMainCodeStartOffset),
                          rom.directWrite(
                            allInventoryHackTrigger2Address
                            + allInventoryHackTrigger2BankReferenceOffset),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Fill in address
  ByteConversion::toBytes(LoadedROM::directToBankedAddress(writeAddress
                            + allInventoryHackMainCodeStartOffset),
                          rom.directWrite(
                            allInventoryHackTrigger2Address
                            + allInventoryHackTrigger2AddressReferenceOffset),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Add initializer 1
  rom.directWrite(allInventoryHackInitializer1Address,
                  allInventoryHackInitializer1Data,
                  allInventoryHackInitializer1Length);
  
  // Add initializer 2
  rom.directWrite(allInventoryHackInitializer2Address,
                  allInventoryHackInitializer2Data,
                  allInventoryHackInitializer2Length);
  
  // Add initializer 3
  rom.directWrite(allInventoryHackInitializer3Address,
                  allInventoryHackInitializer3Data,
                  allInventoryHackInitializer3Length);
  
  // Add initializer 4
  rom.directWrite(allInventoryHackInitializer4Address,
                  allInventoryHackInitializer4Data,
                  allInventoryHackInitializer4Length);
  
}

void TailsAdvBank0Hacks::addFullInventoryHotswapHack(
                   WritableROM& rom) {
  // Use full inventory
  addUseAllInventoryHack(rom);
  
  // Write hotswap hack
  rom.directWrite(fullInventoryHotswapHackMainAddress,
                  fullInventoryHotswapHackMainData,
                  fullInventoryHotswapHackMainLength);
  
  // Write hotswap trigger
  rom.directWrite(fullInventoryHotswapHackTriggerAddress,
                  fullInventoryHotswapHackTriggerData,
                  fullInventoryHotswapHackTriggerLength);
}

void TailsAdvBank0Hacks::addRegularInventoryHotswapHack(
                   WritableROM& rom) {
  // Write hotswap hack
  rom.directWrite(regularInventoryHotswapHackMainAddress,
                  regularInventoryHotswapHackMainData,
                  regularInventoryHotswapHackMainLength);
  
  // Write hotswap trigger
  rom.directWrite(regularInventoryHotswapHackTriggerAddress,
                  regularInventoryHotswapHackTriggerData,
                  regularInventoryHotswapHackTriggerLength);
}

void TailsAdvBank0Hacks::addFlightLimiterHack(
                   WritableROM& rom) {
  
  rom.directWrite(flightLimiterHackMain1Address,
                  flightLimiterHackMain1Data,
                  flightLimiterHackMain1Length);
  
  rom.directWrite(flightLimiterHackMain2Address,
                  flightLimiterHackMain2Data,
                  flightLimiterHackMain2Length);
  
  rom.directWrite(flightLimiterHackTrigger1Address,
                  flightLimiterHackTrigger1Data,
                  flightLimiterHackTrigger1Length);
  
  rom.directWrite(flightLimiterHackTrigger2Address,
                  flightLimiterHackTrigger2Data,
                  flightLimiterHackTrigger2Length);
  
  rom.directWrite(flightLimiterHackTrigger3Address,
                  flightLimiterHackTrigger3Data,
                  flightLimiterHackTrigger3Length);
}

void TailsAdvBank0Hacks::addFlightDisableHack(
                   WritableROM& rom) {
  rom.directWrite(flightDisableHackMainAddress,
                  flightDisableHackMainData,
                  flightDisableHackMainLength);
}

void TailsAdvBank0Hacks::addNoGameOverHack(
                   WritableROM& rom) {
  rom.directWrite(noGameOverHackMainAddress,
                  noGameOverHackMainData,
                  noGameOverHackMainLength);
}

void TailsAdvBank0Hacks::addManualSaveHack(
                     WritableROM& rom) {
  addSaveHackBase(rom);
}

void TailsAdvBank0Hacks::addAutoSaveHack(
                   WritableROM& rom) {
  addSaveHackBase(rom);
  rom.directWrite(autoSaveHackAddress,
                  autoSaveHackData,
                  autoSaveHackLength);
}

void TailsAdvBank0Hacks::addSaveHackBase(
                   WritableROM& rom) {
  rom.directWrite(saveHackAddress1,
                  saveHackData1,
                  saveHackLength1);
                  
  rom.directWrite(saveHackAddress2,
                  saveHackData2,
                  saveHackLength2);
                  
  rom.directWrite(saveHackAddress3,
                  saveHackData3,
                  saveHackLength3);
                  
  rom.directWrite(saveHackAddress4,
                  saveHackData4,
                  saveHackLength4);
}
                     
const Tbyte TailsAdvBank0Hacks::levelHeaderHackData[levelHeaderHackLength] =
  { 0x3E, 0x00,           // ld A,0   ; zero will be replaced by bank number
    0xCD, 0x8E, 0x1B,     // call 1B8E  ; load new bank
    0x11, 0x00, 0x00,     // ld DE,0000h ; zero will be replaced by address
    // jp 742Fh ; jump back to regular routine
    0xC3,
      (Tbyte)(levelHeaderHackReturnAddress & 0x00FF),
      (Tbyte)((levelHeaderHackReturnAddress & 0xFF00) >> 8) };

const Tbyte TailsAdvBank0Hacks
    ::levelHeaderHackTriggerData[levelHeaderHackTriggerLength] =
  // jp levelHeaderHackAddress
  { 0xC3,
      (Tbyte)(levelHeaderHackAddress & 0x00FF),
      (Tbyte)((levelHeaderHackAddress & 0xFF00) >> 8) };
  
const Tbyte TailsAdvBank0Hacks::levelHeaderHackSlotChangeJumpData[
                              levelHeaderHackSlotChangeJumpLength] =
/*  { 0x3E, 0x00,           // ld A, 00h
    0x32, 0x2B, 0xD1,     // ld (D12Ah),A
    0x32, 0xFF, 0xFF,     // ld (FFFEh),A
    0x3A, 0xAA, 0xD2,     // ld A,(D2AAh) */
    { 0xC3, 0x00, 0x00 };   // jp 0000h   ; fill in with correct address
      
const Tbyte TailsAdvBank0Hacks::levelHeaderHackSlotChangeBankData[
                              levelHeaderHackSlotChangeBankLength] =
  { 0x3E, 0x00,           // ld A, 00h    ; fill in with correct bank number
    0xCD, 0x8E, 0x1B,     // call 1B8E    ; load new bank to slot 2
    0xC3, 0x00, 0x00 };   // jp 0000h     ; fill in with correct address
      
const Tbyte TailsAdvBank0Hacks::levelHeaderHackSlotChangeBank2Data[
                              levelHeaderHackSlotChangeBank2Length] =
  { 0x32, 0x2A, 0xD1,     // ld (D12A),A  ; load new bank to slot 1 soft mirror
    0x32, 0xFE, 0xFF,     // ld (FFFE),A  ; load new bank to slot 1
    0xC3, 0x00, 0x00 };   // jp (0000)    ; fill in with correct address
    
    
    
/*    0x32, 0x2A, 0xD1,     // ld (D12Ah),A
    0x32, 0xFE, 0xFF,     // ld (FFFEh),A
    0x3A, 0xAA, 0xD2 };   // ld A,(D2AAh) */
                              
const Tbyte TailsAdvBank0Hacks::levelHeaderHackSlotChangeUnbankData[
                              levelHeaderHackSlotChangeUnbankLength] =
  { 0x20, 17,             // jr nz,+17
    0x3E, 0x00,           // ld A,00      ; fill in with correct bank number
    0xCD, 0x8E, 0x1B,     // call 1B8E    ; load new bank to slot 2
    0xC3, 0x00, 0x00,     // jp (0000)    ; fill in with correct slot 2 address
    0x3E, 0x01,           // ld A,1
    0x32, 0x2A, 0xD1,     // ld (D12Ah),A
    0x32, 0xFE, 0xFF,     // ld (FFFEh),A ; load bank 1 to slot 1
    0xC9 };               // ret
                              
const Tbyte TailsAdvBank0Hacks::levelHeaderHackSlotChangeLoopData[
                              levelHeaderHackSlotChangeLoopLength] =
  { 0x18, 0xC4 };         // jr -60
  
// Conceptually, this changes the code from
// ++counter; if (counter < 0xE) doJump();
// to
// if (counter < 0xD) { doJump(); ++counter; }
// This prevents the counter from incrementing past its maximum value.
// We also have to decrease the counter check constant (0xE) by 1 since
// the counter will now be 0 instead of 1 on the first iteration (otherwise,
// Tails will jump too high).
const Tbyte TailsAdvBank0Hacks::doubleJumpFixHackData[
                         doubleJumpFixHackLength] =
  { 0x7E,                 // ld A,(HL)
    0xFE, 0x0D,           // cp 0Dh
    0x30, 0x10,           // jr nc,+10h
    0x34 };               // inc (HL)   ; increment after check, not before
  
const Tbyte TailsAdvBank0Hacks::button1MaxHeightFixHackData[
                         button1MaxHeightFixHackLength] =
  { 0xE6, 0x20 };         // and 20h    ; AND to button 2, not 1 and 2
  
const Tbyte TailsAdvBank0Hacks::bombWhileJumpingGraphicFixData
                          [bombWhileJumpingGraphicFixLength] =
  { 0x08 };     // load all 16 tiles instead of only the first 12
    
/*const Tbyte TailsAdvBank0Hacks::allInventoryHackMainData[
                      allInventoryHackMainLength] =
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x8, 0x11, 0x10, 
  0xf, 0xe, 0xd, 0xc, 0xb, 0xa, 0x1a, 0x7, 0x6, 0x5, 
  0x4, 0x3, 0x2, 0x1, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 
            // v-- code start
  0x13, 0x12, 0x3a, 0xaa, 0xd2, 0xfe, 0x6, 0x28, 0x68, 0xfe, 
  0x7, 0x28, 0x64, 0xfe, 0xb, 0x28, 0x60, 0x18, 0x0, 0x3a, 
  0x4a, 0xd1, 0xe6, 0xc, 0x28, 0x24, 0x3a, 0x4a, 0xd1, 0xcb, 
  0x57, 0x20, 0x10, 0x3a, 0x35, 0xd0, 0x3d, 0xfe, 0x6, 0x30, 
  0x3, 0x3e, 0x18, 0x3d, 0x32, 0x35, 0xd0, 0x18, 0xd, 0x3a, 
  0x35, 0xd0, 0x3c, 0xfe, 0x18, 0x38, 0x2, 0x3e, 0x6, 0x32, 
  0x35, 0xd0, 0x3a, 0x35, 0xd0, 0x21, 0x32, 0xd0, 0xfe, 0x10, 
  0x38, 0x7, 0x21, 0x30, 0xd0, 0xd6, 0x10, 0x18, 0x9, 0xfe, 
  0x8, 0x38, 0x5, 0x21, 0x31, 0xd0, 0xd6, 0x8, 0x3c, 0x47, 
  0x7e, 0xf, 0x10, 0xfd, 0x38, 0x2, 0x18, 0xb1, 0x21, 0x00,  // <-- addr 1
  0x00, 0x3a, 0x35, 0xd0, 0x5f, 0x16, 0x0, 0x19, 0x7e, 0x32, 
  0x36, 0xd0, 0xc9, 0x3a, 0x4a, 0xd1, 0xe6, 0xc, 0x28, 0x24, 
  0x3a, 0x4a, 0xd1, 0xcb, 0x57, 0x20, 0x10, 0x3a, 0x34, 0xd0, 
  0x3d, 0xfe, 0xff, 0x38, 0x3, 0x3e, 0x8, 0x3d, 0x32, 0x34, 
  0xd0, 0x18, 0xd, 0x3a, 0x34, 0xd0, 0x3c, 0xfe, 0x8, 0x38, 
  0x2, 0x3e, 0x0, 0x32, 0x34, 0xd0, 0x21, 0x33, 0xd0, 0x3c, 
  0x47, 0x7e, 0xf, 0x10, 0xfd, 0x38, 0x2, 0x18, 0xc8, 0x21,
  // v--: addr 2
  0x00, 0x00, 0x3a, 0x34, 0xd0, 0x5f, 0x16, 0x0, 0x19, 0x7e, 
  0x32, 0x36, 0xd0, 0xc9
  }; */
  
// Main patch data to be added in spare ROM area.
// Basically, this eliminates the slot-based inventory system, instead
// searching directly through the bitfield of unlocked items in order
// to figure out which items to equip when pressing left or right on the
// pause screen.
const Tbyte TailsAdvBank0Hacks::allInventoryHackMainData[
                      allInventoryHackMainLength] =
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x8, 0x11, 0x10, 
  0xf, 0xe, 0xd, 0xc, 0xb, 0xa, 0x1a, 0x7, 0x6, 0x5, 
  0x4, 0x3, 0x2, 0x1, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 
            // v-- code start: 32 (dec)
  0x13, 0x12, 0x3a, 0xaa, 0xd2, 0xfe, 0x6, 0x28, 0x68, 0xfe, 
  0x7, 0x28, 0x64, 0xfe, 0xb, 0x28, 0x60, 0x18, 0x0, 0x3a, 
  0x4a, 0xd1, 0xe6, 0xc, 0x28, 0x24, 0x3a, 0x4a, 0xd1, 0xcb, 
  0x57, 0x20, 0x10, 0x3a, 0x35, 0xd0, 0x3d, 0xfe, 0x6, 0x30, 
  0x3, 0x3e, 0x18, 0x3d, 0x32, 0x35, 0xd0, 0x18, 0xd, 0x3a, 
  0x35, 0xd0, 0x3c, 0xfe, 0x18, 0x38, 0x2, 0x3e, 0x6, 0x32, 
  0x35, 0xd0, 0x3a, 0x35, 0xd0, 0x21, 0x32, 0xd0, 0xfe, 0x10, 
  0x38, 0x7, 0x21, 0x30, 0xd0, 0xd6, 0x10, 0x18, 0x9, 0xfe, 
  0x8, 0x38, 0x5, 0x21, 0x31, 0xd0, 0xd6, 0x8, 0x3c, 0x47, 
  0x7e, 0xf, 0x10, 0xfd, 0x38, 0x2, 0x18, 0xb1, 0x21, 0x00,  // <-- addr 1: 129
  0x00, 0x3a, 0x35, 0xd0, 0x5f, 0x16, 0x0, 0x19, 0x7e, 0x32, 
  0x36, 0xd0, 0xc9, 0x3a, 0x4a, 0xd1, 0xe6, 0xc, 0x28, 0x24, 
  0x3a, 0x4a, 0xd1, 0xcb, 0x57, 0x20, 0x10, 0x3a, 0x34, 0xd0, 
  0x3d, 0xfe, 0xff, 0x38, 0x3, 0x3e, 0x8, 0x3d, 0x32, 0x34, 
  0xd0, 0x18, 0xd, 0x3a, 0x34, 0xd0, 0x3c, 0xfe, 0x8, 0x38, 
  0x2, 0x3e, 0x0, 0x32, 0x34, 0xd0, 0x3a, 0x34, 0xd0, 0x21, 
  0x33, 0xd0, 0x3c, 0x47, 0x7e, 0xf, 0x10, 0xfd, 0x38, 0x2,
                   // v-- addr 2: 203
  0x18, 0xc5, 0x21, 0x00, 0x00, 0x3a, 0x34, 0xd0, 0x5f, 0x16, 
  0x0, 0x19, 0x7e, 0x32, 0x36, 0xd0, 0xc9
   };
  
const Tbyte TailsAdvBank0Hacks::allInventoryHackTrigger1Data[
                      allInventoryHackTrigger1Length] =
  { 0x3A, 0x4A, 0xD1,   // ld A,(D14A)
    0xE6, 0x0C,         // and 0C
    0xC8,               // ret z      ; return if left/right not pressed
    0x3E, 0x00,         // ld a,00h
    0xCD, 0x8E, 0x1B,   // call 1B8E  ; change banks
    0xC3, 0x00, 0x00 }; // jp 0000    ; jump to hack code
  
const Tbyte TailsAdvBank0Hacks::allInventoryHackTrigger2Data[
                      allInventoryHackTrigger2Length] =
  { 0x3E, 0x00,         // ld a,00h
    0xCD, 0x8E, 0x1B,   // call 1B8E  ; change banks
    0xCD, 0x00, 0x00,   // call 0000  ; run hack code
    0x18, 0x16 };       // jr +16     ; skip leftover code
  
const Tbyte TailsAdvBank0Hacks::allInventoryHackInitializer1Data[
                        allInventoryHackInitializer1Length] =
  { 0x3E, 0x17, 0x00 }; // initialize selected item to 0x17 instead of 0x1

const Tbyte TailsAdvBank0Hacks::allInventoryHackInitializer2Data[
                          allInventoryHackInitializer2Length] =
  { 0x06 }; // initialize selected sea fox item to 0x6

const Tbyte TailsAdvBank0Hacks::allInventoryHackInitializer3Data[
                          allInventoryHackInitializer3Length] =
  { 0xC3, 0xC4, 0x06 }; // jp 06C4h       ; branch to new init code

const Tbyte TailsAdvBank0Hacks::allInventoryHackInitializer4Data[
                          allInventoryHackInitializer4Length] =
  { 0x32, 0x24, 0xD0,   // ld (D024h),a   ; initialize equipped item 1
    0x32, 0x20, 0xD0,   // ld (D020h),a   ; initialize ?
    0x32, 0x36, 0xD0,   // ld (D036h),a   ; initialize ID # of equipped item
    0x3E, 0x13,         // ld a,0x13
    0x32, 0x28, 0xD0,
    0xC3, 0x1E, 0x27 }; // jp 271Eh       ; branch to regular init code
  
// Inventory hotswap hack main data.
// This code supplants the pause loop and adds in a "hotswap" item
// selection method.
const Tbyte TailsAdvBank0Hacks::fullInventoryHotswapHackMainData[
                        fullInventoryHotswapHackMainLength] =
  { 0x21, 0x0, 0xdb, 0x6, 0x37, 0x3e, 0xe0, 0x77, 0x23, 0x10, 
  0xfa, 0x3e, 0xff, 0x32, 0x36, 0xd1, 0xcd, 0x5b, 0x6, 0xcd, 
  0xbd, 0x7f, 0xb7, 0x20, 0x5, 0x11, 0x24, 0xd0, 0x18, 0x3, 
  0x11, 0x28, 0xd0, 0x21, 0x0, 0x0, 0x6, 0x4, 0x1a, 0x13, 
  0xc6, 0x10, 0x32, 0xa4, 0xd3, 0xd5, 0xe5, 0xcd, 0x78, 0x77, 
  0xe1, 0x22, 0xa9, 0xd3, 0xe5, 0xc5, 0xcd, 0xf8, 0x76, 0xc1, 
  0xe1, 0xd1, 0xd5, 0x11, 0x80, 0x0, 0x19, 0xd1, 0x10, 0xe0, 
  0x3e, 0xe, 0xcd, 0x8e, 0x1b, 0x21, 0x9e, 0x39, 0x1, 0x3, 
  0x4, 0xfd, 0x21, 0x84, 0xd0, 0xcd, 0xb8, 0x9f, 0x21, 0xa8, 
  0x3a, 0x1, 0x3, 0x4, 0xfd, 0x21, 0xa8, 0xd0, 0xcd, 0xb8, 
  0x9f, 0x21, 0xde, 0x3b, 0x1, 0x3, 0x4, 0xfd, 0x21, 0x90, 
  0xd0, 0xcd, 0xb8, 0x9f, 0x21, 0x94, 0x3a, 0x1, 0x3, 0x4, 
  0xfd, 0x21, 0x9c, 0xd0, 0xcd, 0xb8, 0x9f, 0x3e, 0x2f, 0x21, 
  0x0, 0xdb, 0x77, 0x23, 0x77, 0x3e, 0x7f, 0x21, 0x2, 0xdb, 
  0x77, 0x23, 0x77, 0x3e, 0x57, 0x21, 0x4, 0xdb, 0x77, 0x23, 
  0x77, 0x3e, 0x57, 0x21, 0x6, 0xdb, 0x77, 0x23, 0x77, 0x3e, 
  0x78, 0x21, 0x40, 0xdb, 0x77, 0x3e, 0x80, 0x21, 0x42, 0xdb, 
  0x77, 0x3e, 0x78, 0x21, 0x44, 0xdb, 0x77, 0x3e, 0x80, 0x21, 
  0x46, 0xdb, 0x77, 0x3e, 0x50, 0x21, 0x48, 0xdb, 0x77, 0x3e, 
  0x58, 0x21, 0x4a, 0xdb, 0x77, 0x3e, 0xa0, 0x21, 0x4c, 0xdb, 
  0x77, 0x3e, 0xa8, 0x21, 0x4e, 0xdb, 0x77, 0x3e, 0x0, 0x21, 
  0x41, 0xdb, 0x77, 0x3e, 0x2, 0x21, 0x43, 0xdb, 0x77, 0x3e, 
  0x4, 0x21, 0x45, 0xdb, 0x77, 0x3e, 0x6, 0x21, 0x47, 0xdb, 
  0x77, 0x3e, 0x8, 0x21, 0x49, 0xdb, 0x77, 0x3e, 0xa, 0x21, 
  0x4b, 0xdb, 0x77, 0x3e, 0xc, 0x21, 0x4d, 0xdb, 0x77, 0x3e, 
  0xe, 0x21, 0x4f, 0xdb, 0x77, 0x3e, 0xff, 0x32, 0x36, 0xd1, 
  0xcd, 0x5b, 0x6, 0xcd, 0xec, 0x76, 0x3a, 0x4a, 0xd1, 0xe6, 
  0x80, 0x20, 0x3f, 0x3a, 0x3a, 0xd1, 0xe6, 0x80, 0x28, 0x12, 
  0x3a, 0x4a, 0xd1, 0xe6, 0xf, 0x28, 0xb, 0xcd, 0xaf, 0x7e, 
  0xcd, 0x5b, 0x6, 0xcd, 0xec, 0x76, 0x18, 0x26, 0x3a, 0x3a, 
  0xd1, 0xe6, 0x30, 0x28, 0x12, 0xcb, 0x67, 0x28, 0x5, 0xcd, 
  0xaf, 0x7e, 0x18, 0xca, 0xcb, 0x6f, 0x28, 0xc6, 0xcd, 0x19, 
  0x7f, 0x18, 0xc1, 0xcd, 0x4a, 0x15, 0x3a, 0x4a, 0xd1, 0xe6, 
  0xc, 0xc4, 0x79, 0x15, 0x18, 0xb4, 0xcd, 0xb2, 0x7f, 0x3e, 
  0xff, 0x32, 0x36, 0xd1, 0x3e, 0xe, 0xcd, 0x8e, 0x1b, 0x21, 
  0x9e, 0x39, 0x1, 0x3, 0x4, 0xfd, 0x21, 0x84, 0xd0, 0xcd, 
  0xe5, 0x9f, 0x21, 0xa8, 0x3a, 0x1, 0x3, 0x4, 0xfd, 0x21, 
  0xa8, 0xd0, 0xcd, 0xe5, 0x9f, 0x21, 0xde, 0x3b, 0x1, 0x3, 
  0x4, 0xfd, 0x21, 0x90, 0xd0, 0xcd, 0xe5, 0x9f, 0x21, 0x94, 
  0x3a, 0x1, 0x3, 0x4, 0xfd, 0x21, 0x9c, 0xd0, 0xcd, 0xe5, 
  0x9f, 0x21, 0x4e, 0xd3, 0xcb, 0xfe, 0x3a, 0x40, 0xd5, 0xb7, 
  0x28, 0x5, 0x21, 0x51, 0xd3, 0xcb, 0xfe, 0xcd, 0x5b, 0x6, 
  0xc9, 0xcd, 0xbd, 0x7f, 0x4f, 0xb7, 0x20, 0x5, 0x21, 0x24, 
  0xd0, 0x18, 0x3, 0x21, 0x28, 0xd0, 0x3a, 0x4a, 0xd1, 0xcb, 
  0x47, 0x28, 0x4, 0x3e, 0x0, 0x18, 0x19, 0xcb, 0x5f, 0x28, 
  0x4, 0x3e, 0x3, 0x18, 0x11, 0xcb, 0x4f, 0x28, 0x4, 0x3e, 
  0x1, 0x18, 0x9, 0xcb, 0x57, 0x28, 0x4, 0x3e, 0x2, 0x18, 
  0x1, 0xc9, 0x5f, 0x16, 0x0, 0x19, 0x7e, 0xb7, 0x20, 0x6, 
  0x3e, 0xb0, 0x32, 0x4, 0xde, 0xc9, 0x32, 0x36, 0xd0, 0x21, 
  0xd2, 0x7f, 0x5f, 0x16, 0x0, 0x19, 0x79, 0xb7, 0x20, 0x6, 
  0x7e, 0x32, 0x35, 0xd0, 0x18, 0x4, 0x7e, 0x32, 0x34, 0xd0, 
  0x3a, 0x36, 0xd0, 0xc6, 0x10, 0x32, 0xa4, 0xd3, 0xcd, 0xec, 
  0x76, 0x3e, 0xa9, 0x32, 0x4, 0xde, 0xc9, 0xcd, 0xbd, 0x7f, 
  0xb7, 0x20, 0x5, 0x21, 0x24, 0xd0, 0x18, 0x3, 0x21, 0x28, 
  0xd0, 0x3a, 0x4a, 0xd1, 0xcb, 0x47, 0x28, 0x7, 0x3e, 0x0, 
  0x11, 0x0, 0x0, 0x18, 0x22, 0xcb, 0x5f, 0x28, 0x7, 0x3e, 
  0x3, 0x11, 0x80, 0x1, 0x18, 0x17, 0xcb, 0x4f, 0x28, 0x7, 
  0x3e, 0x1, 0x11, 0x80, 0x0, 0x18, 0xc, 0xcb, 0x57, 0x28, 
  0x7, 0x3e, 0x2, 0x11, 0x0, 0x1, 0x18, 0x1, 0xc9, 0xd5, 
  0xe5, 0xd1, 0x4f, 0x6, 0x0, 0x9, 0x3a, 0x36, 0xd0, 0x4f, 
  0x6, 0x4, 0x1a, 0xb9, 0x20, 0x26, 0x7e, 0x12, 0xc6, 0x10, 
  0x32, 0xa4, 0xd3, 0x78, 0x3d, 0x87, 0x5f, 0x16, 0x0, 0xe5, 
  0x21, 0xaa, 0x7f, 0x19, 0x7e, 0x5f, 0x23, 0x7e, 0x57, 0xd5, 
  0xcd, 0x78, 0x77, 0xd1, 0xed, 0x53, 0xa9, 0xd3, 0xcd, 0xf8, 
  0x76, 0xe1, 0x18, 0x3, 0x13, 0x10, 0xd3, 0x3a, 0x36, 0xd0, 
  0x77, 0xc6, 0x10, 0x32, 0xa4, 0xd3, 0xcd, 0x78, 0x77, 0xe1, 
  0x22, 0xa9, 0xd3, 0xcd, 0xf8, 0x76, 0x3e, 0xc7, 0x32, 0x4, 
  0xde, 0xc9, 0x80, 0x1, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0, 
  0x21, 0x0, 0xdb, 0x6, 0x37, 0x3e, 0xe0, 0x77, 0x23, 0x10, 
  0xfa, 0x3a, 0xaa, 0xd2, 0xfe, 0x6, 0x28, 0xb, 0xfe, 0x7, 
  0x28, 0x7, 0xfe, 0xb, 0x28, 0x3, 0x3e, 0x0, 0xc9, 0x3e, 
  0xff, 0xc9, 0x0, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 
  0x7, 0x6, 0xf, 0xe, 0xd, 0xc, 0xb, 0xa, 0x9, 0x8, 
  0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0, 0x10
   };
  
const Tbyte TailsAdvBank0Hacks::fullInventoryHotswapHackTriggerData[
                        fullInventoryHotswapHackTriggerLength] =
  // call $7D0A   ; jump to new pause loop instead of old
  { 0xCD,
    (fullInventoryHotswapHackMainAddress & 0x00FF),
    (fullInventoryHotswapHackMainAddress & 0xFF00) >> 8 };


   
  
const Tbyte TailsAdvBank0Hacks::regularInventoryHotswapHackMainData[
                        regularInventoryHotswapHackMainLength] =
  { 0x21, 0x0, 0xdb, 0x6, 0x37, 0x3e, 0xe0, 0x77, 0x23, 0x10, 
  0xfa, 0x3e, 0xff, 0x32, 0x36, 0xd1, 0xcd, 0x5b, 0x6, 0xcd, 
  0xb5, 0x7f, 0xb7, 0x20, 0x5, 0x11, 0x24, 0xd0, 0x18, 0x3, 
  0x11, 0x28, 0xd0, 0x21, 0x0, 0x0, 0x6, 0x4, 0x1a, 0x13, 
  0xc6, 0x10, 0x32, 0xa4, 0xd3, 0xd5, 0xe5, 0xcd, 0x78, 0x77, 
  0xe1, 0x22, 0xa9, 0xd3, 0xe5, 0xc5, 0xcd, 0xf8, 0x76, 0xc1, 
  0xe1, 0xd1, 0xd5, 0x11, 0x80, 0x0, 0x19, 0xd1, 0x10, 0xe0, 
  0x3e, 0xe, 0xcd, 0x8e, 0x1b, 0x21, 0x9e, 0x39, 0x1, 0x3, 
  0x4, 0xfd, 0x21, 0x84, 0xd0, 0xcd, 0xb8, 0x9f, 0x21, 0xa8, 
  0x3a, 0x1, 0x3, 0x4, 0xfd, 0x21, 0xa8, 0xd0, 0xcd, 0xb8, 
  0x9f, 0x21, 0xde, 0x3b, 0x1, 0x3, 0x4, 0xfd, 0x21, 0x90, 
  0xd0, 0xcd, 0xb8, 0x9f, 0x21, 0x94, 0x3a, 0x1, 0x3, 0x4, 
  0xfd, 0x21, 0x9c, 0xd0, 0xcd, 0xb8, 0x9f, 0x3e, 0x2f, 0x21, 
  0x0, 0xdb, 0x77, 0x21, 0x1, 0xdb, 0x77, 0x3e, 0x7f, 0x21, 
  0x2, 0xdb, 0x77, 0x21, 0x3, 0xdb, 0x77, 0x3e, 0x57, 0x21, 
  0x4, 0xdb, 0x77, 0x21, 0x5, 0xdb, 0x77, 0x3e, 0x57, 0x21, 
  0x6, 0xdb, 0x77, 0x21, 0x7, 0xdb, 0x77, 0x3e, 0x78, 0x21, 
  0x40, 0xdb, 0x77, 0x3e, 0x80, 0x21, 0x42, 0xdb, 0x77, 0x3e, 
  0x78, 0x21, 0x44, 0xdb, 0x77, 0x3e, 0x80, 0x21, 0x46, 0xdb, 
  0x77, 0x3e, 0x50, 0x21, 0x48, 0xdb, 0x77, 0x3e, 0x58, 0x21, 
  0x4a, 0xdb, 0x77, 0x3e, 0xa0, 0x21, 0x4c, 0xdb, 0x77, 0x3e, 
  0xa8, 0x21, 0x4e, 0xdb, 0x77, 0x3e, 0x0, 0x21, 0x41, 0xdb, 
  0x77, 0x3e, 0x2, 0x21, 0x43, 0xdb, 0x77, 0x3e, 0x4, 0x21, 
  0x45, 0xdb, 0x77, 0x3e, 0x6, 0x21, 0x47, 0xdb, 0x77, 0x3e, 
  0x8, 0x21, 0x49, 0xdb, 0x77, 0x3e, 0xa, 0x21, 0x4b, 0xdb, 
  0x77, 0x3e, 0xc, 0x21, 0x4d, 0xdb, 0x77, 0x3e, 0xe, 0x21, 
  0x4f, 0xdb, 0x77, 0x3e, 0xff, 0x32, 0x36, 0xd1, 0xcd, 0x5b, 
  0x6, 0xcd, 0xec, 0x76, 0x3a, 0x4a, 0xd1, 0xe6, 0x80, 0x20, 
  0x3f, 0x3a, 0x3a, 0xd1, 0xe6, 0x80, 0x28, 0x12, 0x3a, 0x4a, 
  0xd1, 0xe6, 0xf, 0x28, 0xb, 0xcd, 0xb7, 0x7e, 0xcd, 0x5b, 
  0x6, 0xcd, 0xec, 0x76, 0x18, 0x26, 0x3a, 0x3a, 0xd1, 0xe6, 
  0x30, 0x28, 0x12, 0xcb, 0x67, 0x28, 0x5, 0xcd, 0xb7, 0x7e, 
  0x18, 0xca, 0xcb, 0x6f, 0x28, 0xc6, 0xcd, 0x11, 0x7f, 0x18, 
  0xc1, 0xcd, 0x4a, 0x15, 0x3a, 0x4a, 0xd1, 0xe6, 0xc, 0xc4, 
  0x79, 0x15, 0x18, 0xb4, 0xcd, 0xaa, 0x7f, 0x3e, 0xff, 0x32, 
  0x36, 0xd1, 0x3e, 0xe, 0xcd, 0x8e, 0x1b, 0x21, 0x9e, 0x39, 
  0x1, 0x3, 0x4, 0xfd, 0x21, 0x84, 0xd0, 0xcd, 0xe5, 0x9f, 
  0x21, 0xa8, 0x3a, 0x1, 0x3, 0x4, 0xfd, 0x21, 0xa8, 0xd0, 
  0xcd, 0xe5, 0x9f, 0x21, 0xde, 0x3b, 0x1, 0x3, 0x4, 0xfd, 
  0x21, 0x90, 0xd0, 0xcd, 0xe5, 0x9f, 0x21, 0x94, 0x3a, 0x1, 
  0x3, 0x4, 0xfd, 0x21, 0x9c, 0xd0, 0xcd, 0xe5, 0x9f, 0x21, 
  0x4e, 0xd3, 0xcb, 0xfe, 0x3a, 0x40, 0xd5, 0xb7, 0x28, 0x5, 
  0x21, 0x51, 0xd3, 0xcb, 0xfe, 0xcd, 0x5b, 0x6, 0xc9, 0xcd, 
  0xb5, 0x7f, 0x4f, 0xb7, 0x20, 0x5, 0x21, 0x24, 0xd0, 0x18, 
  0x3, 0x21, 0x28, 0xd0, 0x3a, 0x4a, 0xd1, 0xcb, 0x47, 0x28, 
  0x4, 0x3e, 0x0, 0x18, 0x19, 0xcb, 0x5f, 0x28, 0x4, 0x3e, 
  0x3, 0x18, 0x11, 0xcb, 0x4f, 0x28, 0x4, 0x3e, 0x1, 0x18, 
  0x9, 0xcb, 0x57, 0x28, 0x4, 0x3e, 0x2, 0x18, 0x1, 0xc9, 
  0x4f, 0x5f, 0x16, 0x0, 0x19, 0x7e, 0xb7, 0x20, 0x6, 0x3e, 
  0xb0, 0x32, 0x4, 0xde, 0xc9, 0x32, 0x36, 0xd0, 0x79, 0x32, 
  0x35, 0xd0, 0x3a, 0x36, 0xd0, 0xc6, 0x10, 0x32, 0xa4, 0xd3, 
  0xcd, 0xec, 0x76, 0x3e, 0xa9, 0x32, 0x4, 0xde, 0xc9, 0xcd, 
  0xb5, 0x7f, 0xb7, 0x20, 0x5, 0x21, 0x24, 0xd0, 0x18, 0x3, 
  0x21, 0x28, 0xd0, 0x3a, 0x4a, 0xd1, 0xcb, 0x47, 0x28, 0x7, 
  0x3e, 0x0, 0x11, 0x0, 0x0, 0x18, 0x22, 0xcb, 0x5f, 0x28, 
  0x7, 0x3e, 0x3, 0x11, 0x80, 0x1, 0x18, 0x17, 0xcb, 0x4f, 
  0x28, 0x7, 0x3e, 0x1, 0x11, 0x80, 0x0, 0x18, 0xc, 0xcb, 
  0x57, 0x28, 0x7, 0x3e, 0x2, 0x11, 0x0, 0x1, 0x18, 0x1, 
  0xc9, 0xd5, 0xe5, 0xd1, 0x4f, 0x6, 0x0, 0x9, 0x3a, 0x36, 
  0xd0, 0x4f, 0x6, 0x4, 0x1a, 0xb9, 0x20, 0x26, 0x7e, 0x12, 
  0xc6, 0x10, 0x32, 0xa4, 0xd3, 0x78, 0x3d, 0x87, 0x5f, 0x16, 
  0x0, 0xe5, 0x21, 0xa2, 0x7f, 0x19, 0x7e, 0x5f, 0x23, 0x7e, 
  0x57, 0xd5, 0xcd, 0x78, 0x77, 0xd1, 0xed, 0x53, 0xa9, 0xd3, 
  0xcd, 0xf8, 0x76, 0xe1, 0x18, 0x3, 0x13, 0x10, 0xd3, 0x3a, 
  0x36, 0xd0, 0x77, 0xc6, 0x10, 0x32, 0xa4, 0xd3, 0xcd, 0x78, 
  0x77, 0xe1, 0x22, 0xa9, 0xd3, 0xcd, 0xf8, 0x76, 0x3e, 0xc7, 
  0x32, 0x4, 0xde, 0xc9, 0x80, 0x1, 0x0, 0x1, 0x80, 0x0, 
  0x0, 0x0, 0x21, 0x0, 0xdb, 0x6, 0x37, 0x3e, 0xe0, 0x77, 
  0x23, 0x10, 0xfa, 0x3a, 0xaa, 0xd2, 0xfe, 0x6, 0x28, 0xb, 
  0xfe, 0x7, 0x28, 0x7, 0xfe, 0xb, 0x28, 0x3, 0x3e, 0x0, 
  0xc9, 0x3e, 0xff, 0xc9, 0x0, 0x17, 0x16, 0x15, 0x14, 0x13, 
  0x12, 0x11, 0x7, 0x6, 0xf, 0xe, 0xd, 0xc, 0xb, 0xa, 
  0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0, 
  0x10
   };
  
const Tbyte TailsAdvBank0Hacks::regularInventoryHotswapHackTriggerData[
                        regularInventoryHotswapHackTriggerLength] =
  // call $7D0A   ; jump to new pause loop instead of old
  { 0xCD,
    (fullInventoryHotswapHackMainAddress & 0x00FF),
    (fullInventoryHotswapHackMainAddress & 0xFF00) >> 8 };
  
const Tbyte TailsAdvBank0Hacks::flightLimiterHackMain1Data
                        [flightLimiterHackMain1Length] =
  // Runs when flight mode triggered
  { 0x3A, 0x60, 0xD1,         // ld a,(D160h)
    0xB7,                     // or a
    0xC0,                     // ret nz       ; ret if flight var nonzero
    0x3E, 0xFF,               // ld a,FF
    0x32, 0x60, 0xD1,         // ld (D160),a  ; set flight var to 0xFF
    0xDD, 0xCB, 0x03, 0x56,   // bit 2,(ix+3) ; run hijacked part of routine
    0xC2, 0x85, 0x36,         // jp nz,3685
    0xC3, 0xBA, 0x36 };       // jp 36BA      ; jump to regular routine
  
const Tbyte TailsAdvBank0Hacks::flightLimiterHackMain2Data
                        [flightLimiterHackMain2Length] =
  // Runs when landing/walking on ground
  { 0x32, 0x60, 0xD1,         // ld (D160),a  ; clear flight var
    0xCD, 0xE4, 0x3A,         // call 3AE4    ; run hijacked part of routine
    0xC3, 0xDB, 0x35 };       // jp 35DB      ; jump to regular routine
  
const Tbyte TailsAdvBank0Hacks::flightLimiterHackTrigger1Data
                        [flightLimiterHackTrigger1Length] =
  { 0xC3, 0xD5, 0x06 };       // jp 6D5
  
const Tbyte TailsAdvBank0Hacks::flightLimiterHackTrigger2Data
                        [flightLimiterHackTrigger2Length] =
  { 0xC3, 0xE9, 0x06 };       // jp 6E9
  
const Tbyte TailsAdvBank0Hacks::flightLimiterHackTrigger3Data
                        [flightLimiterHackTrigger3Length] =
  { 0x21, 0x60, 0xD1,         // ld hl,D160
    0x11, 0x61, 0xD1,         // ld de,D161
    0x01, 0x42, 0x01 };       // ld bc,0142   ; clear flight var

const Tbyte TailsAdvBank0Hacks::flightDisableHackMainData
                        [flightDisableHackMainLength] =
  { 0xC9 };                   // ret          ; don't enter flight mode

const Tbyte TailsAdvBank0Hacks::noGameOverHackMainData
                        [noGameOverHackMainLength] =
  { 0x00,                     // nop          ; don't check lives counter
    0x00 };                   // nop

const Tbyte TailsAdvBank0Hacks::saveHackData1[saveHackLength1] = {
  205, 47, 133, 205, 55, 133, 205, 161, 22, 58, 
  16, 209, 254, 2, 32, 3, 195, 100, 128, 195, 
  35, 128, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0 };

const Tbyte TailsAdvBank0Hacks::saveHackData2[saveHackLength2] = {
  195, 245, 22 };

const Tbyte TailsAdvBank0Hacks::saveHackData3[saveHackLength3] = {
  195, 96, 22, 0, 0 };

const Tbyte TailsAdvBank0Hacks::saveHackData4[saveHackLength4] = {
  62, 8, 50, 252, 255, 58, 32, 128, 254, 0, 
  40, 13, 14, 0, 1, 32, 0, 17, 36, 208, 
  33, 0, 128, 237, 176, 62, 0, 50, 252, 255, 
  33, 46, 208, 203, 86, 40, 5, 62, 2, 50, 
  66, 208, 175, 50, 208, 210, 62, 16, 50, 170, 
  210, 195, 229, 15, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 62, 8, 50, 252, 255, 
  14, 0, 1, 32, 0, 17, 0, 128, 33, 36, 
  208, 237, 176, 62, 255, 50, 32, 128, 62, 0, 
  50, 252, 255, 201, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  73, 32, 99, 97, 110, 39, 116, 32, 98, 101, 
  97, 116, 32, 89, 117, 107, 97, 114, 105, 62, 
  8, 50, 252, 255, 6, 19, 17, 226, 22, 33, 
  33, 128, 26, 190, 32, 6, 35, 19, 16, 248, 
  24, 29, 33, 0, 128, 17, 1, 128, 1, 32, 
  0, 175, 119, 237, 176, 62, 0, 50, 32, 128, 
  33, 226, 22, 17, 33, 128, 1, 19, 0, 237, 
  176, 62, 0, 50, 252, 255, 195, 190, 4, 0, 
  0, 205, 67, 38, 205, 161, 22, 201, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0 };

const Tbyte TailsAdvBank0Hacks::autoSaveHackData[autoSaveHackLength] = {
  205, 51, 23 };

};
