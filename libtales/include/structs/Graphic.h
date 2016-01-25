#ifndef GRAPHIC_H
#define GRAPHIC_H


#include "structs/Tbyte.h"
#include "structs/TransModel.h"
#include "structs/Color.h"
#include "gamegear/GGTile.h"
#include "gamegear/GGPalette.h"

namespace Tales {


/**
 * Storage, access, and manipulator for a raw ARGB graphic.
 * Pixel data is stored in an array in ARGB format, with 1 byte per component.
 * Pixels are ordered left-to-right, top-to-bottom.
 */
class Graphic {
public:

  /**
   * Enum of transparency handling options for blitting.
   */
  enum TransBlitOption {
    noTransUpdate = 0,    /*< Don't update transparency model */
    transUpdate = 1       /*< Update transparency model */
  };
  
  /**
   * Enum of transparency handling options for tile-and-palette constructor.
   */
  enum TileTransferTransOption {
    noTileTrans = 0,    /*< Set alpha on pixels with transparency color */
    tileTrans = 1       /*< Leave pixels with transparency color solid */
  };

  /**
  * Number of bytes per pixel in internal pixel array.
  */
  const static int bytesPerPixel = 4;

  /**
  * Number of bits per pixel in internal pixel array.
  */
  const static int bitsPerPixel = bytesPerPixel * sizeof(Tbyte);
  
  /**
  * Default constructor.
  * Initializes width and height to zero and pixel array to NULL.
  */
  Graphic();
  
  /**
  * Copy constructor.
  * @param graphic Graphic to copy data from.
  */
  Graphic(const Graphic& graphic);
  
  /**
  * Copy assignment.
  * @param graphic Graphic to copy data from.
  */
  Graphic& operator=(const Graphic& graphic);
  
  /**
  * Tile-and-palette constructor.
  * Given a GGTile containing color data and a GGPalette to color it with,
  * this produces a graphic corresponding to the GGTile.
  * @param tile Tile containing indexed color values.
  * @param palette Palette containing colors corresponding to the tile indices.
  */
  Graphic(const GGTile& tile,
          const GGPalette& palette,
          TileTransferTransOption transOption = noTileTrans);
  
  /**
  * Tile-and-palette constructor.
  * Given a GGTile containing color data and a GGPalette to color it with,
  * this produces a graphic corresponding to the GGTile.
  * @param tile Tile containing indexed color values.
  * @param palette Palette containing colors corresponding to the tile indices.
  */
  Graphic(const GGTile& tile,
          const GGPalette& palette,
          TileTransferTransOption transOption,
          Color backgroundColor);
  
  /**
  * Empty graphic constructor.
  * Initializes width and height to specified values, and initializes
  * pixel array to all 0xFF (fully transparent white).
  * @param w__ Graphic width.
  * @param h__ Graphic height.
  */
  Graphic(int w__, int h__);
  
  /**
  * Destructor.
  */
  ~Graphic();
  
  int numTotalPixels() const;
  
  /**
  * Retrieves size of internal pixel data array.
  * @return Size of internal pixel data array.
  */
  int size() const;
  
  /**
  * Getter for image width.
  * @return Image width.
  */
  int w() const;
  
  /**
  * Getter for image height.
  * @return Image height.
  */
  int h() const;
  
  /**
  * Retrieves number of bytes per row of pixel data.
  * @return Number of bytes per row of pixel data.
  */
  int bytesPerRow() const;
  
  /**
  * Returns a const pointer to the start of the internal pixel data array.
  * @return Const pointer to the start of the internal pixel data array.
  */
  const Tbyte* const_imgdat() const;
  
  /**
  * Returns a non-const pointer to the start of the internal pixel data array.
  * @return Non-const pointer to the start of the internal pixel data array.
  */
  Tbyte* imgdat();
  
  /**
  * Returns a const pointer to the internal pixel data array.
  * @param xpos X-position of data pointer.
  * @param ypos Y-position of data pointer.
  * @return Const pointer to the internal pixel data array.
  */
  const Tbyte* const_imgdat(int xpos, int ypos) const;
  
  /**
  * Returns a non-const pointer to the internal pixel data array.
  * @param xpos X-position of data pointer.
  * @param ypos Y-position of data pointer.
  * @return Non-const pointer to the internal pixel data array.
  */
  Tbyte* imgdat(int xpos, int ypos);
  
  /**
   * Copies a portion of another graphic onto this one.
   * Transparency is ignored, so alpha information will be transferred
   * instead of blended. To perform alpha blending, use blit() instead.
   * @param src The source Graphic for the blit.
   * @param dstbox A Box outlining the area to be blitted to in this Graphic.
   * @param srcbox A Box outlining the area to be blitted from src.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see blit()
   */
  void copy(const Graphic& src,
            Box dstbox,
            Box srcbox,
            TransBlitOption updateTrans = transUpdate);
  
  /**
   * Copies a portion of another graphic onto this one.
   * Transparency is ignored, so alpha information will be transferred
   * instead of blended. To perform alpha blending, use blit() instead.
   * @param src The source Graphic for the blit.
   * @param dstbox A Box outlining the area to be blitted to in this Graphic.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see blit()
   */
  void copy(const Graphic& src,
            Box dstbox,
            TransBlitOption updateTrans = transUpdate);
            
  void copyWrap(const Graphic& src,
                Box dstbox,
                Box srcbox,
                TransBlitOption updateTrans = transUpdate);
  
  /**
   * Blits a portion of another graphic onto this one.
   * Similar to copy(), but uses the transparency model to avoid copying
   * transparent pixels.
   * @param src The source Graphic for the blit.
   * @param dstbox A Box outlining the area to be blitted to in this Graphic.
   * If either of the Box's w or h fields is zero, only the x and y position
   * will be used.
   * @param srcbox A Box outlining the area to be blitted from src.
   * If either of the Box's w or h fields is zero, only the x and y position
   * will be used.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see copy()
   */
  void blit(const Graphic& src,
            Box dstbox,
            Box srcbox,
            TransBlitOption updateTrans = transUpdate);
  
  /**
   * Blits a portion of another graphic onto this one.
   * Uses entirety of source graphic.
   * @param src The source Graphic for the blit.
   * @param dstbox A Box outlining the area to be blitted to in this Graphic.
   * If either of the Box's w or h fields is zero, only the x and y position
   * will be used.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see copy()
   */
  void blit(const Graphic& src,
            Box dstbox,
            TransBlitOption updateTrans = transUpdate);
  
  /**
   * Blits a portion of another graphic onto this one.
   * Uses entirety of source graphic and copies to upper-left corner.
   * @param src The source Graphic for the blit.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see copy()
   */
  void blit(const Graphic& src,
            TransBlitOption updateTrans = transUpdate);
  
  /**
   * Blits a portion of another graphic onto this one.
   * Uses entirety of source graphic and copies to given (x, y) position.
   * @param src The source Graphic for the blit.
   * @param xpos The x-position at which to blit the graphic.
   * @param ypos The y-position at which to blit the graphic.
   * @param updateTrans If noTransUpdate, the TransModel will not be updated.
   * Saves time if a Graphic is to be used only as a blit destination and not a
   * source, or if it doesn't have any transparent areas.
   * @see copy()
   */
  void blit(const Graphic& src,
            int xpos,
            int ypos,
            TransBlitOption updateTrans = transUpdate);
            
  void blitWrap(const Graphic& src,
                Box dstbox,
                Box srcbox,
                TransBlitOption updateTrans = transUpdate);
            
  /**
  * Returns the color of the pixel at the given position as a Color.
  * @param xpos X-position of the target pixel.
  * @param ypos Y-position of the target pixel.
  * @return A Color containing the pixel's ARGB values.
  */
  Color getPixel(int xpos, int ypos);
            
  /**
  * Sets the color of a pixel.
  * If the updateTrans parameter is noTransUpdate, this function does 
  * not fully update the transparency model, leaving it in an invalid state.
  * The intention is that if a Graphic must be modified outside of a blit()
  * or copy() -- for example, to load some new data -- it should be done
  * through calls to this function or imgdat(), then concluded with a
  * call to regenerateTransparencyModel().
  * Note that in order to facilitate the expected calls to
  * regenerateTransparencyModel() when updateTrans is noTransUpdate, the
  * transparency model is in fact modified with "stub" values indicating
  * the new pixel transparency, so any call that uses noTransUpdate should
  * consider the transparency data invalid until regenerateTransparencyModel()
  * is called.
  * @param xpos X-position of the target pixel.
  * @param ypos Y-position of the target pixel.
  * @param color A Color containing the new ARGB values for the pixel.
  * @param updateTrans A TransBlitOption specifying whether or not to update
  * the transparency model after modifying the pixel.
  * @see imgdat()
  * @see regenerateTransparencyModel()
  */
  void setPixel(int xpos,
                int ypos,
                Color color,
                TransBlitOption updateTrans = noTransUpdate);
                
  /**
   * Draws a line of the specified color and width between two points.
   * @param x1 X-coordinate of the starting point.
   * @param y1 Y-coordinate of the starting point.
   * @param x2 X-coordinate of the ending point.
   * @param y2 Y-coordinate of the ending point.
   * @param color Color of the line to draw.
   * @param width Width of the line in pixels.
   * @param updateTrans A TransBlitOption specifying whether or not to update
   * the transparency model after drawing the line.
   */
  void drawLine(int x1, int y1,
                int x2, int y2,
                Color color,
                int width,
                TransBlitOption updateTrans = transUpdate);
                
  /**
   * Draws a border of the specified color and width along a rectangular area.
   * The border extends outward from both sides of the lines forming the
   * area; for example, a lineWidth of 3 will add 1 extra row of pixels above
   * the top side of the border and 1 extra row below it, with the other
   * sides similarly augmented. Width and height may be negative.
   * Due to foolishness with the drawLine() function used to implement this,
   * lineWidth must be odd or the border will not render correctly.
   * @param x X-coordinate of the top-left corner of the border.
   * @param y Y-coordinate of the top-left corner of the border.
   * @param width Width of the bordered area.
   * @param height Height of the bordered area.
   * @param color Color of the line to draw.
   * @param lineWidth Width of the line in pixels.
   * @param updateTrans A TransBlitOption specifying whether or not to update
   * the transparency model after drawing the border.
   */
  void drawRectBorder(int x,
                      int y,
                      int width,
                      int height,
                      Color color,
                      int lineWidth,
                      TransBlitOption updateTrans = transUpdate);
                
  void fillRect(int x, int y,
                int width, int height,
                Color color,
                TransBlitOption updateTrans = transUpdate);
  
  /**
   * Scales this Graphic to another size and stores in dst.
   * The original Graphic is unmodified.
   * The scale factor is determined by the w and h fields of dstbox; the
   * graphic will be stretched or shrunken as needed to fill the whole
   * box.
   * Scaling is done without any filtering, so scaling that is not by an even
   * factor (twice the w/h, triple...) will most likely turn out
   * poorly.
   * @param dst Destination graphic.
   * @param dstbox Box indicating the position and size of the scaled Graphic
   * within dst.
   * @param updateTrans A TransBlitOption specifying whether or not to update
   * the transparency model after scaling the Graphic.
   */
  void scale(Graphic& dst,
             Box dstbox,
             TransBlitOption updateTrans = transUpdate);
  
  /**
   * Alternate form of scale() that always fits to dst's full dimensions.
   * @param dst Destination graphic.
   * @param updateTrans A TransBlitOption specifying whether or not to update
   * the transparency model after scaling the Graphic.
   */
  void scale(Graphic& dst,
             TransBlitOption updateTrans = transUpdate);
        
  /**
  * Fully regenerates the transparency model to correspond to the pixel data.
  * This is a relatively expensive call, and should generally only be used to
  * conclude setPixel() or imgdat() operations used to load new
  * graphics data.
  */
  void regenerateTransparencyModel();

  /**
   * Clear the graphic to fully transparent white.
   */
  void clear();

  /**
   * Clear the graphic to the given color.
   * @param color The Color to clear the image to.
   */
  void clear(Color color);
  
protected:

#ifdef _WIN32
  // no endianness check
#else
  union EndCheck {
    EndCheck(std::int32_t i)
      : asInt(i) { };
    std::int32_t asInt;
    Tbyte asChar[4];
  } endCheck = 0x01;
#endif

  enum CopyOrBlitCommand {
    blitCommand     = 0,
    copyCommand     = 1
  };

  enum CopyOrBlitWrapCommand {
    blitWrapCommand     = 0,
    copyWrapCommand     = 1
  };

  /**
   * Draws a 1-pixel-wide line of the specified color between two points.
   * @param x1 X-coordinate of the starting point.
   * @param y1 Y-coordinate of the starting point.
   * @param x2 X-coordinate of the ending point.
   * @param y2 Y-coordinate of the ending point.
   * @param color Color of the line to draw.
   */
  void drawPixelLine(int x1, int y1,
                     int x2, int y2,
                     Color color);
                     
  void drawHorizontalPixelLine(int x1, int y1,
                               int distance,
                               Color color);
                     
  void scaleInternal(Graphic& dst,
                     Box dstbox);
  
  void scaleX(Graphic& dst,
                 Box dstbox,
                 int srcYPos,
                 int dstYPos);
                 
  void blitOrCopyInternal(const Graphic& src,
                          Box dstbox,
                          Box srcbox,
                          TransBlitOption updateTrans = transUpdate,
                          CopyOrBlitCommand command = blitCommand);
                 
  void blitOrCopyWrapInternal(const Graphic& src,
                          Box dstbox,
                          Box srcbox,
                          TransBlitOption updateTrans = transUpdate,
                          CopyOrBlitWrapCommand command = blitWrapCommand);
                 
  void copyInternal(int rowsToCopy,
                    int columnsToCopy,
                    int srcBytesPerRow,
                    int srcTransModelBytesPerRow,
                    Tbyte* putpos,
                    const Tbyte* getpos,
                    char* transputpos,
                    const char* transgetpos);
                 
  void blitInternal(int rowsToCopy,
                    int columnsToCopy,
                    int srcBytesPerRow,
                    int srcTransModelBytesPerRow,
                    Tbyte* putpos,
                    const Tbyte* getpos,
                    char* transputpos,
                    const char* transgetpos);
  
  /**
  * Tile-and-palette constructor.
  * Given a GGTile containing color data and a GGPalette to color it with,
  * this produces a graphic corresponding to the GGTile.
  * @param tile Tile containing indexed color values.
  * @param palette Palette containing colors corresponding to the tile indices.
  */
  void fromTile(const GGTile& tile,
                const GGPalette& palette,
                TileTransferTransOption transOption,
                bool skipTransparentPixels = false);
  
  /**
  * Graphic width.
  */
  int w_;
  
  /**
  * Graphic height.
  */
  int h_;
  
  /**
  * Pixel data array.
  */
  Tbyte* imgdat_;
  
  /**
  * Transparency data.
  */
  TransModel transModel_;
  
};


};


#endif 
