#include "gamegear/GGColor.h"

namespace Tales {


GGColor::GGColor()
	: nativeColor_(0),
		realR_(0),
		realG_(0),
		realB_(0) { };

GGColor::~GGColor() { };

int GGColor::nativeColor() const {
	return nativeColor_;
}

int GGColor::realR() const {
	return realR_;
}

int GGColor::realG() const {
	return realG_;

}

int GGColor::realB() const {
	return realB_;
}

void GGColor::setNativeColor(int color) {
	// Set native color
	nativeColor_ = color;

	// Retrieve real RGB values from color
	realR_ = (color & 0x000F) << 4;
	realG_ = (color & 0x00F0);
	realB_ = (color & 0x0F00) >> 4;
	
  realR_ = correctColor(realR_);
  realG_ = correctColor(realG_);
  realB_ = correctColor(realB_);
  
//  if (realR_ < 240) { realR_ += 16; } else { realR_ += 15; }
//  if (realG_ < 240) { realG_ += 16; } else { realG_ += 15; }
//  if (realB_ < 240) { realB_ += 16; } else { realB_ += 15; }
}

void GGColor::setRGB(int r, int g, int b) {
  
/*  if (r > 240) { r -= 15; } else { r -= 16; }
  if (g > 240) { g -= 15; } else { g -= 16; }
  if (b > 240) { b -= 15; } else { b -= 16; }
  if (r < 0) { r = 0; }
  if (g < 0) { g = 0; }
  if (b < 0) { b = 0; } */
  
	// Reduce color precision to 16 bits
	realR_ = (r & 0x00F0);
	realG_ = (g & 0x00F0);
	realB_ = (b & 0x00F0);

	// Set native color
	nativeColor_ = ((realR_ >> 4)
					| (realG_)
					| (realB_ << 4));
					
  // Correct brightness so we cover the full range linearly
  // instead of truncating (without correction, values will be
  // 0-240 instead of 0-255)
  realR_ = correctColor(realR_);
  realG_ = correctColor(realG_);
  realB_ = correctColor(realB_);
  
/*  if (realR_ < 240) { realR_ += 16; } else { realR_ += 15; }
  if (realG_ < 240) { realG_ += 16; } else { realG_ += 15; }
  if (realB_ < 240) { realB_ += 16; } else { realB_ += 15; } */
}

int GGColor::correctColor(int rgbColor) {
  return rgbColor + (rgbColor / 16);
}


};
