#ifndef DATACHUNKID_H
#define DATACHUNKID_H


namespace Tales {


/**
 * Container for enum of rsource chunk IDs.
 */
class DataChunkIDs {
public:
  
  /**
   * Enum of resource chunk IDs.
   * Do NOT insert new entries in the middle of this list -- always append!
   * These are used to identify data during serialization, and changing
   * existing IDs will break save file compatibility between different
   * versions.
   */
  enum DataChunkID {
    null                            = 0,
    fileStart,
    fileEnd,
    emeraldHealthRefills,
    leafGraphicsTable,
    levelEffectsHeaders,
    levelGraphicsData,
    levelHeaders,
    levelObjectEntryGroups,
    levelPaletteHeaders,
    mapData,
    metatileBehaviors,
    metatileHeightMaps,
    metatileLengthMaps,
    metatileWidthMaps,
    musicAssignments,
    paletteCycles,
    powerUpData,
    radioMusic,
    slopeSpeedValues,
    smokePuffGraphicTable,
    spawnPoints,
    spriteMappings,
    standardPalettes,
    warpDestinations,
    waterSplashGraphicTable,
    
    tailsAdvEditorStart,
    tailsAdvEditorEnd,
    editorMetadata,
    levelMetadataEntry,
    areaMetadataEntry,
    hackSettings
  };
};


};


#endif
