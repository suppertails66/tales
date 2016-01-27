#include "structs/PngConversion.h"
#include "gamegear/GGPalette.h"
#include <cstdio>
#include <fstream>
#include <iostream>

namespace Tales {


#ifdef TALES_ENABLE_LIBPNG
  class PngFailure { };
#endif

bool PngConversion::canConvertPng() {
  #ifdef TALES_ENABLE_LIBPNG
    return true;
  #else
    return false;
  #endif
}
  
bool PngConversion::twoDArrayToIndexedPngGG(
                                    const std::string& filename,
                                    TwoDByteArray& dst) {
#ifdef TALES_ENABLE_LIBPNG
  
#else
  return false;
#endif
}

bool PngConversion::indexedPngToTwoDArrayGG(TwoDByteArray& dst,
                                  const std::string& filename) {
#ifdef TALES_ENABLE_LIBPNG
  
  // Read file
  png_structp png_ptr;
  png_infop info_ptr;
  if (!pngalloc(png_ptr, info_ptr, filename)) {
    return false;
  }
  
  try {
  
    // Fail if image is not palettized
    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_PALETTE) {
      throw PngFailure();
    }
    
    // Fail if data is not 8-bit
    if (png_get_bit_depth(png_ptr, info_ptr) != 8) {
      throw PngFailure();
    }
    
    png_color* palette;
    int num_palette;
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    
    // Fail if there are not enough entries in the palette
    if (num_palette < GGPalette::numColorsInPalette) {
      throw PngFailure();
    }
    
//    png_bytep trans_alpha;
//    int num_trans;
//    png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, NULL);
    
    // Retrieve image width and height
    int w = png_get_image_width(png_ptr, info_ptr);
    int h = png_get_image_height(png_ptr, info_ptr);
    
    // Initialize destination array
    dst.resize(w, h);

    // Get the pixel data
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    
    // Copy values to the destination array
    for (int j = 0; j < h; j++) {
      for (int i = 0; i < w; i++) {
        dst.data(i, j) = row_pointers[j][i];
      }
    }
    
//    std::cout << num_palette << std::endl;
  
    // Clean up
    pngfree(png_ptr, info_ptr);
    return true;
  }
  catch (PngFailure&) {
    // Clean up
    pngfree(png_ptr, info_ptr);
    return false;
  }
#else
  return false;
#endif
}

bool PngConversion::pngalloc(
                     png_structp& png_ptr,
                     png_infop& info_ptr,
                     const std::string& filename) {
  // Generic PNG read code, minimally modified from libpng/example.c
  
  unsigned int sig_read = 0;
//  png_uint_32 width, height;
//  int bit_depth, color_type, interlace_type;
  FILE *fp;
  if ((fp = fopen(filename.c_str(), "rb")) == NULL) {
    return false;
  }
  
  // Check if this is really a PNG
  
  char buf[pngBytesToCheck_];
  if (fread(buf, 1, pngBytesToCheck_, fp) != pngBytesToCheck_) {
    fclose(fp);
    return false;
  }
  
  if (png_sig_cmp((png_bytep)buf, (png_size_t)0, pngBytesToCheck_)) {
    fclose(fp);
    return false;
  }
  
  sig_read = pngBytesToCheck_;
  
  // Try to read the file
  
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
    NULL, NULL, NULL);
  
  if (png_ptr == NULL) {
    fclose(fp);
    return false;
  }
  
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return false;
  }
  
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return false;
  }
  
  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, sig_read);
  
  // Read entire image
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  
  fclose(fp);
  
  return true;
}
                     
bool PngConversion::pngfree(png_structp& png_ptr,
                    png_infop& info_ptr) {
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  return true;
}


};
