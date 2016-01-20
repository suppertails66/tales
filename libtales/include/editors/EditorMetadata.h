#ifndef EDITORMETADATA_H
#define EDITORMETADATA_H


#include "structs/Tbyte.h"
#include "editors/LevelMetadataEntry.h"
#include "editors/AreaMetadataEntry.h"
#include "editors/MetatileStructureDefaultMap.h"
#include "editors/GraphicPaletteDefaultMap.h"
#include "editors/HackSettings.h"
#include "structs/TwoKeyedData.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "structs/DataChunkID.h"
#include <vector>
#include <string>

namespace Tales {


typedef TwoKeyedData<LevelMetadataEntry> LevelMetadataMap;
typedef std::vector<AreaMetadataEntry> AreaMetadataMap;

class EditorMetadata {
public:
  EditorMetadata();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  /**
   * Returns true if the given area number is valid.
   */
  static bool areaNumIsValid(int areaNum);
  
  /**
   * Returns true if the given area number contains editable levels.
   */
  static bool areaNumHasEditableLevels(int areaNum);
  
  /**
   * Returns true if the given area number has manipulable VRAM indices.
   */
  static bool areaNumHasVRAMIndices(int areaNum);
  
  AreaMetadataMap& areaMetadataMap();
  AreaMetadataEntry& areaMetadata(int areaNum);
  
  std::string exportFileLocation();
  void setExportFileLocation(const std::string& exportFileLocation__);
  
  MetatileStructureDefaultMap& metatileStructureDefaults();
  
  GraphicPaletteDefaultMap& compressedGraphicPaletteDefaults();
  GraphicPaletteDefaultMap& uncompressedGraphicPaletteDefaults();
  
  HackSettings& hackSettings();
protected:

  const static int versionNum_ = 1;
  
  const static int areaNumBase = 1;
  
  const static int areaNumLimit = 22;
  
  /**
   * Intializes metadata to default values for a clean ROM.
   */
  void initializeDefaults();
  
  /**
   * Intializes area metadata to default values for a clean ROM.
   */
  void initializeAreaDefaults();
  
  /**
   * Intializes level metadata to default values for a clean ROM.
   */
  void initializeLevelDefaults();
  
  void initializeMetatileStructureDefaults();
  
  void initializeGraphicPaletteDefaults();
  
  void saveGraphicPaletteDefaultMap(
                    std::string& data,
                    GraphicPaletteDefaultMap& src);
  
  int loadGraphicPaletteDefaultMap(
                    GraphicPaletteDefaultMap& dst,
                    const Tbyte* data);
  
  /**
   * Mapping of area numbers to their metadata.
   */
  AreaMetadataMap areaMetadata_;
  
  /**
   * Mapping of level numbers to their metadata.
   */
  LevelMetadataMap levelMetadata_;
  
  MetatileStructureDefaultMap metatileStructureDefaults_;
  
  GraphicPaletteDefaultMap compressedGraphicPaletteDefaults_;
  GraphicPaletteDefaultMap uncompressedGraphicPaletteDefaults_;
  
  HackSettings hackSettings_;
  
  std::string exportFileLocation_;
  
  
};


};


#endif
