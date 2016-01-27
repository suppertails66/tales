#include "structs/PngConversion.h"
#include "gamegear/GGPalette.h"
#include <cstdio>
#include <cstring>
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
                                    TwoDByteArray& src,
                                    GGPalette palette,
                                    bool transparency) {
#ifdef TALES_ENABLE_LIBPNG
  if ((src.w() == 0) || (src.h() == 0)) {
    return false;
  }

  png_structp png_ptr;
  png_infop info_ptr;
  png_bytepp rows = NULL;
  
  
  try {
    // Fail if unable to allocate structures
    if (!pngwalloc(png_ptr, info_ptr)) {
      throw PngFailure();
    }
    
    png_set_IHDR(png_ptr, info_ptr,
                 src.w(), src.h(),
                 pngBitDepth_,
                 PNG_COLOR_TYPE_PALETTE,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);
                 
//    png_colorp palette = 
//      (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH
//                                * png_sizeof(png_color));
    
    // Create palette
    png_color pngPalette[GGPalette::numColorsInPalette];
//      (png_colorp)png_malloc(png_ptr, GGPalette::numColorsInPalette
//                                * png_sizeof(png_color));
    
    // Set palette colors
    for (int i = 0; i < GGPalette::numColorsInPalette; i++) {
      pngPalette[i].red = palette[i].realR();
      pngPalette[i].green = palette[i].realG();
      pngPalette[i].blue = palette[i].realB();
    }
    
    // Create link to palette
//    png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);
    png_set_PLTE(png_ptr, info_ptr, pngPalette, GGPalette::numColorsInPalette);
    
    // Create and initialize transparency array
    png_byte pngTrans[GGPalette::numColorsInPalette];
    std::memset((char*)(pngTrans), 255, GGPalette::numColorsInPalette);
    
    // Set color 0 to transparent if transparency is enabled
    if (transparency) {
      pngTrans[palette.getTransColorIndex()] = 0;
    }
    
    // Create link to transparency array
    png_set_tRNS(png_ptr, info_ptr,
                 pngTrans,
                 GGPalette::numColorsInPalette,
                 NULL);

    // Create pixel data
    rows = new png_bytep[src.h()];
    for (int j = 0; j < src.h(); j++) {
      rows[j] = new png_byte[src.w()];
      
      for (int i = 0; i < src.w(); i++) {
        rows[j][i] = src.data(i, j);
      }
    }
    
    // Create link to rows
    png_set_rows(png_ptr, info_ptr, rows);
    
    // Write to file
    if (!pngwrite(png_ptr, info_ptr, filename)) {
      // Fail if unable to write
      throw PngFailure();
    }
    
    // Clean up
    if (rows != NULL) {
      for (int j = 0; j < src.h(); j++) {
        delete rows[j];
      }
      delete rows;
      rows = NULL;
    }
    pngwfree(png_ptr, info_ptr);
    return true;
  }
  catch (PngFailure&) {
    if (rows != NULL) {
      for (int j = 0; j < src.h(); j++) {
        delete rows[j];
      }
      delete rows;
      rows = NULL;
    }
    pngwfree(png_ptr, info_ptr);
    return false;
  }
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
  if (!pngralloc(png_ptr, info_ptr, filename)) {
    return false;
  }
  
  try {
  
    // Fail if image is not palettized
    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_PALETTE) {
      throw PngFailure();
    }
    
    // Fail if data bit depth does not match expected
    if (png_get_bit_depth(png_ptr, info_ptr) != pngBitDepth_) {
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
    pngrfree(png_ptr, info_ptr);
    return true;
  }
  catch (PngFailure&) {
    // Clean up
    pngrfree(png_ptr, info_ptr);
    return false;
  }
#else
  return false;
#endif
}

#ifdef TALES_ENABLE_LIBPNG
bool PngConversion::pngralloc(
                     png_structp& png_ptr,
                     png_infop& info_ptr,
                     const std::string& filename) {
  // Generic PNG read init code, minimally modified from libpng/example.c
  
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
                     
bool PngConversion::pngrfree(png_structp& png_ptr,
                    png_infop& info_ptr) {
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  return true;
}

bool PngConversion::pngwalloc(png_structp& png_ptr,
                     png_infop& info_ptr) {
  // Generic PNG write init code, minimally modified from libpng/example.c
  
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
    NULL, NULL, NULL);
    
  if (png_ptr == NULL) {
//    fclose(fp);
    return false;
  }
  
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
//    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return false;
  }
  
  return true;
}

bool PngConversion::pngwfree(png_structp& png_ptr,
                     png_infop& info_ptr) {
  png_destroy_write_struct(&png_ptr, &info_ptr);
  return true;
}

bool PngConversion::pngwrite(png_structp& png_ptr,
                     png_infop& info_ptr,
                     const std::string& filename) {
  // Generic PNG write code, minimally modified from libpng/example.c
  
  FILE *fp;
  
  fp = fopen(filename.c_str(), "wb");
  if (fp == NULL) {
    return false;
  }
    
  if (setjmp(png_jmpbuf(png_ptr))) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return false;
  }
  
  png_init_io(png_ptr, fp);
  
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  
  fclose(fp);
  
  return true;
}
#endif


};
