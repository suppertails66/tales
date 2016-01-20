#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/TailsAdvGraphicCompressor.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include "structs/KeyedTableBuilder.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/NotEnoughSpaceException.h"
#include "exception/UnrecognizedVersionException.h"
#include "gamedata/CharacterUncompressedGraphicHeader.h"
#include "gamedata/StandardUncompressedGraphicHeader.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include <cstring>
#include <iostream>

// TODO: remove this
#include "gamedata/TailsAdvAddresses.h"

using namespace Luncheon;

namespace Tales {


const Taddress EditableLevelGraphicsData
    ::itemPickupGraphicAddress(126064);
const Taddress EditableLevelGraphicsData
    ::endingFlickyExplosionGraphicAddress(167104);
const Taddress EditableLevelGraphicsData
    ::endingBigRobotGraphicAddress(167344);
const Taddress EditableLevelGraphicsData
    ::tailsHouseClawGraphicAddress(179728);
const Taddress EditableLevelGraphicsData
    ::itemPickup2GraphicAddress(179920);
const Taddress EditableLevelGraphicsData
    ::tailsHouseItemIconsGraphicAddress(183752);
const Taddress EditableLevelGraphicsData
    ::remoteRobotIconGraphicAddress(188106);
const Taddress EditableLevelGraphicsData
    ::debris1GraphicAddress(233472);
const Taddress EditableLevelGraphicsData
    ::debris2GraphicAddress(233504);
const Taddress EditableLevelGraphicsData
    ::debris3GraphicAddress(233536);
const Taddress EditableLevelGraphicsData
    ::debris4GraphicAddress(233584);
const Taddress EditableLevelGraphicsData
    ::segaLogoGraphicAddress(262144);
const Taddress EditableLevelGraphicsData
    ::levelSelectFontGraphicAddress(263792);
const Taddress EditableLevelGraphicsData
    ::titleScreenGraphicAddress(311296);
const Taddress EditableLevelGraphicsData
    ::tailsHouseGraphicAddress(321348);
const Taddress EditableLevelGraphicsData
    ::passwordGraphicAddress(371264);
const Taddress EditableLevelGraphicsData
    ::passwordSelectorGraphicAddress(373558);
const Taddress EditableLevelGraphicsData
    ::gameOverGraphicAddress(373724);
const Taddress EditableLevelGraphicsData
    ::endingGraphicAddress(401584);
const Taddress EditableLevelGraphicsData
    ::tailsHouseEnglishGraphicAddress(505182);
    
const Taddress EditableLevelGraphicsData
    ::hudGraphicAddress(0x1CF80);
const Taddress EditableLevelGraphicsData
    ::flickyGraphicAddress(0x28B30);
const Taddress EditableLevelGraphicsData
    ::remoteRobotTransformGraphicAddress(0x286A0);
    
//const Taddress EditableLevelGraphicsData
//    ::worldMapMapGraphicAddress(317242);
    
const Taddress EditableLevelGraphicsData
    ::RetForWorldMapAddress(0x7522);
const Tbyte EditableLevelGraphicsData
    ::RetForWorldMapData[RetForWorldMapLength] =
  { 0xF3 };
  
// Fix for hardcoded graphic bank # issues. Several times, the code calls
// a hardcoded graphics loading routine and expects it to switch to a
// particular bank (e.g. containing the tilemaps for the loaded graphics).
// This hack switches the bank back to the expected value before the routine
// returns.
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesHackData[
                      HardcodedBankChangesHackLength] =
  { 0xCD, 0x44, 0x24,   // call 2444  ; load graphic
    0x3E, 0x10,         // ld a,10    ; sega logo bank #
    0x18, 0x0C,         // jr +C      ; jump to calls
    0xCD, 0x44, 0x24,   // call 2444  ; load graphic
    0x3E, 0x13,         // ld a,13    ; title screen tilemap bank #
    0x18, 0x05,         // jr +5      ; jump to calls
    0xCD, 0x44, 0x24,   // call 2444  ; load graphic
    0x3E, 0x16,         // ld a,16    ; game over tilemap bank #
    0xC3, 0x8E, 0x1B,   // jp 1B8E    ; switch bank #
    
    0x3E, 0x18,         // ld a,18    ; credits tilemap bank #
    0xCD, 0x8E, 0x1B,   // call 1B8E  ; switch bank #
    0xC3, 0xC8, 0x22 }; // jp 22C8    ; load tilemap and ret
/*  { 0x3E, 0x13,         // ld a,13    ; title screen tilemap bank #
    0x18, 0x02,         // jr +2      ; jump to calls
    0x3E, 0x16,         // ld a,16    ; game over tilemap bank #
    0xCD, 0x8E, 0x1B,   // call 1B8E  ; switch bank #
    0xC3, 0x44, 0x24,   // jp 2444    ; load graphic and ret
    0x3E, 0x18,         // ld a,18    ; credits tilemap bank #
    0xCD, 0x8E, 0x1B,   // call 1B8E  ; switch bank #
    0xC3, 0xC8, 0x22 }; // jp 22C8    ; load tilemap and ret */
    
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesTrigger1Data[
                      HardcodedBankChangesTrigger1Length] =
  { 0xCD, 0x2B, 0x07 }; // call 72B  ; load title bank for tilemap
    
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesTrigger2Data[
                      HardcodedBankChangesTrigger2Length] =
  { 0xCD, 0x32, 0x07 }; // call 732  ; load game over bank for tilemap
    
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesTrigger3Data[
                      HardcodedBankChangesTrigger3Length] =
  { 0xCD, 0x3A, 0x07 }; // call 73A  ; load credits tilemap
    
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesTrigger4Data[
                      HardcodedBankChangesTrigger4Length] =
  { 0xCD, 0x32, 0x07 }; // call 732  ; load password graphic/bank
                        // (tilemap same as game over)
    
const Tbyte EditableLevelGraphicsData::HardcodedBankChangesTrigger5Data[
                      HardcodedBankChangesTrigger5Length] =
  { 0xCD, 0x24, 0x07 }; // call 724  ; sega logo graphic/bank


EditableLevelGraphicsData::EditableLevelGraphicsData()
  : lastExportSize_(0),
    tableHeaderAddress_(0),
    tableContentAddress_(0),
    mapnumToLevelHeaderIndex_(SubMaps::subMapCounts,
                              PrimaryMaps::primaryMapTableSize) {
  
}

EditableLevelGraphicsData::EditableLevelGraphicsData(
                             LoadedROM& rom,
                             Taddress tableHeaderAddress__,
                             Taddress tableContentAddress__,
                             int numTableEntries,
                             Taddress uncompressedGraphicsHeaderAddress,
                             int numUncompressedGraphicsHeaders,
                             Taddress TailsGraphicsHeadersAddress,
                             int numTailsGraphicsHeaders,
                             Taddress RemoteRobotGraphicsHeadersAddress,
                             int numRemoteRobotGraphicsHeaders)
  : lastExportSize_(0),
    tableHeaderAddress_(tableHeaderAddress__),
    tableContentAddress_(tableContentAddress__),
    mapnumToLevelHeaderIndex_(SubMaps::subMapCounts,
                              PrimaryMaps::primaryMapTableSize) {
  // Step 1: Get raw level header entries
    
  // Read all entries in table content in raw address format.
  // This is temporary and will be used later to produce the "real"
  // entries, which use indices for ease of editing
  RawLevelGraphicsHeaderCollection rawLevelGraphicsHeaders;
  AddressToRawLevelGraphicsHeaderMap sortedRawLevelGraphicsHeaders;
  Taddress rawContentReadAddress = tableContentAddress_;
  for (int i = 0; i < numTableEntries; i++) {
    // Read the raw header
    RawLevelGraphicsHeader header(rom,
                                  rawContentReadAddress);
    
    // Add to temporary storage
    rawLevelGraphicsHeaders.push_back(header);
    
//    std::cout << "header " << i << std::endl;
//    std::cout << '\t' << "vdp: " << header.vdpWriteAddress() << std::endl;
//    std::cout << '\t' << "map: "
//      << header.mapGraphicsAddress() << std::endl;
//    std::cout << '\t' << "obj: "
//      << header.objectGraphicsHeaderAddress() << std::endl;

    // Add to map
    sortedRawLevelGraphicsHeaders.insert(
      AddressToRawLevelGraphicsHeaderPair(
        rawContentReadAddress,
        header));
    
    // Move to next header
    rawContentReadAddress += RawLevelGraphicsHeader::dataSize;
  }
  
  // Create mapping of header indices to addresses
  int levelHeaderIndexNum = 0;
  for (AddressToRawLevelGraphicsHeaderMap::iterator it
          = sortedRawLevelGraphicsHeaders.begin();
       it != sortedRawLevelGraphicsHeaders.end();
       it++) {
    levelHeaderIndexToAddress_.insert(
      IndexToAddressPair(levelHeaderIndexNum++,
                         it->first));
  }
  
  // Create mapping of mapnums to header indices
  KeyedTableBuilder::buildKeyedPrimaryOnlyIndexTable(
                        rom,
                        tableHeaderAddress_,
                        tableContentAddress_,
                        LevelGraphicsHeader::dataSize,
                        mapnumToLevelHeaderIndex_);
  
  // Step 2: Get map graphics addresses
  
  AddressToGraphicIndexMap compressedGraphicSorter;
  
  // Place all map graphic addresses in a map to sort and remove duplicates
  for (RawLevelGraphicsHeaderCollection::iterator
          it = rawLevelGraphicsHeaders.begin();
       it != rawLevelGraphicsHeaders.end();
       it++) {
    // Use placeholder until real indices can be added
    compressedGraphicSorter.insert(
      AddressToGraphicIndexPair(it->mapGraphicAddress(),
                                   0));
  }
  
  // Step 3a: Read raw object graphics headers
  
  // Place object header addresses in a map to sort and remove duplicates
  AddressToObjectGraphicsHeaderIndexMap objectGraphicsHeaderSorter;
  for (RawLevelGraphicsHeaderCollection::iterator
          it = rawLevelGraphicsHeaders.begin();
       it != rawLevelGraphicsHeaders.end();
       it++) {
    // Use placeholder until real indices can be added
    objectGraphicsHeaderSorter.insert(
      AddressToObjectGraphicsHeaderIndexPair(
                                   it->objectGraphicsHeaderAddress(),
                                   0));
  }
  
  // Renumber indices sequentially
  int objectGraphicsHeaderIndexNum = 0;
  for (AddressToObjectGraphicsHeaderIndexMap::iterator
          it = objectGraphicsHeaderSorter.begin();
       it != objectGraphicsHeaderSorter.end();
       it++) {
    it->second = objectGraphicsHeaderIndexNum++;
    
//    std::cout << "object header " << it->second
//      << " address: " << it->first << std::endl;
  }
  
  // Load raw headers
  RawObjectGraphicsHeaderCollection rawObjectGraphicsHeaders;
  AddressToRawObjectGraphicsHeaderMap sortedRawObjectGraphicsHeaders;
  for (AddressToObjectGraphicsHeaderIndexMap::iterator
          it = objectGraphicsHeaderSorter.begin();
       it != objectGraphicsHeaderSorter.end();
       it++) {
    // Read header
    RawObjectGraphicsHeader header(rom,
                                   it->first);
    
    // Add to storage
    rawObjectGraphicsHeaders.push_back(header);
    
    sortedRawObjectGraphicsHeaders.insert(
      AddressToRawObjectGraphicsHeaderPair(
        it->first,
        header));
    
    objectGraphicsHeaderIndexToAddress_.insert(
        IndexToAddressPair(it->second,
                           it->first));
    
//    std::cout << "obj header " << it->second
//      << " size: " << header.size() << std::endl;
  }
  
  // Step 3b: Load object graphics addresses
  
  // Place object graphic addresses in map to sort and remove duplicates
  for (RawObjectGraphicsHeaderCollection::iterator
          it = rawObjectGraphicsHeaders.begin();
       it != rawObjectGraphicsHeaders.end();
       it++) {
    // Iterate over subheaders
    for (int i = 0; i < it->size(); i++) {
      // Get each object graphic address
      Taddress address = it->subheader(i).objectGraphicAddress();
    
      // Use placeholder until real indices can be added
      compressedGraphicSorter.insert(
        AddressToGraphicIndexPair(address,
                                  0));
    }
  }
  
  // Add unlisted graphic addresses
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(itemPickupGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(endingFlickyExplosionGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(endingBigRobotGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(tailsHouseClawGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(itemPickup2GraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(tailsHouseItemIconsGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(remoteRobotIconGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(debris1GraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(debris2GraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(debris3GraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(debris4GraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(segaLogoGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(levelSelectFontGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(titleScreenGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(tailsHouseGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(passwordGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(passwordSelectorGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(gameOverGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(endingGraphicAddress, 0));
  compressedGraphicSorter.insert(
    AddressToGraphicIndexPair(tailsHouseEnglishGraphicAddress, 0));
    
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(itemPickupGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(endingFlickyExplosionGraphicAddress,
                                       0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(endingBigRobotGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(tailsHouseClawGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(itemPickup2GraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(tailsHouseItemIconsGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(remoteRobotIconGraphicAddress, 0));
  // mark debris graphics for no regular export -- they aren't currently
  // handled as a special export, so they won't be exported period
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(debris1GraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(debris2GraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(debris3GraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(debris4GraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(segaLogoGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(levelSelectFontGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(titleScreenGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(tailsHouseGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(passwordGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(passwordSelectorGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(gameOverGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(endingGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(tailsHouseEnglishGraphicAddress, 0));
  // These graphics are used in levels but are also hardcoded in at least one
  // place, so we have to handle them specially
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(hudGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(flickyGraphicAddress, 0));
  specialCompressedGraphicExportAddresses_.insert(
    SpecialExportAddressCollectionPair(remoteRobotTransformGraphicAddress, 0));
  
  // Load graphics and assign indices
  int graphicIndexNum = 0;
  for (AddressToGraphicIndexMap::iterator
         it = compressedGraphicSorter.begin();
       it != compressedGraphicSorter.end();
       it++) {
    // Add proper index
    it->second = graphicIndexNum++;
    
    // GGTileSet to hold loaded data
    GGTileSet tiles;
    
    // Load data
	  TailsAdvGraphicCompressor::decompress(
	            tiles,
						  rom.directRead(it->first),
						  TailsAdvGraphicCompressor::noTableSubstitution);
    
    // Add to primary storage
    compressedGraphics_.push_back(tiles);
    
    // Map index to address
    compressedGraphicIndexToAddress_.insert(
        IndexToAddressPair(it->second,
                           it->first));
						  
    // Compute size
    int totalSize = 0;
    int numTiles = ByteConversion::fromBytes(rom.directRead(it->first 
                                          + graphicDataHeaderNumTiles),
                           ByteSizes::uint16Size,
                           EndiannessTypes::little,
                           SignednessTypes::nosign);
    int dataOffset = ByteConversion::fromBytes(rom.directRead(it->first 
                                          + graphicDataHeaderSourceOffset),
                           ByteSizes::uint16Size,
                           EndiannessTypes::little,
                           SignednessTypes::nosign);
    // Add size of bitpair bytes
    totalSize += (numTiles / graphicDataBitpairDivisor);
    // Add actual compressed data size
    totalSize += dataOffset;
    
    compressedGraphicSizeMap_.push_back(totalSize);
  }
    
  // Generate the dependency groups that determine which compressed graphics
  // must be placed in the same bank
  generateDependencyGroups(compressedGraphicSorter);
  
  // Load uncompressed graphics
  int uncompressedIndexAssigner = 0;
  Tmap<Taddress, StandardUncompressedGraphicHeader> uncompressedHeaders;
  
  // Read and sort Tails and Remote Robot graphic headers
  uncompressedIndexAssigner += importCharacterGraphicsAddresses(
                        rom,
                        uncompressedIndexAssigner,
                        TailsGraphicsHeadersAddress,
                        numTailsGraphicsHeaders);
  uncompressedIndexAssigner += importCharacterGraphicsAddresses(
                        rom,
                        uncompressedIndexAssigner,
                        RemoteRobotGraphicsHeadersAddress,
                        numRemoteRobotGraphicsHeaders);
  
  // Read and sort main uncompressed graphic addresses
  Taddress uncompressedHeaderReadAddress = uncompressedGraphicsHeaderAddress;
  for (int i = 0; i < numUncompressedGraphicsHeaders; i++) {
    // Check for terminator
    Tbyte terminator = ByteConversion::fromBytes(
                            rom.directRead(uncompressedHeaderReadAddress),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    
    // Move to next address if at terminator
    if (terminator == 0xFF) {
      ++uncompressedHeaderReadAddress;
      continue;
    }
    
    StandardUncompressedGraphicHeader header;
    uncompressedHeaderReadAddress +=
      header.readFromData(rom.directRead(uncompressedHeaderReadAddress));
    
    // Associate graphic address with header
    uncompressedHeaders.insert(
      Tmap<Taddress, StandardUncompressedGraphicHeader>::PairType(
        header.graphicAddress(),
        header));
  }
  
  // Load uncompressed graphics
  for (Tmap<Taddress, StandardUncompressedGraphicHeader>::iterator
         it = uncompressedHeaders.begin();
       it != uncompressedHeaders.end();
       it++) {
    Taddress readAddress = it->second.graphicAddress();
    
    // Disallow certain invalid addresses
    if ((readAddress == invalidUncompressedAddress1)
        || (readAddress == invalidUncompressedAddress2)
        || (readAddress == invalidUncompressedAddress3)
        || (readAddress == invalidUncompressedAddress4)) {
      continue;
    }
    
//    std::cout << std::hex << readAddress << std::endl;
       
    GGTileSet tiles(it->second.numTiles());
    
    // Read uncompressed data
    for (int i = 0; i < it->second.numTiles(); i++) {
      tiles[i].assignFromInterleavedPixels(
                    rom.directRead(readAddress));
      readAddress += GGTile::rawInputDataSize;
    }
    
    // Add to storage
    uncompressedGraphics_.push_back(tiles);
    uncompressedGraphicIndexToAddress_.insert(
      IndexToAddressMap::PairType(
        uncompressedIndexAssigner,
        it->second.graphicAddress()));
    
    ++uncompressedIndexAssigner;
  }
  
  // Step 4: Create indexed object graphics header table
  
  for (AddressToRawObjectGraphicsHeaderMap::iterator
          it = sortedRawObjectGraphicsHeaders.begin();
       it != sortedRawObjectGraphicsHeaders.end();
       it++) {
    // Created indexed header
    ObjectGraphicsHeader header;
    
    // Add subheaders
    for (int i = 0; i < it->second.size(); i++) {
      RawObjectGraphicSubheader& subheader
        = it->second.subheader(i);
    
      header.push_back(
        ObjectGraphicSubheader(subheader.vdpWriteAddress(),
                               compressedGraphicSorter.findValueOrThrow(
                                 subheader.objectGraphicAddress()),
                               subheader.substitutionEnabled()
                                 ? ObjectGraphicSubheader
                                    ::substitutionEnabled
                                 : ObjectGraphicSubheader
                                    ::substitutionDisabled));
    }
    
    // Remember raw size of header for future exports
    objectGraphicsHeaderIndexToSize_.push_back(
      header.rawSize());
    
    // Insert into storage
    objectGraphicsHeaders_.push_back(header);
  }
  
  // Step 5: Create indexed level graphics header table
  
  for (AddressToRawLevelGraphicsHeaderMap::iterator
          it = sortedRawLevelGraphicsHeaders.begin();
       it != sortedRawLevelGraphicsHeaders.end();
       it++) {
    // Created indexed header
    LevelGraphicsHeader header(
        it->second.vdpWriteAddress(),
        compressedGraphicSorter.findValueOrThrow(
          it->second.mapGraphicAddress()),
        objectGraphicsHeaderSorter.findValueOrThrow(
          it->second.objectGraphicsHeaderAddress()));
    
    // Insert into storage
    levelGraphicsHeaders_.push_back(header);
  }
  
  // Remember our size for future reference
  lastExportSize_ = totalDataSize();
}

void EditableLevelGraphicsData::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::levelGraphicsData,
                   0);
  
  // Write last export size
  ByteConversion::toBytes(lastExportSize_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Write table header address
  ByteConversion::toBytes(tableHeaderAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Write table content address
  ByteConversion::toBytes(tableContentAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Save mapnum to level header index mapping
  mapnumToLevelHeaderIndex_.writeToData(data);
  
  // Save graphics
  
  // Save number of compressed graphics
  ByteConversion::toBytes(compressedGraphics_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Save compressed graphics
  for (IndexToGraphicMap::iterator it = compressedGraphics_.begin();
       it != compressedGraphics_.end();
       it++) {
    it->save(data);
  }
  for (IndexToGraphicSizeMap::iterator it = compressedGraphicSizeMap_.begin();
       it != compressedGraphicSizeMap_.end();
       it++) {
    ByteConversion::toBytes((*it),
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
  }
  
  // Save number of uncompressed graphics
  ByteConversion::toBytes(uncompressedGraphics_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Save uncompressed graphics
  for (IndexToGraphicMap::iterator it = uncompressedGraphics_.begin();
       it != uncompressedGraphics_.end();
       it++) {
    it->save(data);
  }
  
  // Save headers
  
  // Save level headers
  
  ByteConversion::toBytes(levelGraphicsHeaders_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (LevelGraphicsHeaderCollection::iterator it
          = levelGraphicsHeaders_.begin();
       it != levelGraphicsHeaders_.end();
       it++) {
    it->save(data);
  }
  
  // Save object headers
  
  ByteConversion::toBytes(objectGraphicsHeaders_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (ObjectGraphicsHeaderCollection::iterator it
          = objectGraphicsHeaders_.begin();
       it != objectGraphicsHeaders_.end();
       it++) {
    it->save(data);
  }
  
  // Save object header sizes
  for (IndexToHeaderSizeMap::iterator it
         = objectGraphicsHeaderIndexToSize_.begin();
       it != objectGraphicsHeaderIndexToSize_.end();
       it++) {
    ByteConversion::toBytes(*it,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
  }
  
  // Save special export addresses
  
  ByteConversion::toBytes(specialCompressedGraphicExportAddresses_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (SpecialExportAddressCollection::iterator it
          = specialCompressedGraphicExportAddresses_.begin();
       it != specialCompressedGraphicExportAddresses_.end();
       it++) {
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
  
  // Save compressed graphic export dependency groups
  
  ByteConversion::toBytes(compressedGraphicDependencies_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (GraphicDependencyGroupCollection::iterator it
          = compressedGraphicDependencies_.begin();
       it != compressedGraphicDependencies_.end();
       it++) {
    it->save(data);
  }
  
  // Save index->address mappings
  levelHeaderIndexToAddress_.save(data);
  compressedGraphicIndexToAddress_.save(data);
  uncompressedGraphicIndexToAddress_.save(data);
  objectGraphicsHeaderIndexToAddress_.save(data);
  
  saver.finalize();
}

int EditableLevelGraphicsData::load(const Tbyte* data) {
  // Clear existing data
  compressedGraphics_.clear();
  compressedGraphicSizeMap_.clear();
  compressedGraphicIndexToAddress_.clear();
  uncompressedGraphics_.clear();
  uncompressedGraphicIndexToAddress_.clear();
  objectGraphicsHeaderIndexToSize_.clear();
  levelGraphicsHeaders_.clear();
  specialCompressedGraphicExportAddresses_.clear();
  compressedGraphicDependencies_.clear();
  objectGraphicsHeaders_.clear();
  levelHeaderIndexToAddress_.clear();
  objectGraphicsHeaderIndexToAddress_.clear();
  
  // Count of read bytes
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableLevelGraphicsData::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::levelGraphicsData,
                                       "EditableLevelGraphicsData",
                                       loader.version(),
                                       0);
  }
  
  // Read last export size
  lastExportSize_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read table header address
  tableHeaderAddress_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read table content address
  tableContentAddress_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read mapnum to level header index mapping
  byteCount += mapnumToLevelHeaderIndex_.readFromData(data + byteCount);
  
  // Load graphics
  
  // Read number of compressed graphics
  int numGraphics = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read each compressed graphic
  for (int i = 0; i < numGraphics; i++) {
    GGTileSet tiles;
    byteCount += tiles.load(data + byteCount);
    compressedGraphics_.push_back(tiles);
  }
  for (int i = 0; i < numGraphics; i++) {
    int graphicSize = ByteConversion::fromBytes(
                                  data + byteCount,
                                  ByteSizes::uint16Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    compressedGraphicSizeMap_.push_back(graphicSize);
  }
  
  // Read number of uncompressed graphics
  int numUncompressedGraphics = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read each uncompressed graphic
  for (int i = 0; i < numUncompressedGraphics; i++) {
    GGTileSet tiles;
    byteCount += tiles.load(data + byteCount);
    uncompressedGraphics_.push_back(tiles);
  }
  
  // Load headers
  
  // Load level headers
  
  int numLevelHeaders = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numLevelHeaders; i++) {
    LevelGraphicsHeader header;
    byteCount += header.load(data + byteCount);
    levelGraphicsHeaders_.push_back(header);
  }
  
  // Load object headers
  
  int numObjectHeaders = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numObjectHeaders; i++) {
    ObjectGraphicsHeader header;
    byteCount += header.load(data + byteCount);
    objectGraphicsHeaders_.push_back(header);
  }
  
  for (int i = 0; i < numObjectHeaders; i++) {
    int headerSize = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    objectGraphicsHeaderIndexToSize_.push_back(headerSize);
  }
  
  // Read special export addresses
  
  int numSpecialAddresses = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numSpecialAddresses; i++) {
    int specialAddress = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    specialCompressedGraphicExportAddresses_.insert(
      SpecialExportAddressCollectionPair(
        specialAddress, 0));
  }
  
  // Read compressed graphic dependency groups
  
  int numCompressionDependencies = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numCompressionDependencies; i++) {
    GraphicDependencyGroup group;
    byteCount += group.load(data + byteCount);
    compressedGraphicDependencies_.push_back(group);
  }
  
  // Load index->address mappings
  byteCount += levelHeaderIndexToAddress_.load(data + byteCount);
  byteCount += compressedGraphicIndexToAddress_.load(data + byteCount);
  byteCount += uncompressedGraphicIndexToAddress_.load(data + byteCount);
  byteCount += objectGraphicsHeaderIndexToAddress_.load(data + byteCount);
  
  // Return count of bytes read
  return byteCount;
}

void EditableLevelGraphicsData::exportToROM(WritableROM& rom) {
  // Copy the index->address and index->size maps. The class members are
  // permanent storage for the initial addresses; we always want to try
  // to use those if possible. These copies are used to keep track of
  // where everything goes during the actual export.
  IndexToAddressMap exportObjHeaderAddresses
    = objectGraphicsHeaderIndexToAddress_;
  IndexToAddressMap exportLevelHeaderAddresses
    = levelHeaderIndexToAddress_;
  IndexToHeaderSizeMap exportObjHeaderSizes
    = objectGraphicsHeaderIndexToSize_;
  IndexToGraphicSizeMap exportCompressedGraphicSizes
    = compressedGraphicSizeMap_;
  IndexToAddressMap exportCompressedGraphicAddresses
    = compressedGraphicIndexToAddress_;

  // Export compressed graphics
  exportGraphics(rom,
                 compressedGraphics_,
                 exportCompressedGraphicAddresses,
                 exportCompressedGraphicSizes);
                 
  // Export uncompressed graphics
  exportUncompressedGraphics(rom,
                 uncompressedGraphics_,
                 uncompressedGraphicIndexToAddress_);
                 
  // Export special compressed graphics
  exportSpecialGraphics(rom,
                 compressedGraphics_,
                 exportCompressedGraphicAddresses,
                 exportCompressedGraphicSizes);
                 
  // Add world map ret mini-hack so that altered world map graphics
  // will be correctly reflected
  rom.directWrite(RetForWorldMapAddress,
                  RetForWorldMapData,
                  RetForWorldMapLength);
                  
  // Add hardcoded graphics hack
  rom.directWrite(HardcodedBankChangesHackAddress,
                  HardcodedBankChangesHackData,
                  HardcodedBankChangesHackLength);
  rom.directWrite(HardcodedBankChangesTrigger1Address,
                  HardcodedBankChangesTrigger1Data,
                  HardcodedBankChangesTrigger1Length);
  rom.directWrite(HardcodedBankChangesTrigger2Address,
                  HardcodedBankChangesTrigger2Data,
                  HardcodedBankChangesTrigger2Length);
  rom.directWrite(HardcodedBankChangesTrigger3Address,
                  HardcodedBankChangesTrigger3Data,
                  HardcodedBankChangesTrigger3Length);
  rom.directWrite(HardcodedBankChangesTrigger4Address,
                  HardcodedBankChangesTrigger4Data,
                  HardcodedBankChangesTrigger4Length);
  rom.directWrite(HardcodedBankChangesTrigger5Address,
                  HardcodedBankChangesTrigger5Data,
                  HardcodedBankChangesTrigger5Length);
                 
  // Export headers
  
  // First, determine whether we need to move the level header table
  
  bool needMove = false;
  
  // If any object header exceeds its original size, we need to move
  for (int i = 0; i < objectGraphicsHeaders_.size(); i++) {
    if (objectGraphicsHeaders_[i].rawSize()
          > exportObjHeaderSizes[i]) {
      needMove = true;
      break;
    }
  }
  
  if (needMove) {
    int totalSize = totalDataSize()
                      + TailsAdvBank0Hacks::levelHeaderHackCodeDataSize;
    
//    std::cout << "larger: went from " << lastExportSize_
//      << " to " << totalSize << std::endl;
      
    // Total size has increased: find space in ROM for data
    
    // The game requires the object graphics headers list to be in the
    // same bank as the level header. Thus, if we move the data to a new
    // bank, we have to make sure we claim sufficient space for both headers.
    // TODO: We don't actually need this much space if we don't change
    // banks; under rare circumstances, this could lead to failure even
    // if there is sufficient room for all the data
    FreeSpaceList::iterator spaceIt
        = rom.freeSpace().getFreeSpace(totalSize);
    
    // Throw if not enough space available
    if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
      throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                    "EditableLevelGraphicsData::"
                                    "exportToROM(WritableROM&)",
                                    totalSize);
    }

    // If we haven't changed banks, we don't need to claim extra space for
    // the level header
//    if ((spaceIt->address() >= currentBankBaseAddress)
//        && (spaceIt->address() < currentBankLimitAddress)) {
//      totalHeaderSize = header.rawSize();
//    }
    
//      std::cout << "old address: " << writeAddress << std::endl;

    Taddress oldAddress = tableHeaderAddress_;
                               
    // Get new address
    tableHeaderAddress_ = spaceIt->address();
    
    tableContentAddress_ 
      = tableHeaderAddress_
          + (mapnumToLevelHeaderIndex_.numPrimaryKeys()
                * ByteSizes::uint16Size);
    
//    std::cout << "level table header addr: "
//      << std::hex << tableHeaderAddress_ << std::endl;
//    std::cout << "level table content addr: "
//      << std::hex << tableContentAddress_ << std::endl;
                              
    // Claim space.
    // If the header has changed banks, we claim enough space here to fit
    // the level header as well; we export it there later.
    rom.freeSpace().claimSpace(spaceIt,
                               totalSize);
    
    // Free existing space
//    rom.freeSpace().giveSpace(oldAddress,
//                              lastExportSize_);
    
    // Export object headers
    
    // Object headers go in the space directly after the level header table
    Taddress objWriteAddress = tableHeaderAddress_
                                  + totalLevelHeaderTableSize();
                                  
    // Copy initial address map for future updates
//    IndexToAddressMap objectGraphicsHeaderAddresses
//      = exportObjHeaderAddresses;
                                  
    // Export each object header
    for (int i = 0; i < objectGraphicsHeaders_.size(); i++) {
        
      ObjectGraphicsHeader& header = objectGraphicsHeaders_[i];
      
      // Update address map
      exportObjHeaderAddresses.findValueOrThrow(i)
        = objWriteAddress;
      
      // Update size map
      exportObjHeaderSizes[i] = header.rawSize();
        
      // Write header to ROM
      header.exportToData(
          rom.directWrite(objWriteAddress),
          exportCompressedGraphicAddresses);
      
      // Move to next write position
      objWriteAddress += header.rawSize();
    }
    
    // Export level header table
    Taddress levelHeaderWriteAddress = tableHeaderAddress_;
    Taddress levelContentWriteAddress = tableContentAddress_;
    
    // Write the table content
    for (int i = 0; i < levelGraphicsHeaders_.size(); i++) {
      // Update address to new position
      exportLevelHeaderAddresses.findValueOrThrow(i)
        = levelContentWriteAddress;
            
      // Get map graphic and object header indices
      Taddress mapGraphicAddress
        = exportCompressedGraphicAddresses.findValueOrThrow(
            levelGraphicsHeaders_[i].mapGraphicIndex());
      Taddress objectGraphicsHeaderAddress
        = exportObjHeaderAddresses.findValueOrThrow(
            levelGraphicsHeaders_[i].objectGraphicsHeaderIndex());
            
      Taddress objectGraphicsHeaderBankedAddress
        = LoadedROM::directToBankedAddress(objectGraphicsHeaderAddress);
                                        
      // Convert to slot 1 address for hack
      objectGraphicsHeaderBankedAddress -= LoadedROM::bankSize;
      
      // Export header to ROM
      levelGraphicsHeaders_[i]
          .exportToData(rom.directWrite(levelContentWriteAddress),
                        mapGraphicAddress,
                        objectGraphicsHeaderBankedAddress);
                        
//      std::cout << "index " << std::hex << i << " address: "
//          << exportLevelHeaderAddresses.findValueOrThrow(i) << std::endl;
      
      // Move to next write address
      levelContentWriteAddress += LevelGraphicsHeader::dataSize;
    }
    
    // Write the table header
    for (int i = 0; i < mapnumToLevelHeaderIndex_.numPrimaryKeys(); i++) {
    
      // If entry has no subkeys, fill with first entry
      if (mapnumToLevelHeaderIndex_.subKeyTable()[i] <= 0) {
        Taddress levelBankedAddress = LoadedROM::directToBankedAddress(
                                        tableContentAddress_);
                                        
        // Convert to slot 1 address for hack
        levelBankedAddress -= LoadedROM::bankSize;
                                        
        // Write to ROM
        ByteConversion::toBytes(levelBankedAddress,
                                rom.directWrite(levelHeaderWriteAddress),
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
        
        levelHeaderWriteAddress += ByteSizes::uint16Size;
        
        // Move to next primary map num
        continue;
      }
              
  //    std::cout << std::hex << headerAddress << std::endl;
  
      Taddress index = mapnumToLevelHeaderIndex_
                         .refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                                        0 + TwoKeyedAddress::subKeyBase);
                                        
//      std::cout << "map " << i << "-1: " << index << std::endl;
                                        
//      std::cout << index << std::endl;
      
      Taddress levelAddress
        = exportLevelHeaderAddresses.findValueOrThrow(index);
      
//      std::cout << std::hex << levelAddress << std::endl;
      
      // Convert direct address to banked
      Taddress levelBankedAddress = LoadedROM::directToBankedAddress(
                                      levelAddress);
                                      
      // Convert to slot 1 address for hack
      levelBankedAddress -= LoadedROM::bankSize;
      
      // Write address
      ByteConversion::toBytes(levelBankedAddress,
                              rom.directWrite(levelHeaderWriteAddress),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      
      // Move to next postion
      levelHeaderWriteAddress += ByteSizes::uint16Size;
      
    }
    
    // Add level header hack so we can access the new table
    TailsAdvBank0Hacks::addLevelHeaderHack(rom,
                                           tableHeaderAddress_,
                                           tableHeaderAddress_
                                             + totalSize
                          - TailsAdvBank0Hacks::levelHeaderHackCodeDataSize);
    
//    std::cout << tableHeaderAddress_ << " " << totalSize
//        << " " << TailsAdvBank0Hacks::levelHeaderHackCodeDataSize
//        << std::endl;
    
    // Update last export size              
    lastExportSize_ = totalSize;
    
    return;
  }
  
                 
  // Export object headers
  for (int i = 0; i < objectGraphicsHeaders_.size(); i++) {
    Taddress writeAddress
      = exportObjHeaderAddresses.findValueOrThrow(i);
      
    ObjectGraphicsHeader& header = objectGraphicsHeaders_[i];
    int headerSize = exportObjHeaderSizes[i];
      
    header.exportToData(
        rom.directWrite(writeAddress),
        exportCompressedGraphicAddresses);
  }

  // Export level headers
  for (int i = 0; i < levelGraphicsHeaders_.size(); i++) {
    Taddress headerAddress
      = exportLevelHeaderAddresses.findValueOrThrow(
          i);
          
//    std::cout << std::hex << headerAddress << std::endl;
          
    Taddress mapGraphicAddress
      = exportCompressedGraphicAddresses.findValueOrThrow(
          levelGraphicsHeaders_[i].mapGraphicIndex());
    Taddress objectGraphicsHeaderAddress
      = exportObjHeaderAddresses.findValueOrThrow(
          levelGraphicsHeaders_[i].objectGraphicsHeaderIndex());
    
    // Export header to ROM
    levelGraphicsHeaders_[i].exportToData(rom.directWrite(headerAddress),
                                          mapGraphicAddress,
                                          objectGraphicsHeaderAddress);
  }
}
  
int EditableLevelGraphicsData::totalLevelHeaderTableSize() {
  int total = 0;
  
  // Add size of header
  total += (tableContentAddress_ - tableHeaderAddress_);
  
  // Add size of each entry
  total += (levelGraphicsHeaders_.size() * LevelGraphicsHeader::dataSize);
  
  return total;
}
  
int EditableLevelGraphicsData::totalObjectHeaderSize() {
  int total = 0;
  
  // Add size of each header
  for (ObjectGraphicsHeaderCollection::iterator it
         = objectGraphicsHeaders_.begin();
       it != objectGraphicsHeaders_.end();
       it++) {
    total += it->rawSize();
  }
  
  return total;
}
  
int EditableLevelGraphicsData::totalDataSize() {
  int total = 0;
  
  // Add size of level header table
  total += totalLevelHeaderTableSize();
  
  // Add size of all object headers
  total += totalObjectHeaderSize();
  
  return total;
}
                        
int EditableLevelGraphicsData::importCharacterGraphicsAddresses(
                      LoadedROM& rom,
                      int index,
                      Taddress headerTableAddress,
                      int numHeaders) {
  Taddress readAddress = headerTableAddress;
  Tmap<Taddress, CharacterUncompressedGraphicHeader> uncompressedHeaders;
  
  // Read headers
  for (int i = 0; i < numHeaders; i++) {
//    std::cout << "header addr: " << std::hex << readAddress << std::endl;
    
    CharacterUncompressedGraphicHeader header;
    readAddress += header.readFromData(rom.directRead(readAddress));
    
    uncompressedHeaders.insert(
      Tmap<Taddress, CharacterUncompressedGraphicHeader>
        ::PairType(
          readAddress,
          header));
       
//    std::cout << "grp addr: " << header.graphicAddress() << std::endl;
//    std::cout << "numtiles: "
//      << header.numTiles() << std::endl;
  }
  
  // Read graphics
  for (Tmap<Taddress, CharacterUncompressedGraphicHeader>::iterator
          it = uncompressedHeaders.begin();
       it != uncompressedHeaders.end();
       it++) {
       
    Taddress readAddress = it->second.graphicAddress();
    
    int numTiles = it->second.numTiles();
       
    // HACK: the header for the last frame of Tails' animation for
    // throwing a bomb while jumping has an incorrect length in the
    // original game, causing it to display incorrectly. When that specific
    // graphic is loaded, we fix the length so that we import the full
    // graphic.
    if (it->second.graphicAddress()
            == badTailsBombJumpGraphicLengthAddress) {
      numTiles = 0x10;
    }
    
//    std::cout << std::hex << readAddress << std::endl;
       
    GGTileSet tiles(numTiles);
    
    // Read uncompressed data
    for (int i = 0; i < numTiles; i++) {
      tiles[i].assignFromInterleavedPixels(
                    rom.directRead(readAddress));
      readAddress += GGTile::rawInputDataSize;
    }
    
    // Add to storage
    uncompressedGraphics_.push_back(tiles);
    uncompressedGraphicIndexToAddress_.insert(
      IndexToAddressMap::PairType(
        index,
        it->second.graphicAddress()));
    
    ++index;
  }
  
  return uncompressedHeaders.size();
}
  
void EditableLevelGraphicsData::exportGraphics(
                    WritableROM& rom,
                    IndexToGraphicMap& graphics,
                    IndexToAddressMap& indexToAddress,
                    IndexToGraphicSizeMap& indexToSize) {
  for (int i = 0; i < graphics.size(); i++) {
    Taddress oldAddress = indexToAddress.findValueOrThrow(i);
    
    // Check if this graphic's address is on the list of special export
    // graphics
    if (specialCompressedGraphicExportAddresses_.find(oldAddress)
          != specialCompressedGraphicExportAddresses_.end()) {
//      std::cout << i << std::endl;
      // Ignore special export graphics -- they have to be handled separately
      continue;
    }
  
    std::string compressedData;
    
    TailsAdvGraphicCompressor::compress(
                    compressedData,
                    graphics[i],
                    TailsAdvGraphicCompressor::noTableSubstitution);
    
//    std::cout << "in " << i << ": " << indexToSize[i] << std::endl;
//    std::cout << "out " << i << ": " << compressedData.size() << std::endl;
    
    // Save to original location if size is less than or equal to previous
//    if (compressedData.size() <= indexToSize[i]) {
    if (false) {
      Taddress oldAddress = indexToAddress.findValueOrThrow(i);
//      std::cout << "Writing to previous address: " << oldAddress << std::endl;
      
      rom.directWrite(oldAddress,
                      (const Tbyte*)(compressedData.c_str()),
                      compressedData.size());
    }
    else {
      // Find free space
      FreeSpaceList::iterator spaceIt
          = rom.freeSpace().getFreeSpace(compressedData.size());
      
      // Throw if space isn't available
      if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
        throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                      "EditableLevelGraphicsData::"
                                      "exportGraphics(WritableROM&,"
                                      "IndexToGraphicMap&,"
                                      "IndexToAddressMap&"
                                      "IndexToGraphicSizeMap&)",
                                      compressedData.size());
      }
      
//      std::cout << "moved graphic " << i << " to "
//        << std::hex << spaceIt->address() << "-"
//        << spaceIt->address() + compressedData.size() << std::endl;
      
      // Remember current address so we can update maps
//      Taddress oldAddress = indexToAddress.findValueOrThrow(i);
                                 
      // Get new address
      Taddress newBaseAddress = spaceIt->address();
      
      // Claim the free space we need
      rom.freeSpace().claimSpace(spaceIt,
                                 compressedData.size());
      
      // Free space at old location
      rom.freeSpace().giveSpace(oldAddress,
                                indexToSize[i]);
                                
      // Write data to new location
      rom.directWrite(newBaseAddress,
                      (const Tbyte*)(compressedData.c_str()),
                      compressedData.size());
      
      // Update maps
      indexToAddress[i] = newBaseAddress;
      indexToSize[i] = compressedData.size();
      
//      std::cout << "Writing to new address: " << newBaseAddress << std::endl;
    }
  }
}

void EditableLevelGraphicsData::exportUncompressedGraphics(
                      WritableROM& rom,
                      IndexToGraphicMap& graphics,
                      IndexToAddressMap& indexToAddress) {
  for (int i = 0; i < graphics.size(); i++) {
    Taddress writeAddress = indexToAddress.findValueOrThrow(i);
    
    graphics[i].writeNativeUncompressed(rom.directWrite(writeAddress));
  }
}

void EditableLevelGraphicsData::exportSpecialGraphics(
          WritableROM& rom,
          IndexToGraphicMap& graphics,
          IndexToAddressMap& indexToAddress,
          IndexToGraphicSizeMap& indexToSize) {
  for (GraphicDependencyGroupCollection::iterator it
         = compressedGraphicDependencies_.begin();
       it != compressedGraphicDependencies_.end();
       it++) {
    // Compress all graphics in the group
    int totalSize = 0;
    std::vector<std::string> comprGrp;
    bool larger = false;
    for (GraphicDependencyGroupEntryCollection::iterator jt
           = it->entries().begin();
         jt != it->entries().end();
         jt++) {
      std::string compressedData;
      TailsAdvGraphicCompressor::compress(
                      compressedData,
                      compressedGraphics_[jt->graphicAddress()],
                      TailsAdvGraphicCompressor::noTableSubstitution);
      totalSize += compressedData.size();
      
      int prevSize = indexToSize[jt->graphicAddress()];
      
      if (compressedData.size() > prevSize) {
//        std::cout << "here" << std::endl;
        larger = true;
      }
      
      comprGrp.push_back(compressedData);
    }
    
//    std::cout << totalSize << std::endl;

    // If none of the graphics' size increased, we can simply export them
    // to their existing locations
    if (!larger) {
      for (int i = 0; i < comprGrp.size(); i++) {
        // Get original address
        Taddress writeAddress = indexToAddress[
                                  it->entries()[i].graphicAddress()];
        
        // Copy to ROM
        rom.directWrite(writeAddress,
                        (const Tbyte*)(comprGrp[i].c_str()),
                        comprGrp[i].size());
        
      }
      continue;
    }
    
    // If at least one graphic's size increased, we must move all of the
    // graphics in the group to a new location.
    // Technically the requirement is merely that the graphics must all be in
    // the same bank, but for the sake of simplicity we just look for a free
    // chunk that can hold all the graphics in one group.
    // TODO: smarter allocation
    
//    std::cout << "here" << std::endl;
    
    // Find free space
    FreeSpaceList::iterator spaceIt
        = rom.freeSpace().getFreeSpace(totalSize);
    
    // Throw if space isn't available
    if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
      throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                    "EditableLevelGraphicsData::"
                                    "exportSpecialGraphics(WritableROM&,"
                                    "IndexToGraphicMap&,"
                                    "IndexToAddressMap&"
                                    "IndexToGraphicSizeMap&)",
                                    totalSize);
    }
    
    // Get new address
    Taddress newBaseAddress = spaceIt->address();
    
    // Claim the free space we need
    rom.freeSpace().claimSpace(spaceIt,
                               totalSize);
                               
    // Update bank pointer(s)
    int newBankPointer = LoadedROM::directToBankNum(newBaseAddress);
    for (int i = 0; i < it->bankPointerAddresses().size(); i++) {
      ByteConversion::toBytes(newBankPointer,
                              rom.directWrite(it->bankPointerAddresses()[i]),
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    }
    
    // Free space at old locations and write new data
    for (int i = 0; i < comprGrp.size(); i++) {
      int index = it->entries()[i].graphicAddress();
    
      // Get original address
      Taddress oldAddress = indexToAddress[index];
      
      // Free space
      rom.freeSpace().giveSpace(oldAddress,
                                indexToSize[index]);
                              
      // Write data to new location
      rom.directWrite(newBaseAddress,
                      (const Tbyte*)(comprGrp[i].c_str()),
                      comprGrp[i].size());
      
      // Update maps
      indexToAddress[index] = newBaseAddress;
      indexToSize[index] = comprGrp[i].size();
    
      // Update address pointer(s)
      GraphicDependencyGroupEntry& entry = it->entries()[i];
      for (int j = 0; j < entry.pointerAddresses().size(); j++) {
        Taddress writeAddress = entry.pointerAddresses()[j];
        Taddress graphicBankedAddress
          = LoadedROM::directToBankedAddress(newBaseAddress);
                        
        ByteConversion::toBytes(graphicBankedAddress,
                                rom.directWrite(writeAddress),
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
      }
      
      // Move to next write address
      newBaseAddress += comprGrp[i].size();
    }
       
/*    std::string compressedData;
    
    TailsAdvGraphicCompressor::compress(
                    compressedData,
                    graphics[i],
                    TailsAdvGraphicCompressor::noTableSubstitution);
    
    // Save to original location if size is less than or equal to previous
    if (compressedData.size() <= indexToSize[i]) {
      Taddress oldAddress = indexToAddress.findValueOrThrow(i);
      
      rom.directWrite(oldAddress,
                      (const Tbyte*)(compressedData.c_str()),
                      compressedData.size());
    }
    else {
      // Find free space
      FreeSpaceList::iterator spaceIt
          = rom.freeSpace().getFreeSpace(compressedData.size());
      
      // Throw if space isn't available
      if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
        throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                      "EditableLevelGraphicsData::"
                                      "exportGraphics(WritableROM&,"
                                      "IndexToGraphicMap&,"
                                      "IndexToAddressMap&"
                                      "IndexToGraphicSizeMap&)",
                                      LoadedROM::bankSize);
      }
                                 
      // Get new address
      Taddress newBaseAddress = spaceIt->address();
      
      // Claim the free space we need
      rom.freeSpace().claimSpace(spaceIt,
                                 compressedData.size());
      
      // Free space at old location
      rom.freeSpace().giveSpace(oldAddress,
                                indexToSize[i]);
                                
      // Write data to new location
      rom.directWrite(newBaseAddress,
                      (const Tbyte*)(compressedData.c_str()),
                      compressedData.size());
    } */
  }
}
  
int EditableLevelGraphicsData::levelHeaderIndexByMapnum(
                        int primaryMapNum,
                        int subMapNum) {
  // Throw if primary key out of range
  if ((unsigned int)primaryMapNum
        >= mapnumToLevelHeaderIndex_.numPrimaryKeys()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "levelHeaderIndexByMapnum("
                                   "int,int) [PRIMARY]",
                                   primaryMapNum);
  }
  
  // Throw if subkey out of range
  if ((unsigned int)subMapNum
        > mapnumToLevelHeaderIndex_.subKeyTable()[primaryMapNum]) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "levelHeaderIndexByMapnum("
                                   "int,int) [SUB]",
                                   subMapNum);
  }
  
  return mapnumToLevelHeaderIndex_.refDataByKeys(
                                      primaryMapNum,
                                      subMapNum);
}
  
int EditableLevelGraphicsData::levelGraphicsHeadersSize() const {
  return levelGraphicsHeaders_.size();
}

int EditableLevelGraphicsData::objectGraphicsHeadersSize() const {
  return objectGraphicsHeaders_.size();
}
  
int EditableLevelGraphicsData::compressedGraphicsSize() const {
  return compressedGraphics_.size();
}
  
int EditableLevelGraphicsData::uncompressedGraphicsSize() const {
  return uncompressedGraphics_.size();
}
  
int EditableLevelGraphicsData::numBaseObjectGraphicsHeaders() {
  return 25;
}
  
void EditableLevelGraphicsData::insertObjectGraphicsHeader(
        const ObjectGraphicsHeader& header) {
  // Add new header to back of map
  objectGraphicsHeaders_.push_back(header);
  
  // Put a zero in the index to size map. Since we've added
  // a new header, we'll need extra space to use it, and the
  // check for whether to do so is whether the header's rawSize()
  // is greater than its listed size. This ensures the header table
  // will be properly regenerated on export. The real value will be
  // filled in when that happens.
  // TODO: something better
  objectGraphicsHeaderIndexToSize_.push_back(0);
  
  // Put placeholder in index to address map for similar reasons (we
  // won't know where the object will go until export)
    objectGraphicsHeaderIndexToAddress_.insert(
      IndexToAddressPair(objectGraphicsHeaders_.size() - 1,
                         0));
}
  
void EditableLevelGraphicsData::insertObjectGraphicsHeader(
        const ObjectGraphicsHeader& header,
        int index) {
  if (index == objectGraphicsHeaders_.size() - 1) {
    insertObjectGraphicsHeader(header);
    return;
  }
        
  ObjectGraphicsHeaderCollection::iterator it1
    = objectGraphicsHeaders_.begin();
  IndexToHeaderSizeMap::iterator it2
    = objectGraphicsHeaderIndexToSize_.begin();
  IndexToAddressMap::iterator it3
    = objectGraphicsHeaderIndexToAddress_.begin();
  
  for (int i = 0; i < index; i++) {
    ++it1;
    ++it2;
    ++it3;
  }
  
//  ++it3;
  
  objectGraphicsHeaders_.insert(it1,
                                header);
  
  objectGraphicsHeaderIndexToSize_.insert(it2,
                                          0);
  
  // Renumber all headers after the inserted one
  IndexToAddressMap::iterator it4 = objectGraphicsHeaderIndexToAddress_.end();
  --it4;
  
  while (it4 != it3) {
    int key = it4->first;
    ++key;
    int value = it4->second;
    IndexToAddressMap::iterator eraseIt = it4--;
    
    objectGraphicsHeaderIndexToAddress_.erase(eraseIt);
    
    objectGraphicsHeaderIndexToAddress_.insert(
      IndexToAddressPair(key,
                         value));
  }
  
  // Change first key
  int key = it4->first;
  ++key;
  int value = it4->second;
  IndexToAddressMap::iterator eraseIt = it4;
  
  objectGraphicsHeaderIndexToAddress_.erase(eraseIt);
  
  objectGraphicsHeaderIndexToAddress_.insert(
    IndexToAddressPair(key,
                       value));
  
  // Insert actual key
  objectGraphicsHeaderIndexToAddress_.insert(
      IndexToAddressPair(index,
                         0));
}

void EditableLevelGraphicsData::eraseObjectGraphicsHeader(int index) {
  ObjectGraphicsHeaderCollection::iterator it1
    = objectGraphicsHeaders_.begin();
  IndexToHeaderSizeMap::iterator it2
    = objectGraphicsHeaderIndexToSize_.begin();
  IndexToAddressMap::iterator it3
    = objectGraphicsHeaderIndexToAddress_.begin();
  
  for (int i = 0; i < index; i++) {
    ++it1;
    ++it2;
    ++it3;
  }
  
  ++it3;
  
  objectGraphicsHeaders_.erase(it1);
  objectGraphicsHeaderIndexToSize_.erase(it2);
  objectGraphicsHeaderIndexToAddress_.erase(
    objectGraphicsHeaderIndexToAddress_.findOrThrow(index));
  
  // Renumber all headers after the erased one
  while (it3 != objectGraphicsHeaderIndexToAddress_.end()) {
    int key = it3->first;
    --key;
    int value = it3->second;
    IndexToAddressMap::iterator eraseIt = it3++;
    
    objectGraphicsHeaderIndexToAddress_.erase(eraseIt);
    
    objectGraphicsHeaderIndexToAddress_.insert(
      IndexToAddressPair(key,
                         value));
  }
//  objectGraphicsHeaderIndexToAddress_.erase(it3);
}
  
LevelGraphicsHeader& EditableLevelGraphicsData
    ::levelGraphicsHeader(int index) {
  // Throw if out of range
  if ((unsigned int)index >= levelGraphicsHeaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "levelGraphicsHeader(int)",
                                   index);
  }
  
  return levelGraphicsHeaders_[index];
}

ObjectGraphicsHeader& EditableLevelGraphicsData
    ::objectGraphicsHeader(int index) {
  // Throw if out of range
  if ((unsigned int)index >= objectGraphicsHeaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "objectGraphicsHeader(int)",
                                   index);
  }
  
  return objectGraphicsHeaders_[index];
}
  
GGTileSet& EditableLevelGraphicsData
    ::compressedGraphic(int index) {
  // Throw if out of range
  if ((unsigned int)index >= compressedGraphics_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "compressedGraphic(int)",
                                   index);
  }
  
  return compressedGraphics_[index];
}
  
GGTileSet& EditableLevelGraphicsData
    ::uncompressedGraphic(int index) {
  // Throw if out of range
  if ((unsigned int)index >= uncompressedGraphics_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelGraphicsData::"
                                   "uncomrpessedGraphic(int)",
                                   index);
  }
  
  return uncompressedGraphics_[index];
}
  
void EditableLevelGraphicsData::generateDependencyGroups(
    const AddressToGraphicIndexMap& compressedGraphicSorter) {
  // Add dependency groups
  // these really, really REALLY need to be their own classes
  // TODO: make these their own classes
  
  // ending 1: endingGraphicAddress
  // ending 2: hudGraphicAddress
  // ending 3: endingBigRobotGraphicAddress,
  // flickyGraphicAddress, endingFlickyExplosionGraphicAddress
  // tails house main 1: tailsHouseItemIconsGraphicAddress,
  // remoteRobotIconGraphicAddress
  // tails house main 2: tailsHouseGraphicAddress
  // tails house main 3: tailsHouseEnglishGraphicAddress
  // tails house dock 1: tailsHouseClawGraphicAddress,
  // remoteRobotTransform
  // password 1: passwordGraphicAddress
  // item pickup 1: itemPickup2GraphicAddress
  // game over 1: gameOverGraphicAddress
  // level select 1: levelSelectFontGraphicAddress
  // sega logo 1: segaLogoGraphicAddress
  
  // entries
  
  // ending background
  GraphicDependencyGroupEntry endingGraphicEntry(
    compressedGraphicSorter
      .findValueOrThrow(endingGraphicAddress));
  endingGraphicEntry.pointerAddresses().push_back(0x7640);
  
  // hud graphics
  GraphicDependencyGroupEntry hudGraphicEntry(
    compressedGraphicSorter
      .findValueOrThrow(hudGraphicAddress));
  hudGraphicEntry.pointerAddresses().push_back(0x765F);
  
  // ending big robot
  GraphicDependencyGroupEntry endingBigRobotEntry(
    compressedGraphicSorter
      .findValueOrThrow(endingBigRobotGraphicAddress));
  endingBigRobotEntry.pointerAddresses().push_back(0x7671);
  
  // intro/ending flicky
  GraphicDependencyGroupEntry flickyEntry(
    compressedGraphicSorter
      .findValueOrThrow(flickyGraphicAddress));
  flickyEntry.pointerAddresses().push_back(0x767E);
  flickyEntry.pointerAddresses().push_back(0x7698);  // flipped version
  
  // ending flicky explosion
  GraphicDependencyGroupEntry endingFlickyExplosionEntry(
    compressedGraphicSorter
      .findValueOrThrow(endingFlickyExplosionGraphicAddress));
  endingFlickyExplosionEntry.pointerAddresses().push_back(0x768B);
  
  // tails house item icons
  GraphicDependencyGroupEntry tailsHouseItemIconsEntry(
    compressedGraphicSorter
      .findValueOrThrow(tailsHouseItemIconsGraphicAddress));
  tailsHouseItemIconsEntry.pointerAddresses().push_back(0x757F);
  tailsHouseItemIconsEntry.pointerAddresses().push_back(0x75D2);  // dock
  
  // remote robot icon
  GraphicDependencyGroupEntry remoteRobotIconEntry(
    compressedGraphicSorter
      .findValueOrThrow(remoteRobotIconGraphicAddress));
  remoteRobotIconEntry.pointerAddresses().push_back(0x758C);
  
  // tails house background graphics
  GraphicDependencyGroupEntry tailsHouseEntry(
    compressedGraphicSorter
      .findValueOrThrow(tailsHouseGraphicAddress));
  tailsHouseEntry.pointerAddresses().push_back(0x759E);
  
  // tails house english text
  GraphicDependencyGroupEntry tailsHouseEnglishEntry(
    compressedGraphicSorter
      .findValueOrThrow(tailsHouseEnglishGraphicAddress));
  tailsHouseEnglishEntry.pointerAddresses().push_back(0x75B6);
  
  // tails house dock claw
  GraphicDependencyGroupEntry tailsHouseClawEntry(
    compressedGraphicSorter
      .findValueOrThrow(tailsHouseClawGraphicAddress));
  tailsHouseClawEntry.pointerAddresses().push_back(0x75EE);
  
  // remote robot transform
  GraphicDependencyGroupEntry remoteRobotTransformEntry(
    compressedGraphicSorter
      .findValueOrThrow(remoteRobotTransformGraphicAddress));
  remoteRobotTransformEntry.pointerAddresses().push_back(0x75FB);
  
  // password background
  GraphicDependencyGroupEntry passwordEntry(
    compressedGraphicSorter
      .findValueOrThrow(passwordGraphicAddress));
  passwordEntry.pointerAddresses().push_back(0x7557);
  
  // item pickup 2
  GraphicDependencyGroupEntry itemPickup2Entry(
    compressedGraphicSorter
      .findValueOrThrow(itemPickup2GraphicAddress));
  itemPickup2Entry.pointerAddresses().push_back(0x7613);
  
  // game over
  GraphicDependencyGroupEntry gameOverEntry(
    compressedGraphicSorter
      .findValueOrThrow(gameOverGraphicAddress));
  gameOverEntry.pointerAddresses().push_back(0x7628);
  
  // level select font
  GraphicDependencyGroupEntry levelSelectFontEntry(
    compressedGraphicSorter
      .findValueOrThrow(levelSelectFontGraphicAddress));
  levelSelectFontEntry.pointerAddresses().push_back(0x74F7);
  
  // title screen
  GraphicDependencyGroupEntry titleScreenEntry(
    compressedGraphicSorter
      .findValueOrThrow(titleScreenGraphicAddress));
  titleScreenEntry.pointerAddresses().push_back(0x750B);
  
  // sega logo (currently not used due to need for hack to sort out banking)
  GraphicDependencyGroupEntry segaLogoEntry(
    compressedGraphicSorter
      .findValueOrThrow(segaLogoGraphicAddress));
  segaLogoEntry.pointerAddresses().push_back(0x2BFC);
  
  // groups
  
  // credits 1
  GraphicDependencyGroup creditsGroup1;
  creditsGroup1.bankPointerAddresses().push_back(0x7635);
  creditsGroup1.entries().push_back(endingGraphicEntry);
  compressedGraphicDependencies_.push_back(creditsGroup1);
    
  // credits 2
  GraphicDependencyGroup creditsGroup2;
  creditsGroup2.bankPointerAddresses().push_back(0x7654);
  creditsGroup2.entries().push_back(hudGraphicEntry);
  compressedGraphicDependencies_.push_back(creditsGroup2);
    
  // credits 3
  GraphicDependencyGroup creditsGroup3;
  creditsGroup3.bankPointerAddresses().push_back(0x7666);
  creditsGroup3.entries().push_back(endingBigRobotEntry);
  creditsGroup3.entries().push_back(flickyEntry);
  creditsGroup3.entries().push_back(endingFlickyExplosionEntry);
  compressedGraphicDependencies_.push_back(creditsGroup3);
    
  // tails house main 1
  GraphicDependencyGroup tailsHouseMainGroup1;
  tailsHouseMainGroup1.bankPointerAddresses().push_back(0x7574);
  tailsHouseMainGroup1.bankPointerAddresses().push_back(0x75C7);  // dock
  tailsHouseMainGroup1.entries().push_back(tailsHouseItemIconsEntry);
  tailsHouseMainGroup1.entries().push_back(remoteRobotIconEntry);
  compressedGraphicDependencies_.push_back(tailsHouseMainGroup1);
    
  // tails house main 2
  GraphicDependencyGroup tailsHouseMainGroup2;
  tailsHouseMainGroup2.bankPointerAddresses().push_back(0x7593);
  tailsHouseMainGroup2.entries().push_back(tailsHouseEntry);
  compressedGraphicDependencies_.push_back(tailsHouseMainGroup2);
    
  // tails house main 3
  GraphicDependencyGroup tailsHouseMainGroup3;
  tailsHouseMainGroup3.bankPointerAddresses().push_back(0x75AB);
  tailsHouseMainGroup3.entries().push_back(tailsHouseEnglishEntry);
  compressedGraphicDependencies_.push_back(tailsHouseMainGroup3);
    
  // tails house dock 1
  GraphicDependencyGroup tailsHouseDockGroup1;
  tailsHouseDockGroup1.bankPointerAddresses().push_back(0x75E3);
  tailsHouseDockGroup1.entries().push_back(tailsHouseClawEntry);
  tailsHouseDockGroup1.entries().push_back(remoteRobotTransformEntry);
  compressedGraphicDependencies_.push_back(tailsHouseDockGroup1);
    
  // password 1
  GraphicDependencyGroup passwordGroup1;
  passwordGroup1.bankPointerAddresses().push_back(0x754C);
  passwordGroup1.entries().push_back(passwordEntry);
  compressedGraphicDependencies_.push_back(passwordGroup1);
    
  // item pickup 2 1
  GraphicDependencyGroup itemPickup2Group1;
  itemPickup2Group1.bankPointerAddresses().push_back(0x7608);
  itemPickup2Group1.entries().push_back(itemPickup2Entry);
  compressedGraphicDependencies_.push_back(itemPickup2Group1);
    
  // game over 1
  GraphicDependencyGroup gameOverGroup1;
  gameOverGroup1.bankPointerAddresses().push_back(0x761D);
  gameOverGroup1.entries().push_back(gameOverEntry);
  compressedGraphicDependencies_.push_back(gameOverGroup1);
    
  // level select 1
  GraphicDependencyGroup levelSelectGroup1;
  levelSelectGroup1.bankPointerAddresses().push_back(0x74EC);
  levelSelectGroup1.entries().push_back(levelSelectFontEntry);
  compressedGraphicDependencies_.push_back(levelSelectGroup1);
    
  // title screen 1
  GraphicDependencyGroup titleScreenGroup1;
  titleScreenGroup1.bankPointerAddresses().push_back(0x7500);
  titleScreenGroup1.entries().push_back(titleScreenEntry);
  compressedGraphicDependencies_.push_back(titleScreenGroup1);
    
  // sega logo 1
  GraphicDependencyGroup segaLogoGroup1;
  segaLogoGroup1.bankPointerAddresses().push_back(0x2BEE);
  segaLogoGroup1.entries().push_back(segaLogoEntry);
  compressedGraphicDependencies_.push_back(segaLogoGroup1);
  
}


};
