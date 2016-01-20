#include "gamedata/SubMaps.h"
#include "gamedata/PrimaryMaps.h"

namespace Tales {


const int SubMaps::subMapCounts[SubMaps::subMapCountsSize]
 = { 
   0,		// 0x00: null, headers point to poloy 1
	 3,		// 0x01: poloy forest
	 2,		// 0x02: caron forest
	 3, 	// 0x03: volcanic tunnel
	 4, 	// 0x04: polly mtn 1
	 2, 	// 0x05: polly mtn 2
	 9, 	// 0x06: lake rocky
	 2, 	// 0x07: lake crystal
	 2, 	// 0x08: green island
	 3, 	// 0x09: cavern island
	 3, 	// 0x0A: coco island
	 2, 	// 0x0B: battle fortress flight
	 3, 	// 0x0C: battle fortress
	 0, 	// 0x0D: null, headers point to poloy 1
	 0, 	// 0x0E: null, headers point to poloy 1
	 0, 	// 0x0F: null, headers point to poloy 1
	 1, 	// 0x10: world map
	 0, 	// 0x11: tails' house
	 0, 	// 0x12: null? primary map header points to intro forest
	 2,		// 0x13: intro forest
	 2,		// 0x14: leave dock cutscene
	 1,		// 0x15: return to dock cutscene
//	 0		// 0x16: another dock cutscene? headers point to poloy1
 };

const int SubMaps::subMapFixedGraphicTableCounts[
            SubMaps::subMapFixedGraphicTableCountsSize]
 = { 
   0,		// 0x00: null, headers point to poloy 1
	 3,		// 0x01: poloy forest
	 2,		// 0x02: caron forest
	 3, 	// 0x03: volcanic tunnel
	 4, 	// 0x04: polly mtn 1
	 2, 	// 0x05: polly mtn 2
	 9, 	// 0x06: lake rocky
	 2, 	// 0x07: lake crystal
	 2, 	// 0x08: green island
	 3, 	// 0x09: cavern island
	 3, 	// 0x0A: coco island
	 2, 	// 0x0B: battle fortress flight
	 3, 	// 0x0C: battle fortress
 };
 
const int SubMaps::subMapLevelObjectTableCounts[
    SubMaps::subMapLevelObjectTableCountsSize]
 = { 
   0,		// 0x00: null, headers point to poloy 1
	 3,		// 0x01: poloy forest
	 2,		// 0x02: caron forest
	 3, 	// 0x03: volcanic tunnel
	 4, 	// 0x04: polly mtn 1
	 2, 	// 0x05: polly mtn 2
	 9, 	// 0x06: lake rocky
	 2, 	// 0x07: lake crystal
	 2, 	// 0x08: green island
	 3, 	// 0x09: cavern island
	 3, 	// 0x0A: coco island
	 3, 	// 0x0B: battle fortress flight
	 3, 	// 0x0C: battle fortress
	 0, 	// 0x0D: null, headers point to poloy 1
	 0, 	// 0x0E: null, headers point to poloy 1
	 0, 	// 0x0F: null, headers point to poloy 1
	 0, 	// 0x10: world map
	 0, 	// 0x11: tails' house
	 0, 	// 0x12: null? primary map header points to intro forest
	 0,		// 0x13: intro forest
	 2,		// 0x14: leave dock cutscene
	 1,		// 0x15: return to dock cutscene
 };


}; 
