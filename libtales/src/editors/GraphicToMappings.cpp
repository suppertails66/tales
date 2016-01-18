#include "editors/GraphicToMappings.h"

namespace Tales {


int GraphicToMappings::numMappingsForGraphic(
                                   CompressionType compressionType,
                                   int index) {
  if (compressionType == GraphicToMappings::compressed) {
    // Anything with no mappings
    switch (index) {
    case 33:  // Polly Mt 2 fire wind
    case 57:  // (?) Tails House' interface
    case 58:  // (?) Remote Robot item
    case 63:  // Sega logo
    case 64:  // Debug font
    case 65:  // level graphics
    case 66:  // level graphics
    case 68:  // title screen
    case 69:  // level graphics
    case 70:  // level graphics
    case 71:  // level graphics
    case 72:  // level graphics
    case 73:  // level graphics
    case 74:  // level graphics
    case 75:  // level graphics
    case 76:  // level graphics
    case 77:  // level graphics
    case 78:  // level graphics
    case 79:  // level graphics
    case 80:  // level graphics
      return 0;
      break;
    default:
      break;
    }
    
    switch (index) {
    case 0x000: return cmpgrp000size; break;
    case 0x001: return cmpgrp001size; break;
    case 0x002: return cmpgrp002size; break;
    case 0x003: return cmpgrp003size; break;
    case 0x004: return cmpgrp004size; break;
    case 0x005: return cmpgrp005size; break;
    case 0x006: return cmpgrp006size; break;
    case 0x007: return cmpgrp007size; break;
    case 0x008: return cmpgrp008size; break;
    case 0x009: return cmpgrp009size; break;
    case 0x00A: return cmpgrp00Asize; break;
    case 0x00B: return cmpgrp00Bsize; break;
    case 0x00C: return cmpgrp00Csize; break;
    case 0x00D: return cmpgrp00Dsize; break;
    case 0x00E: return cmpgrp00Esize; break;
    case 0x00F: return cmpgrp00Fsize; break;
    case 0x010: return cmpgrp010size; break;
    case 0x011: return cmpgrp011size; break;
    case 0x012: return cmpgrp012size; break;
    case 0x013: return cmpgrp013size; break;
    case 0x014: return cmpgrp014size; break;
    case 0x015: return cmpgrp015size; break;
    case 0x016: return cmpgrp016size; break;
    case 0x017: return cmpgrp017size; break;
    case 0x018: return cmpgrp018size; break;
    case 0x019: return cmpgrp019size; break;
    case 0x01A: return cmpgrp01Asize; break;
    case 0x01B: return cmpgrp01Bsize; break;
    case 0x01C: return cmpgrp01Csize; break;
    case 0x01D: return cmpgrp01Dsize; break;
    case 0x01E: return cmpgrp01Esize; break;
    case 0x01F: return cmpgrp01Fsize; break;
    case 0x020: return cmpgrp020size; break;
  //  case 0x021: return cmpgrp021size; break;
    case 0x022: return cmpgrp022size; break;
    case 0x023: return cmpgrp023size; break;
    case 0x024: return cmpgrp024size; break;
    case 0x025: return cmpgrp025size; break;
    case 0x026: return cmpgrp026size; break;
    case 0x027: return cmpgrp027size; break;
    case 0x028: return cmpgrp028size; break;
    case 0x029: return cmpgrp029size; break;
    case 0x02A: return cmpgrp02Asize; break;
    case 0x02B: return cmpgrp02Bsize; break;
    case 0x02C: return cmpgrp02Csize; break;
    case 0x02D: return cmpgrp02Dsize; break;
    case 0x02E: return cmpgrp02Esize; break;
    case 0x02F: return cmpgrp02Fsize; break;
    case 0x030: return cmpgrp030size; break;
    case 0x031: return cmpgrp031size; break;
    case 0x032: return cmpgrp032size; break;
    case 0x033: return cmpgrp033size; break;
    case 0x034: return cmpgrp034size; break;
    case 0x035: return cmpgrp035size; break;
    case 0x036: return cmpgrp036size; break;
    case 0x037: return cmpgrp037size; break;
    case 0x038: return cmpgrp038size; break;
  //  case 0x039: return cmpgrp039size; break;
  //  case 0x03A: return cmpgrp03Asize; break;
    case 0x03B: return cmpgrp03Bsize; break;
    case 0x03C: return cmpgrp03Csize; break;
    case 0x03D: return cmpgrp03Dsize; break;
    case 0x03E: return cmpgrp03Esize; break;
    default:
      return -1;
      break;
    }
  }
  else {
    // Anything with no mappings
    switch (index) {
    case 157:  // flight meter
    case 158:  // flight meter
    case 159:  // flight meter
    case 160:  // flight meter
    case 161:  // flight meter
    case 162:  // flight meter
    case 163:  // flight meter
    case 164:  // flight meter
    case 165:  // flight meter
    case 166:  // flight meter
    case 167:  // flight meter
    case 168:  // flight meter
    case 169:  // flight meter
    case 226:  // lake crystal graphic cycle
    case 227:  // lake crystal graphic cycle
    case 228:  // lake crystal graphic cycle
    case 229:  // lake crystal graphic cycle
    case 230:  // conveyor graphic cycle
    case 231:  // conveyor graphic cycle
    case 271:  // ?
    case 272:  // ?
      return 0;
      break;
    default:
      break;
    }
    
    // Anything with more than one mapping
    switch (index) {
    case 154: return 2; break; // torpedo
    case 156: return 2; break; // vulcan cannon
    case 200: return 2; break; // bomb
    case 201: return 5; break; // napalm bomb
    case 202: return 3; break; // anti-air missile
    case 203: return 3; break; // hammer
    case 217: return 13; break; // final boss
    case 218: return 2; break; // (?) final boss bombs
    case 219: return 32; break; // extra armor
    case 274: return 12; break; // (?) Remote Robot transform
    default:
      break;
    }
    
    // Everything else has one mapping
    return 1;
  }
}
  
GraphicToMappingEntry GraphicToMappings::graphicMapping(
                                   CompressionType compressionType,
                                   int graphicIndex,
                                   int mappingIndex) {
  if (compressionType == GraphicToMappings::compressed) {
    return compressedGraphicMapping(graphicIndex, mappingIndex);
  }
  else {
    // Tails
    if (graphicIndex < 0x084) {
      return GraphicToMappingEntry(graphicIndex, 0x00, "Frame 1");
    }
    // Remote Robot
    else if (graphicIndex < 0x09A) {
      return GraphicToMappingEntry(graphicIndex, -0x0A, "Frame 1");
    }
    // Proton torpedo
    else if (graphicIndex <= 0x09A) {
      switch (mappingIndex) {
      case 0:
        return GraphicToMappingEntry(0x0E5, 0, "Frame 1");
      case 1:
        return GraphicToMappingEntry(0x0E6, 0, "Frame 2");
      default:
        break;
      }
    }
    // Mine weapon
    else if (graphicIndex <= 0x09B) {
      return GraphicToMappingEntry(0x0EC, 0, "Frame 1");
    }
    // Vulcan cannon
    else if (graphicIndex <= 0x09C) {
      switch (mappingIndex) {
      case 0:
        return GraphicToMappingEntry(0x0E7, 0, "Frame 1");
      case 1:
        return GraphicToMappingEntry(0x0E8, 0, "Frame 2");
      default:
        break;
      }
    }
    // Inventory items
    else if (graphicIndex < 0x0C8) {
      return GraphicToMappingEntry(0x0ED, 0, "");
    }
    // Bomb
    else if (graphicIndex <= 0x0C8) {
      return GraphicToMappingEntry(0x0D8 + mappingIndex, 0, "");
    }
    // Napalm bomb
    else if (graphicIndex <= 0x0C9) {
      return GraphicToMappingEntry(0x0DA + mappingIndex, 0, "");
    }
    // Anti-air missile
    else if (graphicIndex <= 0x0CA) {
      return GraphicToMappingEntry(0x0E9 + mappingIndex, 0, "");
    }
    // Hammer
    else if (graphicIndex <= 0x0CB) {
      return GraphicToMappingEntry(0x0DF + mappingIndex, 0, "");
    }
    // Title cards JP
    else if (graphicIndex < 0x0D9) {
      return GraphicToMappingEntry(0x15D, 0, "");
    }
    // Final boss
    else if (graphicIndex <= 0x0D9) {
      return GraphicToMappingEntry(0x1DD + mappingIndex, 0, "");
    }
    // Final boss bombs
    else if (graphicIndex <= 0x0DA) {
      return GraphicToMappingEntry(0x140 + mappingIndex, 0, "");
    }
    // Extra Armor stars
    else if (graphicIndex <= 0x0DB) {
      return GraphicToMappingEntry(mappingIndex + 0x09A, -0x4A, "Frame 1");
    }
    // Chaos emerald pickups
    else if (graphicIndex < 0x0E2) {
      return GraphicToMappingEntry(0x0ED, 0, "");
    }
    // Item pickup labels JP
    else if (graphicIndex < 0x102) {
      return GraphicToMappingEntry(0x0BA, -0x5E, "");
    }
    // Title cards EN
    else if (graphicIndex < 0x10F) {
      return GraphicToMappingEntry(0x15D, 0, "");
    }
    // ?
    else if (graphicIndex <= 0x10F) {
      return GraphicToMappingEntry(0x15D, 0, "");
    }
    // ?
    else if (graphicIndex <= 0x110) {
      return GraphicToMappingEntry(0x15D, 0, "");
    }
    // Item pickup labels EN
    else if (graphicIndex < 0x12B) {
      return GraphicToMappingEntry(0x0BA, -0x5E, "");
    }
  }
}

GraphicToMappingEntry GraphicToMappings::compressedGraphicMapping(
    int graphicIndex,
    int mappingIndex) {
  const GraphicToMappingEntry* target;
  switch (graphicIndex) {
  case 0x000: target = cmpgrp000maps; break;
  case 0x001: target = cmpgrp001maps; break;
  case 0x002: target = cmpgrp002maps; break;
  case 0x003: target = cmpgrp003maps; break;
  case 0x004: target = cmpgrp004maps; break;
  case 0x005: target = cmpgrp005maps; break;
  case 0x006: target = cmpgrp006maps; break;
  case 0x007: target = cmpgrp007maps; break;
  case 0x008: target = cmpgrp008maps; break;
  case 0x009: target = cmpgrp009maps; break;
  case 0x00A: target = cmpgrp00Amaps; break;
  case 0x00B: target = cmpgrp00Bmaps; break;
  case 0x00C: target = cmpgrp00Cmaps; break;
  case 0x00D: target = cmpgrp00Dmaps; break;
  case 0x00E: target = cmpgrp00Emaps; break;
  case 0x00F: target = cmpgrp00Fmaps; break;
  case 0x010: target = cmpgrp010maps; break;
  case 0x011: target = cmpgrp011maps; break;
  case 0x012: target = cmpgrp012maps; break;
  case 0x013: target = cmpgrp013maps; break;
  case 0x014: target = cmpgrp014maps; break;
  case 0x015: target = cmpgrp015maps; break;
  case 0x016: target = cmpgrp016maps; break;
  case 0x017: target = cmpgrp017maps; break;
  case 0x018: target = cmpgrp018maps; break;
  case 0x019: target = cmpgrp019maps; break;
  case 0x01A: target = cmpgrp01Amaps; break;
  case 0x01B: target = cmpgrp01Bmaps; break;
  case 0x01C: target = cmpgrp01Cmaps; break;
  case 0x01D: target = cmpgrp01Dmaps; break;
  case 0x01E: target = cmpgrp01Emaps; break;
  case 0x01F: target = cmpgrp01Fmaps; break;
  case 0x020: target = cmpgrp020maps; break;
//  case 0x021: target = cmpgrp021maps; break;
  case 0x022: target = cmpgrp022maps; break;
  case 0x023: target = cmpgrp023maps; break;
  case 0x024: target = cmpgrp024maps; break;
  case 0x025: target = cmpgrp025maps; break;
  case 0x026: target = cmpgrp026maps; break;
  case 0x027: target = cmpgrp027maps; break;
  case 0x028: target = cmpgrp028maps; break;
  case 0x029: target = cmpgrp029maps; break;
  case 0x02A: target = cmpgrp02Amaps; break;
  case 0x02B: target = cmpgrp02Bmaps; break;
  case 0x02C: target = cmpgrp02Cmaps; break;
  case 0x02D: target = cmpgrp02Dmaps; break;
  case 0x02E: target = cmpgrp02Emaps; break;
  case 0x02F: target = cmpgrp02Fmaps; break;
  case 0x030: target = cmpgrp030maps; break;
  case 0x031: target = cmpgrp031maps; break;
  case 0x032: target = cmpgrp032maps; break;
  case 0x033: target = cmpgrp033maps; break;
  case 0x034: target = cmpgrp034maps; break;
  case 0x035: target = cmpgrp035maps; break;
  case 0x036: target = cmpgrp036maps; break;
  case 0x037: target = cmpgrp037maps; break;
  case 0x038: target = cmpgrp038maps; break;
//  case 0x039: target = cmpgrp039maps; break;
//  case 0x03A: target = cmpgrp03Amaps; break;
  case 0x03B: target = cmpgrp03Bmaps; break;
  case 0x03C: target = cmpgrp03Cmaps; break;
  case 0x03D: target = cmpgrp03Dmaps; break;
  case 0x03E: target = cmpgrp03Emaps; break;
  default:
    return GraphicToMappingEntry(-1, -1, "***INVALID GRAPHIC INDEX***");
    break;
  }
  
  return target[mappingIndex];
}

// HUD
const GraphicToMappingEntry GraphicToMappings::cmpgrp000maps[
    cmpgrp000size] =
  {
    // Ring
    GraphicToMappingEntry(0x0BB, -0x12, "Ring 1"),
    GraphicToMappingEntry(0x0BC, -0x12, "Ring 2"),
    GraphicToMappingEntry(0x0BD, -0x12, "Ring 3"),
    GraphicToMappingEntry(0x0BE, -0x12, "Ring 4"),
    // Explosion
    GraphicToMappingEntry(0x0D4, -0x12, "Explosion 1"),
    GraphicToMappingEntry(0x0D5, -0x12, "Explosion 2"),
    GraphicToMappingEntry(0x0D6, -0x12, "Explosion 3"),
    GraphicToMappingEntry(0x0D7, -0x12, "Explosion 4"),
  };

// Compressed bomb (possibly not used?)
const GraphicToMappingEntry GraphicToMappings::cmpgrp001maps[
    cmpgrp001size] =
  {
    GraphicToMappingEntry(0x0D8, 0, "Frame 1"),
    GraphicToMappingEntry(0x0D9, 0, "Frame 2")
  };

// Compressed item pickup
const GraphicToMappingEntry GraphicToMappings::cmpgrp002maps[
    cmpgrp002size] =
  {
    GraphicToMappingEntry(0x0ED, 0, "Frame 1"),
    GraphicToMappingEntry(0x0EE, -0xFC, "Frame 2") // ?
  };

// Flying mech duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp003maps[
    cmpgrp003size] =
  {
    GraphicToMappingEntry(0x0EF, 0, "Frame 1"),
    GraphicToMappingEntry(0x0F0, 0, "Frame 2"),
    GraphicToMappingEntry(0x0F1, 0, "Frame 3"),
    GraphicToMappingEntry(0x0F2, 0, "Frame 4"),
    GraphicToMappingEntry(0x0F3, 0, "Frame 5"),
    GraphicToMappingEntry(0x0F4, 0, "Frame 6"),
    GraphicToMappingEntry(0x0F5, 0, "Frame 7")
  };

// Walking mech duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp004maps[
    cmpgrp004size] =
  {
    GraphicToMappingEntry(0x0F6, 0, "Frame 1"),
    GraphicToMappingEntry(0x0F7, 0, "Frame 2"),
    GraphicToMappingEntry(0x0F8, 0, "Frame 3")
  };

// Bomber mouse
const GraphicToMappingEntry GraphicToMappings::cmpgrp005maps[
    cmpgrp005size] =
  {
    GraphicToMappingEntry(0x0FA, 0, "Frame 1"),
    GraphicToMappingEntry(0x0FB, 0, "Frame 2"),
    GraphicToMappingEntry(0x0FC, 0, "Frame 3"),
    GraphicToMappingEntry(0x0FD, 0, "Frame 3")
  };

// Fixed-position gun
const GraphicToMappingEntry GraphicToMappings::cmpgrp006maps[
    cmpgrp006size] =
  {
    GraphicToMappingEntry(0x0FE, 0, "Frame 1"),
    GraphicToMappingEntry(0x0FF, 0, "Frame 2"),
    GraphicToMappingEntry(0x100, 0, "Frame 3")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp007maps[
    cmpgrp007size] =
  {
    GraphicToMappingEntry(0x101, 0, "Frame 1"),
    GraphicToMappingEntry(0x102, 0, "Frame 2"),
    GraphicToMappingEntry(0x103, 0, "Frame 3")
  };

// Drill robot
const GraphicToMappingEntry GraphicToMappings::cmpgrp008maps[
    cmpgrp008size] =
  {
    GraphicToMappingEntry(0x104, 0, "Frame 1"),
    GraphicToMappingEntry(0x105, 0, "Frame 2")
  };

// Flying bat
const GraphicToMappingEntry GraphicToMappings::cmpgrp009maps[
    cmpgrp009size] =
  {
    GraphicToMappingEntry(0x15B, 0, "Frame 1"),
    GraphicToMappingEntry(0x15C, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Amaps[
    cmpgrp00Asize] =
  {
    GraphicToMappingEntry(0x187, 0, "Frame 1"),
    GraphicToMappingEntry(0x188, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Bmaps[
    cmpgrp00Bsize] =
  {
    GraphicToMappingEntry(0x106, 0, "Frame 1"),
    GraphicToMappingEntry(0x107, 0, "Frame 2"),
    GraphicToMappingEntry(0x108, 0, "Frame 3"),
    GraphicToMappingEntry(0x109, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Cmaps[
    cmpgrp00Csize] =
  {
    GraphicToMappingEntry(0x10A, 0, "Frame 1"),
    GraphicToMappingEntry(0x10B, 0, "Frame 2"),
    GraphicToMappingEntry(0x10C, 0, "Frame 3"),
    GraphicToMappingEntry(0x10D, 0, "Frame 4"),
    GraphicToMappingEntry(0x10E, 0, "Frame 5"),
    GraphicToMappingEntry(0x10F, 0, "Frame 6")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Dmaps[
    cmpgrp00Dsize] =
  {
    GraphicToMappingEntry(0x11E, 0, "Frame 1"),
    GraphicToMappingEntry(0x11F, 0, "Frame 2"),
    GraphicToMappingEntry(0x120, 0, "Frame 3")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Emaps[
    cmpgrp00Esize] =
  {
    GraphicToMappingEntry(0x121, 0, "Frame 1"),
    GraphicToMappingEntry(0x122, 0, "Frame 2"),
    GraphicToMappingEntry(0x123, 0, "Frame 3")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp00Fmaps[
    cmpgrp00Fsize] =
  {
    GraphicToMappingEntry(0x124, 0, "Frame 1"),
    GraphicToMappingEntry(0x125, 0, "Frame 2"),
    GraphicToMappingEntry(0x126, 0, "Frame 3"),
    GraphicToMappingEntry(0x127, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp010maps[
    cmpgrp010size] =
  {
    GraphicToMappingEntry(0x133, 0, "Frame 1"),
    GraphicToMappingEntry(0x134, 0, "Frame 2"),
    GraphicToMappingEntry(0x135, 0, "Frame 3"),
    GraphicToMappingEntry(0x136, 0, "Frame 4"),
    GraphicToMappingEntry(0x137, 0, "Frame 5")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp011maps[
    cmpgrp011size] =
  {
    GraphicToMappingEntry(0x138, 0, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp012maps[
    cmpgrp012size] =
  {
    GraphicToMappingEntry(0x139, 0, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp013maps[
    cmpgrp013size] =
  {
    GraphicToMappingEntry(0x13A, 0, "Frame 1"),
    GraphicToMappingEntry(0x13B, 0, "Frame 2"),
    GraphicToMappingEntry(0x13C, 0, "Frame 3"),
    GraphicToMappingEntry(0x13D, 0, "Frame 4"),
    GraphicToMappingEntry(0x13E, 0, "Frame 5"),
    GraphicToMappingEntry(0x13F, 0, "Frame 6")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp014maps[
    cmpgrp014size] =
  {
    GraphicToMappingEntry(0x142, 0, "Frame 1"),
    GraphicToMappingEntry(0x143, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp015maps[
    cmpgrp015size] =
  {
    GraphicToMappingEntry(0x11A, 0, "Frame 1"),
    GraphicToMappingEntry(0x11B, 0, "Frame 2"),
    GraphicToMappingEntry(0x11C, 0, "Frame 3"),
    GraphicToMappingEntry(0x11D, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp016maps[
    cmpgrp016size] =
  {
    GraphicToMappingEntry(0x159, 0, "Frame 1"),
    GraphicToMappingEntry(0x15A, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp017maps[
    cmpgrp017size] =
  {
    GraphicToMappingEntry(0x14B, 0, "Frame 1"),
    GraphicToMappingEntry(0x14C, 0, "Frame 2"),
    GraphicToMappingEntry(0x14D, 0, "Frame 3")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp018maps[
    cmpgrp018size] =
  {
    GraphicToMappingEntry(0x140, 0, "Frame 1"),
    GraphicToMappingEntry(0x141, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp019maps[
    cmpgrp019size] =
  {
    GraphicToMappingEntry(0x144, 0, "Frame 1"),
    GraphicToMappingEntry(0x145, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Amaps[
    cmpgrp01Asize] =
  {
    GraphicToMappingEntry(0x0C0, 0, "Frame 1"),
    GraphicToMappingEntry(0x0C1, 0, "Frame 2"),
    GraphicToMappingEntry(0x0C2, 0, "Frame 3"),
    GraphicToMappingEntry(0x0C3, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Bmaps[
    cmpgrp01Bsize] =
  {
    GraphicToMappingEntry(0x14E, 0, "Frame 1"),
    GraphicToMappingEntry(0x14F, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Cmaps[
    cmpgrp01Csize] =
  {
    GraphicToMappingEntry(0x150, 0, "Frame 1"),
    GraphicToMappingEntry(0x151, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Dmaps[
    cmpgrp01Dsize] =
  {
    GraphicToMappingEntry(0x152, 0, "Frame 1"),
    GraphicToMappingEntry(0x153, 0, "Frame 2"),
    GraphicToMappingEntry(0x154, 0, "Frame 3"),
    GraphicToMappingEntry(0x155, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Emaps[
    cmpgrp01Esize] =
  {
    GraphicToMappingEntry(0x156, 0, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp01Fmaps[
    cmpgrp01Fsize] =
  {
    GraphicToMappingEntry(0x110, 0, "Frame 1"),
    GraphicToMappingEntry(0x111, 0, "Frame 2"),
    GraphicToMappingEntry(0x112, 0, "Frame 3"),
    GraphicToMappingEntry(0x113, 0, "Frame 4"),
    GraphicToMappingEntry(0x114, 0, "Frame 5"),
    GraphicToMappingEntry(0x115, 0, "Frame 6"),
    GraphicToMappingEntry(0x116, 0, "Frame 7"),
    GraphicToMappingEntry(0x117, 0, "Frame 8"),
    GraphicToMappingEntry(0x118, 0, "Frame 9"),
    GraphicToMappingEntry(0x119, 0, "Frame 10")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp020maps[
    cmpgrp020size] =
  {
    GraphicToMappingEntry(0x146, 0, "Frame 1"),
    GraphicToMappingEntry(0x147, 0, "Frame 2"),
    GraphicToMappingEntry(0x148, 0, "Frame 3"),
    GraphicToMappingEntry(0x149, 0, "Frame 4"),
    GraphicToMappingEntry(0x14A, 0, "Frame 5")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp022maps[
    cmpgrp022size] =
  {
    GraphicToMappingEntry(0x16A, 0, "Frame 1"),
    GraphicToMappingEntry(0x16B, 0, "Frame 2"),
    GraphicToMappingEntry(0x16C, 0, "Frame 3"),
    GraphicToMappingEntry(0x16D, 0, "Frame 4"),
    GraphicToMappingEntry(0x16E, 0, "Frame 5"),
    GraphicToMappingEntry(0x16F, 0, "Frame 6"),
    GraphicToMappingEntry(0x170, 0, "Frame 7"),
    GraphicToMappingEntry(0x171, 0, "Frame 8"),
    GraphicToMappingEntry(0x172, 0, "Frame 9"),
    GraphicToMappingEntry(0x173, 0, "Frame 10"),
    GraphicToMappingEntry(0x174, 0, "Frame 11"),
    GraphicToMappingEntry(0x175, 0, "Frame 12"),
    GraphicToMappingEntry(0x176, 1, "Frame 13"),
    GraphicToMappingEntry(0x177, 1, "Frame 14"),
    GraphicToMappingEntry(0x178, 0, "Frame 15"),
    GraphicToMappingEntry(0x179, 0, "Frame 16"),
    GraphicToMappingEntry(0x17A, 0, "Frame 17"),
    GraphicToMappingEntry(0x17B, 0, "Frame 18"),
    GraphicToMappingEntry(0x17C, 0, "Frame 19"),
    GraphicToMappingEntry(0x17D, 0, "Frame 20"),
    GraphicToMappingEntry(0x17E, 0, "Frame 21"),
    GraphicToMappingEntry(0x17F, 0, "Frame 22"),
    GraphicToMappingEntry(0x180, 0, "Frame 23"),
    GraphicToMappingEntry(0x181, 0, "Frame 24"),
    GraphicToMappingEntry(0x182, 0, "Frame 25")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp023maps[
    cmpgrp023size] =
  {
    GraphicToMappingEntry(0x157, 0, "Frame 1"),
    GraphicToMappingEntry(0x158, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp024maps[
    cmpgrp024size] =
  {
    GraphicToMappingEntry(0x0C4, 0, "Frame 1"),
    GraphicToMappingEntry(0x0C5, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp025maps[
    cmpgrp025size] =
  {
    GraphicToMappingEntry(0x0F9, 0, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp026maps[
    cmpgrp026size] =
  {
    GraphicToMappingEntry(0x183, 0, "Frame 1"),
    GraphicToMappingEntry(0x184, 0, "Frame 2"),
    GraphicToMappingEntry(0x185, 0, "Frame 3"),
    GraphicToMappingEntry(0x186, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp027maps[
    cmpgrp027size] =
  {
    GraphicToMappingEntry(0x128, 0, "Frame 1"),
    GraphicToMappingEntry(0x129, 0, "Frame 2"),
    GraphicToMappingEntry(0x12A, 0, "Frame 3"),
    GraphicToMappingEntry(0x12B, 0, "Frame 4"),
    GraphicToMappingEntry(0x12C, 0, "Frame 5"),
    GraphicToMappingEntry(0x12D, 0, "Frame 6"),
    GraphicToMappingEntry(0x12E, 0, "Frame 7"),
    GraphicToMappingEntry(0x12F, 0, "Frame 8"),
    GraphicToMappingEntry(0x130, 0, "Frame 9"),
    GraphicToMappingEntry(0x131, 0, "Frame 10"),
    GraphicToMappingEntry(0x132, 0, "Frame 11")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp028maps[
    cmpgrp028size] =
  {
    GraphicToMappingEntry(0x128, 0, "Frame 1"),
    GraphicToMappingEntry(0x129, 0, "Frame 2"),
    GraphicToMappingEntry(0x12A, 0, "Frame 3"),
    GraphicToMappingEntry(0x12B, 0, "Frame 4"),
    GraphicToMappingEntry(0x12C, 0, "Frame 5"),
    GraphicToMappingEntry(0x12D, 0, "Frame 6"),
    GraphicToMappingEntry(0x12E, 0, "Frame 7"),
    GraphicToMappingEntry(0x12F, 0, "Frame 8")
//    GraphicToMappingEntry(0x130, 0, "Frame 9"),
//    GraphicToMappingEntry(0x131, 0, "Frame 9"),
//    GraphicToMappingEntry(0x132, 0, "Frame 11")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp029maps[
    cmpgrp029size] =
  {
    GraphicToMappingEntry(0x189, 0, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Amaps[
    cmpgrp02Asize] =
  {
    GraphicToMappingEntry(0x18A, 0, "Frame 1"),
    GraphicToMappingEntry(0x18B, 0, "Frame 2"),
    GraphicToMappingEntry(0x18C, 0, "Frame 3"),
    GraphicToMappingEntry(0x18D, 0, "Frame 4"),
    GraphicToMappingEntry(0x18E, 0, "Frame 5"),
    GraphicToMappingEntry(0x18F, 0, "Frame 6"),
    GraphicToMappingEntry(0x190, 0, "Frame 7"),
    GraphicToMappingEntry(0x191, 0, "Frame 8"),
    GraphicToMappingEntry(0x192, 0, "Frame 9"),
    GraphicToMappingEntry(0x193, 0, "Frame 10"),
    GraphicToMappingEntry(0x194, 0, "Frame 11"),
    GraphicToMappingEntry(0x195, 0, "Frame 12"),
    GraphicToMappingEntry(0x196, 0, "Frame 13"),
    GraphicToMappingEntry(0x197, 0, "Frame 14"),
    GraphicToMappingEntry(0x198, 0, "Frame 15"),
    GraphicToMappingEntry(0x199, 0, "Frame 16")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Bmaps[
    cmpgrp02Bsize] =
  {
    GraphicToMappingEntry(0x1BB, 0, "Frame 1"),
    GraphicToMappingEntry(0x1BC, 0, "Frame 2"),
    GraphicToMappingEntry(0x1BD, 0, "Frame 3"),
    GraphicToMappingEntry(0x1BE, 0, "Frame 4"),
    GraphicToMappingEntry(0x1BF, 0, "Frame 5"),
    GraphicToMappingEntry(0x1C0, 0, "Frame 6"),
    GraphicToMappingEntry(0x1C1, 0, "Frame 7"),
    GraphicToMappingEntry(0x1C2, 0, "Frame 8"),
    GraphicToMappingEntry(0x1C3, 0, "Frame 9"),
    GraphicToMappingEntry(0x1C4, 0, "Frame 10")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Cmaps[
    cmpgrp02Csize] =
  {
    GraphicToMappingEntry(0x1C5, 0, "Frame 1"),
    GraphicToMappingEntry(0x1C6, 0, "Frame 2"),
    GraphicToMappingEntry(0x1C7, 0, "Frame 3"),
    GraphicToMappingEntry(0x1C8, 0, "Frame 4"),
    GraphicToMappingEntry(0x1C9, 0, "Frame 5"),
    GraphicToMappingEntry(0x1CA, 0, "Frame 6"),
    GraphicToMappingEntry(0x1CB, 0, "Frame 7"),
    GraphicToMappingEntry(0x1CC, 0, "Frame 8"),
    GraphicToMappingEntry(0x1CD, 0, "Frame 9"),
    GraphicToMappingEntry(0x1CE, 0, "Frame 10")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Dmaps[
    cmpgrp02Dsize] =
  {
    GraphicToMappingEntry(0x0C6, 0, "Frame 1"),
    GraphicToMappingEntry(0x0C7, 0, "Frame 2"),
    GraphicToMappingEntry(0x0C8, 0, "Frame 3"),
    GraphicToMappingEntry(0x0C9, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Emaps[
    cmpgrp02Esize] =
  {
    GraphicToMappingEntry(0x0CA, -0x10, "Frame 1"),
    GraphicToMappingEntry(0x0CB, -0x10, "Frame 2"),
    GraphicToMappingEntry(0x0CC, -0x10, "Frame 3"),
    GraphicToMappingEntry(0x0CD, -0x10, "Frame 4"),
    GraphicToMappingEntry(0x0CE, -0x10, "Frame 5"),
    GraphicToMappingEntry(0x0CF, -0x10, "Frame 6"),
    GraphicToMappingEntry(0x0D0, -0x10, "Frame 7"),
    GraphicToMappingEntry(0x0D1, -0x10, "Frame 8")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp02Fmaps[
    cmpgrp02Fsize] =
  {
    GraphicToMappingEntry(0x1EA, 0, "Frame 1"),
    GraphicToMappingEntry(0x1EB, 0, "Frame 2"),
    GraphicToMappingEntry(0x1EC, 0, "Frame 3"),
    GraphicToMappingEntry(0x1ED, 0, "Frame 4")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp030maps[
    cmpgrp030size] =
  {
    GraphicToMappingEntry(0x1EE, -0x10, "Frame 1"),
    GraphicToMappingEntry(0x1EF, -0x10, "Frame 2"),
    GraphicToMappingEntry(0x1F0, -0x10, "Frame 3")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp031maps[
    cmpgrp031size] =
  {
/*    GraphicToMappingEntry(0x1F1, -0x10, "Frame 1"),
    GraphicToMappingEntry(0x1F2, -0x10, "Frame 2"),
    GraphicToMappingEntry(0x1F3, -0x10, "Frame 3"),
    GraphicToMappingEntry(0x1F4, -0x10, "Frame 4"),
    GraphicToMappingEntry(0x1F5, -0x10, "Frame 5") */
    GraphicToMappingEntry(0x1F1, 0, "Frame 1"),
    GraphicToMappingEntry(0x1F2, 0, "Frame 2"),
    GraphicToMappingEntry(0x1F3, 0, "Frame 3"),
    GraphicToMappingEntry(0x1F4, 0, "Frame 4"),
    GraphicToMappingEntry(0x1F5, 0, "Frame 5")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp032maps[
    cmpgrp032size] =
  {
    GraphicToMappingEntry(0x1B1, -0x36, "Frame 1"),
    GraphicToMappingEntry(0x1B2, -0x36, "Frame 2"),
    GraphicToMappingEntry(0x1B3, -0x36, "Frame 3"),
    GraphicToMappingEntry(0x1B4, -0x36, "Frame 4"),
    GraphicToMappingEntry(0x1B5, -0x36, "Frame 5")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp033maps[
    cmpgrp033size] =
  {
    GraphicToMappingEntry(0x1A9, 0, "Frame 1"),
    GraphicToMappingEntry(0x1AA, 0, "Frame 2"),
    GraphicToMappingEntry(0x1AB, 0, "Frame 3"),
    GraphicToMappingEntry(0x1AC, 0, "Frame 4"),
    GraphicToMappingEntry(0x1AD, 0, "Frame 5"),
    GraphicToMappingEntry(0x1AE, 0, "Frame 6"),
    GraphicToMappingEntry(0x1AF, 0, "Frame 7"),
    GraphicToMappingEntry(0x1B0, 0, "Frame 8")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp034maps[
    cmpgrp034size] =
  {
    GraphicToMappingEntry(0x1A2, -0x36, "Frame 1"),
    GraphicToMappingEntry(0x1A3, -0x36, "Frame 2"),
    GraphicToMappingEntry(0x1A4, -0x36, "Frame 3"),
    GraphicToMappingEntry(0x1A5, -0x36, "Frame 4"),
    GraphicToMappingEntry(0x1A6, -0x36, "Frame 5"),
    GraphicToMappingEntry(0x1A7, -0x36, "Frame 6"),
    GraphicToMappingEntry(0x1A8, -0x36, "Frame 7")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp035maps[
    cmpgrp035size] =
  {
    GraphicToMappingEntry(0x1B6, 0, "Frame 1"),
    GraphicToMappingEntry(0x1B7, 0, "Frame 2"),
    GraphicToMappingEntry(0x1B8, 0, "Frame 3"),
    GraphicToMappingEntry(0x1B9, 0, "Frame 4"),
    GraphicToMappingEntry(0x1BA, 0, "Frame 5")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp036maps[
    cmpgrp036size] =
  {
    GraphicToMappingEntry(0x1CF, 0, "Frame 1"),
    GraphicToMappingEntry(0x1D0, 0, "Frame 2"),
    GraphicToMappingEntry(0x1D1, 0, "Frame 3"),
    GraphicToMappingEntry(0x1D2, 0, "Frame 4"),
    GraphicToMappingEntry(0x1D3, 0, "Frame 5"),
    GraphicToMappingEntry(0x1D4, 0, "Frame 6"),
    GraphicToMappingEntry(0x1D5, 0, "Frame 7"),
    GraphicToMappingEntry(0x1D6, 0, "Frame 8"),
    GraphicToMappingEntry(0x1D7, 0, "Frame 9"),
    GraphicToMappingEntry(0x1D8, 0, "Frame 10"),
    GraphicToMappingEntry(0x1D9, 0, "Frame 11"),
    GraphicToMappingEntry(0x1DA, 0, "Frame 12"),
    GraphicToMappingEntry(0x1DB, 0, "Frame 13"),
    GraphicToMappingEntry(0x1DC, 0, "Frame 14")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp037maps[
    cmpgrp037size] =
  {
    GraphicToMappingEntry(0x0D2, 0, "Frame 1"),
    GraphicToMappingEntry(0x0D3, 0, "Frame 2")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp038maps[
    cmpgrp038size] =
  {
    GraphicToMappingEntry(0x0ED, 0, "Frame 1"),
    GraphicToMappingEntry(0x0EE, -0xFC, "?")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp03Bmaps[
    cmpgrp03Bsize] =
  {
    GraphicToMappingEntry(0x0BF, -0x5A, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp03Cmaps[
    cmpgrp03Csize] =
  {
    GraphicToMappingEntry(0x0BF, -0x5A, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp03Dmaps[
    cmpgrp03Dsize] =
  {
    GraphicToMappingEntry(0x0BF, -0x5A, "Frame 1")
  };

// Crouching duck
const GraphicToMappingEntry GraphicToMappings::cmpgrp03Emaps[
    cmpgrp03Esize] =
  {
    GraphicToMappingEntry(0x0BF, -0x5A, "Frame 1")
  };


};
