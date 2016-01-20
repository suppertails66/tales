#ifndef TAILSADVADDRESSES_H
#define TAILSADVADDRESSES_H


namespace Tales {


/**
 * Collection of addresses to data that needs to be loaded from ROM.
 * All addresses are direct (i.e. not using Sega mapper banking format).
 */
class TailsAdvAddresses {
public:

  /**
  * Address of the graphics decompression substitution table.
  */
  const static int GraphicsDecSubstitutionTable = 0x00100;

  /**
  * Address of the level music table.
  */
  const static int LevelMusicTable              = 0x01635;

  /**
  * Address of the map effects table.
  */
  const static int MapEffectsTable              = 0x027BC;

  /**
  * Address of the map effects table content.
  */
  const static int MapEffectsTableContent       = 0x02842;

  /**
  * Address of one past the map effects table end.
  */
  const static int MapEffectsTableEnd           = 0x028A2;

  /**
  * Number of entries in the map effects table.
  */
  const static int NumMapEffectsTableEntries    = 24;

  /**
  * Address of the slope speed adjustment table.
  */
  const static int SlopeSpeedTable              = 0x03545;

  /**
  * Number of entries in the slope speed adjustment table.
  */
  const static int NumSlopeSpeedTableEntries    = 13;

  /**
  * Address of the radio music table.
  */
  const static int RadioMusicTable              = 0x03CB4;

  /**
  * Number of entries in the radio music table.
  */
  const static int NumRadioMusicTableEntries    = 13;

  /**
  * Address of the player spawn point table.
  */
  const static int TailsSpawnTable              = 0x04176;

  /**
  * Address of the player spawn point table content.
  */
  const static int TailsSpawnTableContent       = 0x041FE;

  /**
  * Number of entries in the player spawn point table.
  */
  const static int NumTailsSpawnTableEntries    = 83;

  /**
  * Address of one past the end of the player spawn point table content.
  */
  const static int TailsSpawnTableEnd           = 0x4496;

  /**
  * Address of the level header table.
  */
  const static int LevelHeaderTable             = 0x045B2;

  /**
  * Address of the level header table content.
  */
  const static int LevelHeaderTableContent      = 0x0468C;

  /**
  * Number of level headers in the level header table.
  */
  const static int LevelHeaderTableContentEntries = 51;

  /**
  * Address of the warp destination table.
  */
  const static int WarpDestinationTable         = 0x0634C;

  /**
  * Address of one past the end of the warp destination table content.
  */
  const static int WarpDestinationTableEnd      = 0x0654B;

  /**
  * Address of the object script routine table.
  */
  const static int ObjectScriptRoutineTable     = 0x066F5;

  /**
  * Address of the map graphics header table.
  */
  const static int MapGraphicsHeaderTable       = 0x077D9;

  /**
  * Address of the map graphics header table content.
  */
  const static int MapGraphicsHeaderTableContent = 0x07805;

  /**
  * Number of entries in the map graphics header table.
  */
  const static int NumMapGraphicsHeaderTableEntries = 47;

  /**
  * Address of the powerup table.
  */
  const static int PowerUpTable                 = 0x2CD70;

  /**
  * Address of the water splash graphic table.
  */
  const static int WaterSplashGraphicTable      = 0x33106;

  /**
  * Address of the emerald health refill table.
  */
  const static int EmeraldHealthRefillTable     = 0x353AB;

  /**
  * Address of the metatile behavior key lookup table.
  */
  const static int MetatileBehaviorTable        = 0x38000;

  /**
  * Address of the metatile behavior table.
  */
  const static int MetatileBehaviorTableContent = 0x38200;

  /**
  * Address of the height map table in memory.
  */
  const static int HeightMapTable               = 0x38900;
  
  /**
   * Number of height maps in the height map table.
   */
  const static int NumHeightMaps                = 35;

  /**
  * Address of the width map table in memory.
  */
  const static int WidthMapTable                = 0x38B30;
  
  /**
  * Address of the Tails graphic headers.
  */
  const static int TailsGraphicHeaders          = 0x38D70;
  
  /**
  * Number of Tails graphic headers.
  */
  const static int NumTailsGraphicHeaders = 131;
  
  /**
  * Address of the Remote Robot graphic headers.
  */
  const static int RemoteRobotGraphicHeaders  = 0x38F7C;
  
  /**
  * Number of Remote Robot graphic headers.
  */
  const static int NumRemoteRobotGraphicHeaders = 23;
  
  /**
   * Number of width maps in the width map table.
   */
  const static int NumWidthMaps                 = 35;

  /**
  * Address of the primary palette table.
  */
  const static int PaletteTable                 = 0x3928B;

  /**
  * Number of (standard) palettes in the primary table.
  */
  const static int NumPaletteTableEntries       = 42;

  /**
  * Address of the map#-palette# association table.
  */
  const static int MapPaletteNumTable           = 0x397CB;

  /**
  * Address of the map#-palette# association table content.
  */
  const static int MapPaletteNumTableContent    = 0x397F7;

  /**
  * Number of entries in the map#-palette# association table.
  */
  const static int NumMapPaletteNumTableEntries = 46;

  /**
  * Address of the map effects handler routine address table.
  */
  const static int MapEffectsHandlerTable       = 0x39881;
  
  /**
  * Address of the torch palette cycle effect.
  */
  const static int TorchPaletteCycle            = 0x39CAC;
  
  /**
  * Address of the Lake Rocky palette cycle effect.
  */
  const static int LakeRockyMainPaletteCycle    = 0x39CCC;
  
  /**
  * Address of the Lake Rocky top exit palette cycle effect.
  */
  const static int LakeRockyTopPaletteCycle1    = 0x39EDC;
  
  /**
  * Address of the Lake Rocky top exit palette cycle effect.
  */
  const static int LakeRockyTopPaletteCycle2    = 0x39EE4;
  
  /**
  * Address of the Lake Rocky bottom exit palette cycle effect.
  */
  const static int LakeRockyBottomPaletteCycle1 = 0x39EEC;
  
  /**
  * Address of the Lake Rocky bottom exit palette cycle effect.
  */
  const static int LakeRockyBottomPaletteCycle2 = 0x39F24;
  
  /**
  * Address of the Lake Rocky bottom exit palette cycle effect.
  */
  const static int LakeRockyBottomPaletteCycle3 = 0x39F58;
  
  /**
  * Address of the Cavern Island palette cycle effect.
  */
  const static int CavernIslandPaletteCycle     = 0x39F5C;
  
  /**
  * Address of the Poloy Forest palette cycle effect.
  */
  const static int PoloyForestPaletteCycle      = 0x39F6C;
  
  /**
  * Address of the second part of the Poloy Forest palette cycle effect.
  */
  const static int PoloyForestPaletteCyclePart2 = 0x39F72;
  
  /**
  * Address of the world map palette cycle effect.
  */
  const static int WorldMapPaletteCycle         = 0x39F7E;
  
  /**
  * Address of the sprite mappings table.
  */
  const static int SpriteMappingsTable          = 0x3C000;
  
  /**
  * Address of the uncompressed graphics headers.
  */
  const static int UncompressedGraphicsHeaders  = 0x3EB6F;
  
  /**
  * Number of uncompressed graphics headers.
  */
  const static int NumUncompressedGraphicsHeaders = 180;
  
  /**
  * Number of object entries in the sprite mappings table.
  */
  const static int NumSpriteMappingsTableObjects = 0x70;

  /**
  * Address of the metatile structure table.
  */
  const static int MetatileStructureTable       = 0x44000;

  /**
  * Address of the smoke puff graphic table.
  */
  const static int SmokePuffGraphicTable        = 0x65A6C;

  /**
  * Address of the leaf graphics table.
  */
  const static int LeafGraphicsTable            = 0x65EF7;

  /**
  * Address of the object layout table.
  */
  const static int ObjectLayoutTable            = 0x7054F;

  /**
  * Address of the object layout table content.
  */
  const static int ObjectLayoutTableContent     = 0x705C9;

  /**
  * Address of one past the end of the object layout table content.
  */
  const static int ObjectLayoutTableEnd         = 0x71FF3;

  /**
  * Number of entries in the object layout table.
  */
  const static int NumObjectLayoutTableEntries  = 42;
protected:
  
};


};


#endif 
