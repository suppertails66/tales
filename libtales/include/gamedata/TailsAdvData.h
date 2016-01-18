#ifndef TAILSADVDATA_H
#define TAILSADVDATA_H


#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/TailsAdvEditable.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditablePaletteCycles.h"
#include "gamedata/EditableLevelEffectsHeaders.h"
#include "gamedata/EditableLevelPaletteHeaders.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableLeafGraphicsTable.h"
#include "gamedata/EditableWaterSplashGraphicTable.h"
#include "gamedata/EditableSmokePuffGraphicTable.h"
#include "gamedata/EditableSpriteMappings.h"
#include "gamedata/EditableMusicAssignments.h"
#include "gamedata/EditableRadioMusic.h"
#include "gamedata/EditablePowerUpData.h"
#include "gamedata/EditableEmeraldHealthRefills.h"
#include "gamedata/EditableMetatileWidthMaps.h"
#include "gamedata/EditableMetatileHeightMaps.h"
#include "gamedata/EditableSlopeSpeedValues.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/EditableSpawnPoints.h"
#include "gamedata/EditableWarpDestinations.h"
#include "gamedata/EditableLevelObjectEntryGroups.h"
#include "gamedata/EditableMapData.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


/**
 * Container for all editable Tails Adventure data.
 */
class TailsAdvData : public TailsAdvEditable {
public:
  /**
   * Constructor.
   * @param rom__ A clean Tails Adventures ROM from which to import data.
   */
  TailsAdvData(LoadedROM& rom);
  
  /** 
   * Appends a loadable representation of edited state to the given string.
   * @param data A string to which the representation of the altered state
   * should be appended.
   * @see load()
   */
  virtual void save(std::string& data);
  
  /**  
   * Loads edited state from a block of data written using save().
   * @param data A block of raw data corresponding to a previous call to
   * save().
   * @see save()
   */
  virtual int load(const Tbyte* data);
  
  /**  
   * Writes the contained data to a WritableROM.
   * @param rom WritableROM to write data to.
   */
  virtual void exportToROM(WritableROM& rom);
  
  /**  
   * Writes the contained data to file.
   * @param rom LoadedROM to use as source for unmodified data.
   * @param filename Name of the file to write to.
   */
  virtual void exportToFile(LoadedROM& rom,
                            const std::string& filename);
  
  /**
   * Returns true if output ROMs will be expanded to 1 MB.
   * @return True if output ROMs will be expanded to 1 MB.
   */
  bool romExpanded() const;
  
  /**
   * Setter for romExpanded_;
   * @param romExpanded__ Indicates whether to expand ROM to 1 MB.
   */
  void setRomExpanded(bool romExpanded__);
  
  /**
   * Accessor for standardPalettes_.
   * @returns Reference to standardPalettes_.
   */
  EditableStandardPalettes& standardPalettes();
  
  /**
   * Accessor for paletteCycles_.
   * @returns Reference to paletteCycles_.
   */
  EditablePaletteCycles& paletteCycles();
  
  /**
   * Accessor for levelEffectsHeaders_.
   * @returns Reference to levelEffectsHeaders_.
   */
  EditableLevelEffectsHeaders& levelEffectsHeaders();
  
  /**
   * Accessor for levelPaletteHeaders_.
   * @returns Reference to levelPaletteHeaders_.
   */
  EditableLevelPaletteHeaders& levelPaletteHeaders();
  
  /**
   * Accessor for levelGraphicsData_.
   * @returns Reference to levelGraphicsData_.
   */
  EditableLevelGraphicsData& levelGraphicsData();
  
  /**
   * Accessor for leafGraphicsTable_.
   * @returns Reference to leafGraphicsTable_.
   */
  EditableLeafGraphicsTable& leafGraphicsTable();
  
  /**
   * Accessor for waterSplashGraphicTable_.
   * @returns Reference to waterSplashGraphicTable_.
   */
  EditableWaterSplashGraphicTable& waterSplashGraphicTable();
  
  /**
   * Accessor for smokePuffGraphicTable_.
   * @returns Reference to smokePuffGraphicTable_.
   */
  EditableSmokePuffGraphicTable& smokePuffGraphicTable();
  
  /**
   * Accessor for spriteMappings_.
   * @returns Reference to spriteMappings_.
   */
  EditableSpriteMappings& spriteMappings();
  
  /**
   * Accessor for musicAssignments_.
   * @returns Reference to musicAssignments_.
   */
  EditableMusicAssignments& musicAssignments();
  
  /**
   * Accessor for radioMusic_.
   * @returns Reference to radioMusic_.
   */
  EditableRadioMusic& radioMusic();
  
  /**
   * Accessor for powerUpData_.
   * @returns Reference to powerUpData_.
   */
  EditablePowerUpData& powerUpData();
  
  /**
   * Accessor for emeraldHealthRefills_.
   * @returns Reference to emeraldHealthRefills_.
   */
  EditableEmeraldHealthRefills& emeraldHealthRefills();
  
  /**
   * Accessor for metatileWidthMaps_.
   * @returns Reference to metatileWidthMaps_.
   */
  EditableMetatileWidthMaps& metatileWidthMaps();
  
  /**
   * Accessor for heightMaps_.
   * @returns Reference to heightMaps_.
   */
  EditableMetatileHeightMaps& metatileHeightMaps();
  
  /**
   * Accessor for slopeSpeedValues_.
   * @returns Reference to slopeSpeedValues_.
   */
  EditableSlopeSpeedValues& slopeSpeedValues();
  
  /**
   * Accessor for metatileBehaviors_.
   * @returns Reference to metatileBehaviors_.
   */
  EditableMetatileBehaviors& metatileBehaviors();
  
  /**
   * Accessor for spawnPoints_.
   * @returns Reference to spawnPoints_.
   */
  EditableSpawnPoints& spawnPoints();
  
  /**
   * Accessor for warpDestinations_.
   * @returns Reference to warpDestinations_.
   */
  EditableWarpDestinations& warpDestinations();
  
  /**
   * Accessor for levelObjectEntryGroups_.
   * @returns Reference to levelObjectEntryGroups_.
   */
  EditableLevelObjectEntryGroups& levelObjectEntryGroups();
  
  /**
   * Accessor for mapData_.
   * @returns Reference to mapData_.
   */
  EditableMapData& mapData();
  
protected:

  // Indicates whether ROM has been expanded
  bool romExpanded_;
  
  // AND mask offsets that need to be adjusted if ROM is expanded
  const static Taddress andMaskExpandAdjustAddress1 = 0x7482;
  const static Taddress andMaskExpandAdjustAddress2 = 0x774D;
  
  // New value for the AND mask at the associated addresses
  const static Tbyte andMaskExpandAdjustValue[1];

  EditableStandardPalettes standardPalettes_;
  EditablePaletteCycles paletteCycles_;
  EditableLevelEffectsHeaders levelEffectsHeaders_;
  EditableLevelPaletteHeaders levelPaletteHeaders_;
  EditableLevelGraphicsData levelGraphicsData_;
  EditableLeafGraphicsTable leafGraphicsTable_;
  EditableWaterSplashGraphicTable waterSplashGraphicTable_;
  EditableSmokePuffGraphicTable smokePuffGraphicTable_;
  EditableSpriteMappings spriteMappings_;
  EditableMusicAssignments musicAssignments_;
  EditableRadioMusic radioMusic_;
  EditableEmeraldHealthRefills emeraldHealthRefills_;
  EditablePowerUpData powerUpData_;
  EditableMetatileWidthMaps metatileWidthMaps_;
  EditableMetatileHeightMaps metatileHeightMaps_;
  EditableSlopeSpeedValues slopeSpeedValues_;
  EditableMetatileBehaviors metatileBehaviors_;
  EditableSpawnPoints spawnPoints_;
  EditableWarpDestinations warpDestinations_;
  EditableLevelObjectEntryGroups levelObjectEntryGroups_;
  EditableMapData mapData_;
  
};


};


#endif
