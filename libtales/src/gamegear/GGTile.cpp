#include "gamegear/GGTile.h"
#include "util/ArrayOps.h"
#include "gamegear/GGPalette.h"
#include "exception/ColorOutOfRangeException.h"
#include <cstring>
#include <iostream>

using namespace Luncheon;

namespace Tales {

GGTile::GGTile() {
  // Initialize all pixels to 0
  std::memset(imgdat_, 0, sizeof(imgdat_));
}

GGTile::GGTile(const GGTile& tile) {
  // Copy pixel data
  std::memcpy(imgdat_, tile.imgdat_, sizeof(imgdat_));
}

GGTile& GGTile::operator=(const GGTile& tile) {
  // Copy pixel data
  std::memcpy(imgdat_, tile.imgdat_, sizeof(imgdat_));
  
  return *this;
}

GGTile::GGTile(const Tbyte* vramData) {
  assignFromInterleavedPixels(vramData);
}

void GGTile::assignFromInterleavedPixels(
    const Tbyte* interleavedPixelData) {
  // Deinterleaved data buffer
  Tbyte deinterleavedPixels[rawInputDataSize];
    
  // Handle 4 bytes at a time (4 bytes = 1 row of pixels)
	for (int i = 0; i < rawInputDataSize; i += deinterleaveBufferSize) {

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
					bytes[3 - j/2]
					  |= ((((*(interleavedPixelData + i + k) & mask) >> j) << k) << 4);
				}
			}
			// Even bits go to the low nibble of the current byte
			else {
			  // Copy from each target byte
				for (int k = 0; k < 4; k++) {
					bytes[3 - j/2]
					  |= (((*(interleavedPixelData + i + k) & mask) >> j) << k);
				}
			}
		}

    // Copy the deinterleaved bytes
		std::memcpy(deinterleavedPixels + i, bytes, 4);
	}
	
	// Load from deinterleaved pixel data
	assignFromDeinterleavedPixels(deinterleavedPixels);
}
  
void GGTile::toInterleavedPixels(Tbyte* dst) const {

//  Tbyte interleaveBuffer[deinterleaveBufferSize];

  std::memset(dst, 0, rawInputDataSize);
  
/*  std::cout << "in:  ";
  for (int j = 0; j < dataSize; j++) {
    std::cout << std::hex << (int)(imgdat_[j]) << " ";
  }
  std::cout << std::endl; */

  // Handle 8 pixels (8 input bytes, 4 output bytes) at a time
  for (int i = 0; i < dataSize; i += 8) {
  
    Tbyte* putpos = (dst + (i/2));
      
    for (int j = 0; j < 8; j++) {
      const Tbyte* getpos = imgdat_ + i + j;
      
      Tbyte putmask = ((Tbyte)1) << ((8 - j) - 1);
      Tbyte getmask = 0x08;
      
      for (int k = 0; k < 4; k++) {
        if ((*getpos) & getmask) {
          *(putpos + ((4 - k) - 1)) |= putmask;
        }
        
        getmask >>= 1;
      }
    }
  }
  
/*  std::cout << "out:  ";
  for (int j = 0; j < rawInputDataSize; j++) {
    std::cout << std::hex << (int)(dst[j]) << " ";
  }
  std::cout << std::endl;
  
  char c;
  std::cin >> c; */
}

void GGTile::assignFromDeinterleavedPixels(
    const Tbyte* deinterleavedPixelData) {
  // Iterate over the number of bytes needed to fill a tile
  // (values are 4-bits-per-pixel and dataSize is 8-bits-per-pixel,
  // so we only need half the dataSize)
  for (int i = 0; i < rawInputDataSize; i++) {
	  // Low nibble = byte 2
		imgdat_[(i * 2) + 1] = deinterleavedPixelData[i] & 0x0F;
		
		// High nibble = byte 1
		imgdat_[(i * 2)] = (deinterleavedPixelData[i] & 0xF0) >> 4;
	}
}

int GGTile::w() {
  return width;
}

int GGTile::h() {
  return height;
}

int GGTile::size() {
  return dataSize;
}

Tbyte* GGTile::imgdat() {
  return imgdat_;
}

const Tbyte* GGTile::const_imgdat() const {
  return imgdat_;
}

Tbyte GGTile::getPixel(int xpos, int ypos) const {
  return imgdat_[(ypos * bytesPerRow) + (xpos * bytesPerPixel)];
}

void GGTile::setPixel(
              int xpos,
              int ypos,
              Tbyte value) {
  // Throw if value to be set is not a valid color index
  if (value >= GGPalette::numColorsInPalette) {
    throw ColorOutOfRangeException(TALES_SRCANDLINE,
                                   "GGTile::setPixel(int,int,Tbyte)",
                                   value);
  }
  
  imgdat_[(ypos * bytesPerRow) + (xpos * bytesPerPixel)]
    = value;
}

void GGTile::flipHorizontal() {
  // Copy array pointer
  Tbyte* datptr = imgdat_;
  
  for (int j = 0; j < height; j++) {
    // Reverse each row of the data
    ArrayOps::reverseArray(datptr, width);
    datptr += width;
  }
}

void GGTile::flipVertical() {
  // Temporary array to hold row while swapping
  Tbyte temp[bytesPerRow];
  
  // Pointer to first row
  Tbyte* frow = imgdat_;
  
  // Pointer to last row
  Tbyte* lrow = imgdat_ + dataSize - bytesPerRow;
  
  while (frow < lrow) {
    // Copy frow to temp
    std::memcpy(temp, frow, bytesPerRow);
    
    // Copy lrow to frow
    std::memcpy(frow, lrow, bytesPerRow);
    
    // Copy temp to lrow
    std::memcpy(lrow, temp, bytesPerRow);
    
    // Advance frow by one row
    frow += bytesPerRow;
    
    // Move back lrow by one row
    lrow -= bytesPerRow;
  }
  
  
}

void GGTile::save(std::string& data) {
  // Write pixel values
  data += std::string((char*)imgdat_, dataSize);
}

int GGTile::load(const Tbyte* data) {
  // Read pixel values
  std::memcpy(imgdat_,
              data,
              dataSize);
  
  return dataSize;
}
  
void GGTile::transferToByteArray(TwoDByteArray& dst,
                         int x, int y) {
  for (int j = 0; j < GGTile::height; j++) {
    for (int i = 0; i < GGTile::width; i++) {
      // just be lazy and use a "safe" copy function
      dst.setDataClipped(x + i,
                         y + j,
                         getPixel(i, j));
    }
  }
}


};
