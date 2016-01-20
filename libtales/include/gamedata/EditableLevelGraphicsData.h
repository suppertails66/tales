#ifndef EDITABLELEVELGRAPHICSDATA_H
#define EDITABLELEVELGRAPHICSDATA_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamegear/GGTileSet.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/KeyedTableBuilder.h"
#include "gamedata/RawLevelGraphicsHeader.h"
#include "gamedata/RawObjectGraphicsHeader.h"
#include "gamedata/LevelGraphicsHeader.h"
#include "gamedata/ObjectGraphicsHeader.h"
#include "structs/IndexToAddressMap.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "structs/GraphicDependencyGroup.h"
#include <utility>
#include <string>
#include <vector>

namespace Tales {


typedef std::vector<RawLevelGraphicsHeader> RawLevelGraphicsHeaderCollection;
typedef std::vector<RawObjectGraphicsHeader> RawObjectGraphicsHeaderCollection;

typedef std::pair<int, bool> IndexAndSubstitutionEnabledPair;

typedef Tmap<Taddress, int> AddressToGraphicIndexMap;
typedef AddressToGraphicIndexMap::PairType AddressToGraphicIndexPair;

//typedef Tmap<int, Taddress> IndexToMapGraphicMap;
//typedef IndexToMapGraphicMap::PairType IndexToMapGraphicPair;
typedef Tmap<Taddress, int> AddressToMapGraphicIndexMap;
typedef AddressToMapGraphicIndexMap::PairType AddressToMapGraphicIndexPair;

typedef Tmap<Taddress, int> AddressToObjectGraphicsHeaderIndexMap;
typedef AddressToObjectGraphicsHeaderIndexMap::PairType
    AddressToObjectGraphicsHeaderIndexPair;
    
typedef Tmap<Taddress, IndexAndSubstitutionEnabledPair>
    AddressToObjectGraphicIndexMap;
typedef AddressToObjectGraphicIndexMap::PairType
    AddressToObjectGraphicIndexPair;
    
typedef Tmap<Taddress, RawLevelGraphicsHeader>
    AddressToRawLevelGraphicsHeaderMap;
typedef AddressToRawLevelGraphicsHeaderMap::PairType
    AddressToRawLevelGraphicsHeaderPair;
    
typedef Tmap<Taddress, RawObjectGraphicsHeader>
    AddressToRawObjectGraphicsHeaderMap;
typedef AddressToRawObjectGraphicsHeaderMap::PairType
    AddressToRawObjectGraphicsHeaderPair;
    
typedef std::vector<LevelGraphicsHeader> LevelGraphicsHeaderCollection;
typedef std::vector<ObjectGraphicsHeader> ObjectGraphicsHeaderCollection;

typedef std::vector<GGTileSet> IndexToGraphicMap;

//typedef std::vector<bool> IndexToObjectGraphicFlipMap;
typedef std::vector<int> IndexToGraphicSizeMap;
typedef std::vector<int> IndexToHeaderSizeMap;

typedef Tmap<Taddress, int> SpecialExportAddressCollection;
typedef SpecialExportAddressCollection::PairType
  SpecialExportAddressCollectionPair;

typedef std::vector<GraphicDependencyGroup> GraphicDependencyGroupCollection;

/**
 * Storage for and access on level graphics headers and associated data.
 * This includes the level graphics headers themselves, the object graphics
 * headers, the map graphics, and the object graphics.
 */
class EditableLevelGraphicsData {
public:
  /**
   * Default constructor.
   */
  EditableLevelGraphicsData();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param tableHeaderAddress__ Direct address of the graphics header table.
   * @param tableContentAddress__ Direct address of the table content.
   * @param numTableEntries Number of entries in the graphics header table.
   */
  EditableLevelGraphicsData(LoadedROM& rom,
                               Taddress tableHeaderAddress__,
                               Taddress tableContentAddress__,
                               int numTableEntries,
                               Taddress uncompressedGraphicsHeaderAddress,
                               int numUncompressedGraphicsHeaders,
                               Taddress TailsGraphicsHeadersAddress,
                               int numTailsGraphicsHeaders,
                               Taddress RemoteRobotGraphicsHeadersAddress,
                               int numRemoteRobotGraphicsHeaders);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes of data read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes stored data to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  int levelHeaderIndexByMapnum(int primaryMapNum,
                          int subMapNum);
  
  int levelGraphicsHeadersSize() const;
  
  int objectGraphicsHeadersSize() const;
  
  int compressedGraphicsSize() const;
  
  int uncompressedGraphicsSize() const;
  
  int numBaseObjectGraphicsHeaders();
  
  void insertObjectGraphicsHeader(const ObjectGraphicsHeader& header);
  
  void insertObjectGraphicsHeader(const ObjectGraphicsHeader& header,
                                  int index);
  
  void eraseObjectGraphicsHeader(int index);
  
  LevelGraphicsHeader& levelGraphicsHeader(int index);
  
  ObjectGraphicsHeader& objectGraphicsHeader(int index);
  
  GGTileSet& compressedGraphic(int index);
  
  GGTileSet& uncompressedGraphic(int index);
  
protected:
  // A few hardcoded compressed graphic addresses. The game doesn't explicitly
  // reference these in the level headers. They're inserted into the sort map
  // in the constructor and treated as any other compressed graphic from there
  // on.
  // ... Except actually they're not, because any dolt who applied their brain
  // to this problem for half a second would realize this doesn't work if a
  // graphic's location changes due to increased size because the pointers
  // aren't updated. We'll need special (harcoded) handling.
  // TODO: hardcoded address updates for these
  // These probably belong in TailsAdvAddresses or elsewhere, but this will
  // do for now.
  const static Taddress itemPickupGraphicAddress;             // where??
  const static Taddress endingFlickyExplosionGraphicAddress;
  const static Taddress endingBigRobotGraphicAddress;
  const static Taddress tailsHouseClawGraphicAddress;
  const static Taddress itemPickup2GraphicAddress;
  const static Taddress tailsHouseItemIconsGraphicAddress;
  const static Taddress remoteRobotIconGraphicAddress;
  // debris graphics -- need special handling
  const static Taddress debris1GraphicAddress;
  const static Taddress debris2GraphicAddress;
  const static Taddress debris3GraphicAddress;
  const static Taddress debris4GraphicAddress;
  const static Taddress segaLogoGraphicAddress;
  const static Taddress levelSelectFontGraphicAddress;
  const static Taddress titleScreenGraphicAddress;
  const static Taddress tailsHouseGraphicAddress;
  const static Taddress passwordGraphicAddress;
  const static Taddress passwordSelectorGraphicAddress;
  const static Taddress gameOverGraphicAddress;
  const static Taddress endingGraphicAddress;
  const static Taddress tailsHouseEnglishGraphicAddress;
  
  // used in levels, but hardcoded in other places
  
  // ending
  const static Taddress hudGraphicAddress;
  const static Taddress flickyGraphicAddress;
  // tails house dock
  const static Taddress remoteRobotTransformGraphicAddress;
  
  const static int invalidUncompressedIndex1 = 258;
  const static int invalidUncompressedIndex2 = 259;
  const static int invalidUncompressedIndex3 = 301;
  const static int invalidUncompressedIndex4 = 302;
  
  const static Taddress invalidUncompressedAddress1 = 340992;
  const static Taddress invalidUncompressedAddress2 = 341504;
  const static Taddress invalidUncompressedAddress3 = 521218;
  const static Taddress invalidUncompressedAddress4 = 521730;
  
  SpecialExportAddressCollection specialCompressedGraphicExportAddresses_;
  GraphicDependencyGroupCollection compressedGraphicDependencies_;
  
  const static Taddress badTailsBombJumpGraphicLengthAddress = 0x13380;
  
  // Address of the world map map graphics (i.e. non-object graphics).
  // Although ostensibly referenced by the level table, the game seems
  // to use a hardcoded address for these that we'll need to update
  // if the graphic expands.
//  const static Taddress worldMapMapGraphicAddress;

  // Due to screwy programming, changes to world map graphics will not
  // be properly reflected unless we add a RET at this address.
  // Specifically, the issue is that the game reloads the world map
  // graphics from a hardcoded location, even though the main map load
  // routine has already loaded them.
  const static Taddress RetForWorldMapAddress;
  const static int RetForWorldMapLength = 1;
  const static Tbyte RetForWorldMapData[RetForWorldMapLength];
  
//  const static Taddress HardcodedBankChangesHackAddress = 0x74EA;
  const static Taddress HardcodedBankChangesHackAddress = 0x724;
  const static int HardcodedBankChangesHackLength = 30;
  const static Tbyte HardcodedBankChangesHackData[
                        HardcodedBankChangesHackLength];
  
  const static Taddress HardcodedBankChangesTrigger1Address = 0x750E;
  const static int HardcodedBankChangesTrigger1Length = 3;
  const static Tbyte HardcodedBankChangesTrigger1Data[
                        HardcodedBankChangesTrigger1Length];
  
  const static Taddress HardcodedBankChangesTrigger2Address = 0x762B;
  const static int HardcodedBankChangesTrigger2Length = 3;
  const static Tbyte HardcodedBankChangesTrigger2Data[
                        HardcodedBankChangesTrigger2Length];
  
  const static Taddress HardcodedBankChangesTrigger3Address = 0x764F;
  const static int HardcodedBankChangesTrigger3Length = 3;
  const static Tbyte HardcodedBankChangesTrigger3Data[
                        HardcodedBankChangesTrigger3Length];
  
  const static Taddress HardcodedBankChangesTrigger4Address = 0x755A;
  const static int HardcodedBankChangesTrigger4Length = 3;
  const static Tbyte HardcodedBankChangesTrigger4Data[
                        HardcodedBankChangesTrigger4Length];
  
  const static Taddress HardcodedBankChangesTrigger5Address = 0x2BFF;
  const static int HardcodedBankChangesTrigger5Length = 3;
  const static Tbyte HardcodedBankChangesTrigger5Data[
                        HardcodedBankChangesTrigger5Length];

  const static int graphicDataHeaderNumTiles = 2;
  const static int graphicDataHeaderSourceOffset = 4;
  const static int graphicDataHeaderSize = 6;
  const static int graphicDataBitpairDivisor = 4;
  
  int lastExportSize_;

  /**
   * Address of the level graphics header table.
   */
  Taddress tableHeaderAddress_;

  /**
   * Address of the level graphics header table content.
   */
  Taddress tableContentAddress_;
  
  /**
   * Map number to level header index mappings.
   */
  TwoKeyedAddress mapnumToLevelHeaderIndex_;
  
  IndexToGraphicMap compressedGraphics_;
  IndexToGraphicSizeMap compressedGraphicSizeMap_;
  IndexToAddressMap compressedGraphicIndexToAddress_;
  
  IndexToGraphicMap uncompressedGraphics_;
  IndexToAddressMap uncompressedGraphicIndexToAddress_;
  
  IndexToHeaderSizeMap objectGraphicsHeaderIndexToSize_;
  
  /**
   * Storage for level headers.
   */
  LevelGraphicsHeaderCollection levelGraphicsHeaders_;
  
  /**
   * Storage for object headers.
   */
  ObjectGraphicsHeaderCollection objectGraphicsHeaders_;
  
  /**
   * Mapping of level header indices to corresponding addresses.
   */
  IndexToAddressMap levelHeaderIndexToAddress_;
  
  /**
   * Mapping of object graphic header indices to corresponding addresses.
   */
  IndexToAddressMap objectGraphicsHeaderIndexToAddress_;
  
  int totalLevelHeaderTableSize();
  
  int totalObjectHeaderSize();
  
  int totalDataSize();
  
  /**
   * Imports a set of uncompressed character graphics.
   * @param rom ROM to load from.
   * @param index Starting index for numbering imported graphics.
   * @param headerTableAddress Address of the header table to load from.
   * @param numHeaders Number of headers in the table.
   * @return Number of graphics read.
   */
  int importCharacterGraphicsAddresses(
                        LoadedROM& rom,
                        int index,
                        Taddress headerTableAddress,
                        int numHeaders);
  
  /**
   * Exports a set of graphics to ROM.
   * @param graphics Set of graphics to export.
   * @param indexToAddress Mapping of each graphic index (in the input
   * graphics set) to its previous export address.
   * @param indexToSize Mapping of each graphic index (in the input
   * graphics set) to its previous size.
   */
  void exportGraphics(WritableROM& rom,
                      IndexToGraphicMap& graphics,
                      IndexToAddressMap& indexToAddress,
                      IndexToGraphicSizeMap& indexToSize);
  
  /**
   * Exports uncompressed graphics to ROM.
   * @param graphics Set of graphics to export.
   * @param indexToAddress Mapping of each graphic index (in the input
   * graphics set) to its previous export address.
   */
  void exportUncompressedGraphics(WritableROM& rom,
                      IndexToGraphicMap& graphics,
                      IndexToAddressMap& indexToAddress);
  
  /**
   * Exports "special" graphics to ROM.
   * These are hardcoded graphics whose pointers must be manually adjusted
   * if they are moved.
   * @param rom ROM to write to.
   */
  void exportSpecialGraphics(WritableROM& rom,
                             IndexToGraphicMap& graphics,
                             IndexToAddressMap& indexToAddress,
                             IndexToGraphicSizeMap& indexToSize);
  
  void generateDependencyGroups(
      const AddressToGraphicIndexMap& compressedGraphicSorter);
  
};


};


#endif
