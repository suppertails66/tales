#include "exception/UnrecognizedVersionException.h"
#include "gamedata/EditablePaletteCycles.h"
#include "gamedata/TailsAdvAddresses.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditablePaletteCycles::EditablePaletteCycles() { };

EditablePaletteCycles::EditablePaletteCycles(LoadedROM& rom) {
  torchPaletteCycle_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::TorchPaletteCycle),
                         TorchPaletteCycleBaseIndex,
                         TorchPaletteCycleNumColors,
                         TorchPaletteCycleNumStates);
                         
  lakeRockyMainPaletteCycle_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyMainPaletteCycle),
                         LakeRockyMainPaletteCycleIndex,
                         LakeRockyMainPaletteCycleNumColors,
                         LakeRockyMainPaletteCycleNumStates);
                         
  lakeRockyTopPaletteCycle1_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyTopPaletteCycle1),
                         LakeRockyTopPaletteCycle1Index,
                         LakeRockyTopPaletteCycle1NumColors,
                         LakeRockyTopPaletteCycle1NumStates);
                         
  lakeRockyTopPaletteCycle2_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyTopPaletteCycle2),
                         LakeRockyTopPaletteCycle2Index,
                         LakeRockyTopPaletteCycle2NumColors,
                         LakeRockyTopPaletteCycle2NumStates);
                         
  lakeRockyBottomPaletteCycle1_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyBottomPaletteCycle1),
                         LakeRockyBottomPaletteCycle1Index,
                         LakeRockyBottomPaletteCycle1NumColors,
                         LakeRockyBottomPaletteCycle1NumStates);
                         
  lakeRockyBottomPaletteCycle2_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyBottomPaletteCycle2),
                         LakeRockyBottomPaletteCycle2Index,
                         LakeRockyBottomPaletteCycle2NumColors,
                         LakeRockyBottomPaletteCycle2NumStates);
                         
  lakeRockyBottomPaletteCycle3_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::LakeRockyBottomPaletteCycle3),
                         LakeRockyBottomPaletteCycle3Index,
                         LakeRockyBottomPaletteCycle3NumColors,
                         LakeRockyBottomPaletteCycle3NumStates);
                         
  cavernIslandPaletteCycle_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::CavernIslandPaletteCycle),
                         CavernIslandPaletteCycleIndex,
                         CavernIslandPaletteCycleNumColors,
                         CavernIslandPaletteCycleNumStates);
                         
  importPoloyForestPaletteCycle(rom);
                         
  worldMapPaletteCycle_.standardReadFromData(
          rom.directRead(TailsAdvAddresses::WorldMapPaletteCycle),
                         WorldMapPaletteCycleIndex,
                         WorldMapPaletteCycleNumColors,
                         WorldMapPaletteCycleNumStates);
  
  
}

void EditablePaletteCycles::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::paletteCycles,
                   0);
                   
  torchPaletteCycle_.save(data);
  lakeRockyMainPaletteCycle_.save(data);
  lakeRockyTopPaletteCycle1_.save(data);
  lakeRockyTopPaletteCycle2_.save(data);
  lakeRockyBottomPaletteCycle1_.save(data);
  lakeRockyBottomPaletteCycle2_.save(data);
  lakeRockyBottomPaletteCycle3_.save(data);
  cavernIslandPaletteCycle_.save(data);
  poloyForestPaletteCycle_.save(data);
  worldMapPaletteCycle_.save(data);
  
  saver.finalize();
}

int EditablePaletteCycles::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditablePaletteCycles::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::paletteCycles,
                                       "EditablePaletteCycles",
                                       loader.version(),
                                       0);
  }
  
  byteCount += torchPaletteCycle_.load(data + byteCount);
  byteCount += lakeRockyMainPaletteCycle_.load(data + byteCount);
  byteCount += lakeRockyTopPaletteCycle1_.load(data + byteCount);
  byteCount += lakeRockyTopPaletteCycle2_.load(data + byteCount);
  byteCount += lakeRockyBottomPaletteCycle1_.load(data + byteCount);
  byteCount += lakeRockyBottomPaletteCycle2_.load(data + byteCount);
  byteCount += lakeRockyBottomPaletteCycle3_.load(data + byteCount);
  byteCount += cavernIslandPaletteCycle_.load(data + byteCount);
  byteCount += poloyForestPaletteCycle_.load(data + byteCount);
  byteCount += worldMapPaletteCycle_.load(data + byteCount);
  
  return byteCount;
}

void EditablePaletteCycles::exportToROM(WritableROM& rom) {
  torchPaletteCycle_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::TorchPaletteCycle));
  lakeRockyMainPaletteCycle_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyMainPaletteCycle));
  lakeRockyTopPaletteCycle1_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyTopPaletteCycle1));
  lakeRockyTopPaletteCycle2_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyTopPaletteCycle2));
  lakeRockyBottomPaletteCycle1_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyBottomPaletteCycle1));
  lakeRockyBottomPaletteCycle2_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyBottomPaletteCycle2));
  lakeRockyBottomPaletteCycle3_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::LakeRockyBottomPaletteCycle3));
  cavernIslandPaletteCycle_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::CavernIslandPaletteCycle));
  exportPoloyForestPaletteCycle(rom);
  worldMapPaletteCycle_.standardWriteToData(
      rom.directWrite(TailsAdvAddresses::WorldMapPaletteCycle));
}
  
PaletteCycle& EditablePaletteCycles::torchPaletteCycle() {
  return torchPaletteCycle_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyMainPaletteCycle() {
  return lakeRockyMainPaletteCycle_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyTopPaletteCycle1() {
  return lakeRockyTopPaletteCycle1_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyTopPaletteCycle2() {
  return lakeRockyTopPaletteCycle2_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyBottomPaletteCycle1() {
  return lakeRockyBottomPaletteCycle1_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyBottomPaletteCycle2() {
  return lakeRockyBottomPaletteCycle2_;
}

PaletteCycle& EditablePaletteCycles::lakeRockyBottomPaletteCycle3() {
  return lakeRockyBottomPaletteCycle3_;
}

PaletteCycle& EditablePaletteCycles::cavernIslandPaletteCycle() {
  return cavernIslandPaletteCycle_;
}

PaletteCycle& EditablePaletteCycles::poloyForestPaletteCycle() {
  return poloyForestPaletteCycle_;
}

PaletteCycle& EditablePaletteCycles::worldMapPaletteCycle() {
  return worldMapPaletteCycle_;
}

void EditablePaletteCycles::importPoloyForestPaletteCycle(LoadedROM& rom) {
  // Poloy Forest's palette cycle is stored in the following format:
  // [s0c0] [s1c0] [s2c0]
  // [s0c1] [s0c2]
  // [s1c1] [s1c2]
  // [s2c1] [s2c2]
  // where s0c1 means color 1 of state 0. Color 0 goes to index 0,
  // color 1 goes to index 14, and color 2 goes to index 15.
  
  for (int i = 0;
       i < PoloyForestPaletteCycleNumStates;
       i++) {
    PaletteCycleState state;
    
    GGColor color0;
    color0.setNativeColor(ByteConversion::fromBytes(
                            rom.directRead(TailsAdvAddresses::
                              PoloyForestPaletteCycle + (i * 2)),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign));
    
    GGColor color14;
    color14.setNativeColor(ByteConversion::fromBytes(
                            rom.directRead(TailsAdvAddresses::
                              PoloyForestPaletteCyclePart2 + (i * 4) + 0),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign));
    
    GGColor color15;
    color15.setNativeColor(ByteConversion::fromBytes(
                            rom.directRead(TailsAdvAddresses::
                              PoloyForestPaletteCyclePart2 + (i * 4) + 2),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign));
    
    
    state.insertColor(PoloyForestPaletteCycleFirstColorIndex,
                      color0);
    state.insertColor(PoloyForestPaletteCycleSecondColorIndex,
                      color14);
    state.insertColor(PoloyForestPaletteCycleThirdColorIndex,
                      color15);
    
    poloyForestPaletteCycle_.addState(state);
  }
}

void EditablePaletteCycles::exportPoloyForestPaletteCycle(WritableROM& rom) {
  for (int i = 0; i < poloyForestPaletteCycle_.numStates(); i++) {
    ByteConversion::toBytes(poloyForestPaletteCycle_.state(i)
                              .color(PoloyForestPaletteCycleFirstColorIndex)
                                .nativeColor(),
                            rom.directWrite(TailsAdvAddresses::
                              PoloyForestPaletteCycle + (i * 2)),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
                            
    ByteConversion::toBytes(poloyForestPaletteCycle_.state(i)
                              .color(PoloyForestPaletteCycleSecondColorIndex)
                                .nativeColor(),
                            rom.directWrite(TailsAdvAddresses::
                              PoloyForestPaletteCyclePart2 + (i * 4) + 0),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
                            
    ByteConversion::toBytes(poloyForestPaletteCycle_.state(i)
                              .color(PoloyForestPaletteCycleThirdColorIndex)
                                .nativeColor(),
                            rom.directWrite(TailsAdvAddresses::
                              PoloyForestPaletteCyclePart2 + (i * 4) + 2),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
  }
}


};
