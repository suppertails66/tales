#include "gamegear/GGFullTileSet.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include "structs/Tbyte.h"
#include <string>
#include <cstring>

using namespace Luncheon;

namespace Tales {


GGFullTileSet::GGFullTileSet() { };

GGFullTileSet::GGFullTileSet(const GGFullTileSet& ggTileSet) {
  // Copy tile data
  for (int i = 0; i < numTilesInSet; i++) {
    tileSet_[i] = ggTileSet.tileSet_[i];
  }
}

GGFullTileSet& GGFullTileSet::operator=(const GGFullTileSet& ggTileSet) {
  // Copy tile data
  for (int i = 0; i < numTilesInSet; i++) {
    tileSet_[i] = ggTileSet.tileSet_[i];
  }
  
  return *this;
}

GGFullTileSet::GGFullTileSet(const VirtualVDP& vdp) {
  // Deinterleave VRAM for future tile lookup
	// Format: [p1][p2] [p3][p4] [p5][p6] [p7][p8],
	// where each bracketed value represents a nibble
	// and the contained value is the corresponding palette entry
	
	Tbyte deinterleavedVRAM[VirtualVDP::vramSize];
	const Tbyte* sourceVRAM = vdp.vramRead(0);

  // Handle 4 bytes at a time (4 bytes = 1 row of pixels)
	for (int i = 0; i < VirtualVDP::vramSize; i += deinterleaveBufferSize) {

    // Storage for the deinterleaved data
		Tbyte bytes[deinterleaveBufferSize];
		std::memset(bytes, 0, deinterleaveBufferSize);

    // Examine bits in the bytes (all 0 bits, then all 1 bits, etc.)
		for (int j = 0; j < 8; j++) {
		
		  // AND mask for the current bit
			Tbyte mask = ((Tbyte)1) << j;

			// Odd-numbered bits go in the high nibble of the target byte
			if (j % 2) {
			  // Copy from each target byte
				for (int k = 0; k < 4; k++) {
					bytes[3 - j/2] |= ((((*(sourceVRAM + i + k) & mask) >> j) << k) << 4);
				}
			}
			// Even bits go to the low nibble of the current byte
			else {
			  // Copy from each target byte
				for (int k = 0; k < 4; k++) {
					bytes[3 - j/2] |= (((*(sourceVRAM + i + k) & mask) >> j) << k);
				}
			}
		}

    // Copy the deinterleaved bytes
		std::memcpy(deinterleavedVRAM + i, bytes, 4);
	}
	
	// Copy each tile's deinterleaved pixel data to the corresponding GGTile
	for (int i = 0; i < numTilesInSet; i++) {
    tileSet_[i].assignFromDeinterleavedPixels(
      // Source data location is the current tile number ...
      deinterleavedVRAM + (i * 
        // ... multiplied by the number of bytes per tile ...
        (GGTile::dataSize /
          // ... divided by the number of pixels per byte (which is 2)
          (2))));
          // bad: shouldn't assume 8 bits per char
          /*CHAR_BIT / GGTile::bitsPerPixel*/
  }

/*	// Temporary buffer to hold 1-byte-per-pixel decompressed VRAM
	Tbyte decVRAM[VirtualVDP::vramSize * 2];
	
	// Reorganize VRAM to 1 byte per pixel
	for (int i = 0; i < VirtualVDP::vramSize; i++) {
	  // Low nibble = byte 2
		decVRAM[(i * 2) + 1] = deinterleavedVRAM[i] & 0x0F;
		
		// High nibble = byte 1
		decVRAM[(i * 2)] = (deinterleavedVRAM[i] & 0xF0) >> 4;
	} */
	
}

GGTile& GGFullTileSet::operator[](unsigned int tileNum) {
  // Throw on out-of-range access
  if (tileNum >= numTilesInSet) {
    throw TGenericException(TALES_SRCANDLINE,
                           "GGFullTileSet::operator[](unsigned int)",
                           std::string("Out-of-range tileSet_ access (index ")
                            + StringConversion::toString(tileNum)
                            + std::string(")"));
  }

  return tileSet_[tileNum];
}

const GGTile& GGFullTileSet::operator[](unsigned int tileNum) const {
  // Throw on out-of-range access
  if (tileNum >= numTilesInSet) {
    throw TGenericException(TALES_SRCANDLINE,
                           "GGFullTileSet::operator[](unsigned int) const",
                           std::string("Out-of-range tileSet_ access (index ")
                            + StringConversion::toString(tileNum)
                            + std::string(")"));
  }
  
  return tileSet_[tileNum];
}


}; 
