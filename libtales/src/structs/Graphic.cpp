#include "structs/Graphic.h"
#include "exception/TGenericException.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace Tales {


Graphic::Graphic()
  : w_(0),
    h_(0),
    imgdat_(NULL),
    transModel_() { };

Graphic::Graphic(const Graphic& graphic)
  : w_(graphic.w_),
    h_(graphic.h_),
    imgdat_(new Tbyte[graphic.size()]),
    transModel_(graphic.transModel_) {
  // Copy pixel data array
  std::memcpy(imgdat_, graphic.imgdat_, graphic.size());
}

Graphic& Graphic::operator=(const Graphic& graphic) {
  w_ = graphic.w_;
  h_ = graphic.h_;
  transModel_ = graphic.transModel_;
  
  // Delete existing image data
  delete imgdat_;
  
  // Copy pixel data array from source graphic
  imgdat_ = new Tbyte[graphic.size()];
  std::memcpy(imgdat_, graphic.imgdat_, graphic.size());
  
  return *this;
}

Graphic::Graphic(const GGTile& tile,
                 const GGPalette& palette,
                 TileTransferTransOption transOption)
  : w_(tile.w()),
    h_(tile.h()),
    imgdat_(new Tbyte[w_ * h_ * bytesPerPixel]),
    transModel_(w_, h_) {
  // Clear pixel data array
  clear();
  
  // Read tile data
  fromTile(tile, palette, transOption);
}

Graphic::Graphic(const GGTile& tile,
                 const GGPalette& palette,
                 TileTransferTransOption transOption,
                 Color backgroundColor)
  : w_(tile.w()),
    h_(tile.h()),
    imgdat_(new Tbyte[w_ * h_ * bytesPerPixel]),
    transModel_(w_, h_) {
  // Clear pixel data array
  clear(backgroundColor);
  
  // Read tile data
  fromTile(tile, palette, transOption, true);
}

void Graphic::fromTile(const GGTile& tile,
              const GGPalette& palette,
              TileTransferTransOption transOption,
              bool skipTransparentPixels) {
  // Copy pixel data, turning color indices into their full equivalents
  for (int j = 0; j < tile.h(); j++) {
    for (int i = 0; i < tile.w(); i++) {
      // Get the index at the current pixel
      Tbyte index = tile.getPixel(i, j);
      
      // Retrieve the associated color
      GGColor color = palette[index];
      
      // Assume full opacity
      int alpha = Color::fullAlphaOpacity;
      
      // If transOption is set and the color is transparent,
      // update the alpha channel
      if (transOption == tileTrans) {
        if (index == palette.getTransColorIndex()) {
          if (skipTransparentPixels) {
            continue;
          }
          else {
            alpha = Color::fullAlphaTransparency;
          }
        }
      }
      
      // Set the corresponding pixel in imgdat, leaving the transparency
      // model update until all pixels are set
      setPixel(i, j,
               Color(color.realR(),
                     color.realG(),
                     color.realB(),
                     alpha),
               noTransUpdate);
    }
  }
  
  // Generate the transparency model
  regenerateTransparencyModel();
}

Graphic::Graphic(int w__, int h__)
  : w_(w__),
    h_(h__),
    imgdat_(new Tbyte[w_ * h_ * bytesPerPixel]),
    transModel_(w__, h__) {
  // Clear pixel data array
  clear();
}

Graphic::~Graphic() {
  // Delete pixel data
  delete imgdat_;
}

int Graphic::numTotalPixels() const {
  return w_ * h_;
}

int Graphic::size() const {
  return w_ * h_ * bytesPerPixel;
}
  
int Graphic::w() const {
  return w_;
}

int Graphic::h() const {
  return h_;
}

int Graphic::bytesPerRow() const {
  return (w_ * bytesPerPixel);
}

const Tbyte* Graphic::const_imgdat() const {
  return imgdat_;
}

Tbyte* Graphic::imgdat() {
  return imgdat_;
}

const Tbyte* Graphic::const_imgdat(int xpos, int ypos) const {
  return imgdat_
            + (ypos * bytesPerRow())  // get row
            + (xpos * bytesPerPixel); // get column
}

Tbyte* Graphic::imgdat(int xpos, int ypos) {
  return imgdat_
            + (ypos * bytesPerRow())  // get row
            + (xpos * bytesPerPixel); // get column
}

void Graphic::copy(const Graphic& src,
          Box dstbox,
          Box srcbox,
          TransBlitOption updateTrans) {
  blitOrCopyInternal(src,
                     dstbox,
                     srcbox,
                     updateTrans,
                     copyCommand);
}

void Graphic::copy(const Graphic& src,
                   Box dstbox,
                   TransBlitOption updateTrans) {
  copy(src,
       dstbox,
       Box(0, 0, src.w(), src.h()),
       updateTrans);
}
            
void Graphic::copyWrap(const Graphic& src,
              Box dstbox,
              Box srcbox,
              TransBlitOption updateTrans) {
  blitOrCopyWrapInternal(src,
                         dstbox,
                         srcbox,
                         updateTrans,
                         CopyOrBlitWrapCommand::copyWrapCommand);
}

void Graphic::blit(const Graphic& src,
          Box dstbox,
          Box srcbox,
          TransBlitOption updateTrans) {
  blitOrCopyInternal(src,
                     dstbox,
                     srcbox,
                     updateTrans,
                     blitCommand);
}

void Graphic::blit(const Graphic& src,
          Box dstbox,
          TransBlitOption updateTrans) {
  blit(src,
       dstbox,
       Box(0, 0, src.w(), src.h()),
       updateTrans);
}

void Graphic::blit(const Graphic& src,
          TransBlitOption updateTrans) {
  blit(src,
       Box(0, 0, w_, h_),
       Box(0, 0, src.w(), src.h()),
       updateTrans);
}

void Graphic::blit(const Graphic& src,
                   int xpos,
                   int ypos,
                   TransBlitOption updateTrans) {
  blit(src,
       Box(xpos, ypos, 0, 0),
       Box(0, 0, src.w(), src.h()),
       updateTrans);
}
           
void Graphic::blitWrap(const Graphic& src,
              Box dstbox,
              Box srcbox,
              TransBlitOption updateTrans) {
  blitOrCopyWrapInternal(src,
                         dstbox,
                         srcbox,
                         updateTrans,
                         CopyOrBlitWrapCommand::blitWrapCommand);
}

Color Graphic::getPixel(int xpos, int ypos) {
//  return Color(imgdat(xpos, ypos));
  Tbyte* src = imgdat(xpos, ypos);
  
#ifdef _WIN32
  return Color(src[2], src[1], src[0], src[3]);
#else
  // does this code work? who knows???
  if (endCheck.asChar[0] != 0) {
    return Color(src[2], src[1], src[0], src[3]);
  }
  else {
    return Color(src[3], src[0], src[1], src[2]);
  }
#endif
  
  return Color(src[2], src[1], src[0], src[3]);
}

void Graphic::setPixel(int xpos,
                       int ypos,
                       Color color,
                       TransBlitOption updateTrans) {
  if ((xpos >= w_) || (ypos >= h_)) {
//    std::cerr << "setpix bad" << std::endl;
	return;
  }

  Tbyte* dst = imgdat(xpos, ypos);
  

#ifdef _WIN32
  dst[3] = color.a();
  dst[2] = color.r();
  dst[1] = color.g();
  dst[0] = color.b();
#else
  if (endCheck.asChar[0] != 0) {
    dst[3] = color.a();
    dst[2] = color.r();
    dst[1] = color.g();
    dst[0] = color.b();
  }
  else {
    dst[0] = color.a();
    dst[1] = color.r();
    dst[2] = color.g();
    dst[3] = color.b();
  }
#endif
  
  // Mark change in transparency model for future update
  if (color.a() == Color::fullAlphaTransparency) {
    *(transModel_.model(xpos, ypos)) = TransModel::transparentBaseNum;
  }
  else {
    *(transModel_.model(xpos, ypos)) = TransModel::solidBaseNum;
  }
  
  // If transparency update requested, update transparency model
  if (updateTrans == transUpdate) {
    transModel_.update(Box(xpos, ypos, 1, 1));
  }
}

void Graphic::drawLine(int x1, int y1,
                       int x2, int y2,
                       Color color,
                       int width,
                       TransBlitOption updateTrans) {
//  std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
  // To simplify the drawing loop, ensure we draw from left to right
  // by exchanging the points if point 1 is to the right of point 2
  if (x2 < x1) {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
  
  int offsetX = -(width / 2);
  
  // Y offset is inverted if drawing upward
  int offsetY = offsetX;
  if (y2 < y1) {
    offsetY = -offsetY;
  }
  
  int xDist = x2 - x1;
  int yDist = y2 - y1;
  double slope = 0;
  // Avoid division by zero
  if (xDist != 0) {
    slope = (double)yDist / (double)xDist;
  }
                       
  // Iterate over columns, drawing vertically as needed
  for (int i = 0; i < width; i++) {
    if (slope == 0) {
      if (xDist == 0) {
        // Vertical line
        drawPixelLine(x1 + offsetX, y1 + offsetY,
                      x2 + offsetX, y2 - offsetY,
                      color);
        ++offsetX;
      }
      else {
        // Horizontal line
        drawPixelLine(x1 + offsetX, y1 + offsetY,
                      x2 - offsetX, y2 + offsetY,
                      color);
        ++offsetY;
      }
    }
    else if ((slope > 1) || (slope < -1)) {
      // 0-45 or 135-180 degrees
      drawPixelLine(x1 + offsetX, y1 + offsetY,
                    x2 + offsetX, y2 - offsetY,
                    color);
      ++offsetX;
    }
    else {
      // 45-135 degrees
      drawPixelLine(x1 + offsetX, y1 + offsetY,
                    x2 - offsetX, y2 + offsetY,
                    color);
      ++offsetY;
    }
  }
  
  if (updateTrans == transUpdate) {
    regenerateTransparencyModel();
  }
}

void Graphic::drawRectBorder(
                      int x,
                      int y,
                      int width,
                      int height,
                      Color color,
                      int lineWidth,
                      TransBlitOption updateTrans) {
  // Check that area is valid
  if ((width == 0) || (height == 0)) {
    return;
  }
  
  // If width is negative, reposition rectangle so width is positive.
  // This should not strictly be necessary, but due to the off-by-one
  // issue later on it currently is.
  if (width < 0) {
    x += width;
    width = -width;
  }
  
  // If height is negative, reposition rectangle so height is positive
  if (height < 0) {
    y += height;
    height = -height;
  }
  
  // Small hack for some off-by-one issue I haven't bothered to figure out
  // the proper cause or fix for
  int xCorrection = 0;
  int yCorrection = 0;
  if (!(lineWidth % 2)) {
    // If line width is even, correct right and bottom side positions by 1
    // pixel
    xCorrection = 1;
    yCorrection = 1;
  }
                      
  // Draw four lines, one for each side of the given area
  
  // Top
  drawLine(x, y,
           x + width - 1, y,
           color,
           lineWidth,
           noTransUpdate);
  
  // Right
  drawLine(x + width - 1 + xCorrection, y,
           x + width - 1 + xCorrection, y + height - 1,
           color,
           lineWidth,
           noTransUpdate);
  
  // Bottom
  drawLine(x + width - 1, y + height - 1 + yCorrection,
           x, y + height - 1 + yCorrection,
           color,
           lineWidth,
           noTransUpdate);
  
  // Left
  drawLine(x, y + height - 1,
           x, y,
           color,
           lineWidth,
           noTransUpdate);
  
  // Update transparency model if needed
  if (updateTrans == transUpdate) {
    regenerateTransparencyModel();
  }
}
                
void Graphic::fillRect(int x, int y,
              int width, int height,
              Color color,
              TransBlitOption updateTrans) {
  int target = y + height;
  for (int i = y; i < target; i++) {
    drawHorizontalPixelLine(x, i,
                            width,
                            color);
  }
  
  if (updateTrans == transUpdate) {
    regenerateTransparencyModel();
  }
}

void Graphic::scale(Graphic& dst,
                    Box dstbox,
                    TransBlitOption updateTrans) {
  scaleInternal(dst, dstbox);
  
  if (updateTrans == transUpdate) {
    dst.regenerateTransparencyModel();
  }
}

void Graphic::scale(Graphic& dst,
                    TransBlitOption updateTrans) {
  scale(dst,
        Box(0, 0, dst.w(), dst.h()),
        updateTrans);
}

void Graphic::regenerateTransparencyModel() {
  transModel_.update();
}

void Graphic::clear() {
  // Clear pixel data array
  std::memset(imgdat_, 0xFF, size());
  transModel_.clear();
}

void Graphic::clear(Color color) {
  // Do "slow" clear.
  // TODO: This could be made faster using a memcpy trick similar to the one
  // used to initialize the transparency model
/*  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
      setPixel(i, j, color, noTransUpdate);
    }
  }
  
  regenerateTransparencyModel(); */
  
  if (size() <= 0) {
    return;
  }
  
  drawHorizontalPixelLine(0, 0,
                          numTotalPixels(),
                          color);
  
  // Change color of first pixel
/*  setPixel(0, 0, color, noTransUpdate);
  
  int totalBytesChanged = bytesPerPixel;
  int numBytesToChange = size();
  while (totalBytesChanged < numBytesToChange) {
    int tocopy = totalBytesChanged;
    if ((totalBytesChanged * 2) >= numBytesToChange) {
      tocopy = numBytesToChange - totalBytesChanged;
    }
    
    std::memcpy(imgdat_ + totalBytesChanged,
                imgdat_,
                tocopy);
    
    totalBytesChanged *= 2;
  } */
  
  if (color.a() == Color::fullAlphaTransparency) {
    transModel_.clear();
  }
  else {
    transModel_.clearOpaque();
  }
}

void Graphic::drawPixelLine(
                     int x1, int y1,
                     int x2, int y2,
                     Color color) {
  // To simplify the drawing loop, ensure we draw from left to right
  // by exchanging the points if point 1 is to the right of point 2
  if (x2 < x1) {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
  
  // Compute slope of the line
  int xDist = x2 - x1;
  int yDist = y2 - y1;
  double slope = 0;
  // Avoid division by zero
  if (xDist != 0) {
    slope = (double)yDist / (double)xDist;
  }
  
//  std::cout << slope << std::endl;

  int realX1 = x1;
  if (x1 < 0) {
    realX1 = 0;
    xDist += x1;
  }
  int realXDist = xDist;
  if (realX1 + realXDist >= w_) {
    realXDist = w_ - realX1;
  }
  
  if (slope == 0) {
    // Handle horizontal and vertical lines
    if (xDist == 0) {
      // Vertical line
      
      if ((x1 < 0) || (x1 >= w_)) {
        return;
      }
      
//      std::cout << "vert: " << y1 << " " << y2 << std::endl;
      
      // Always draw from top to bottom (x position doesn't matter)
      if (y2 < y1) {
        std::swap(y1, y2);
      }
      
      int yDist = y2 - y1;
      for (int i = 0; i <= yDist; i++) {
        int yPos = i + y1;
        
        if ((yPos < 0) || (yPos >= h_)) {
          continue;
        }
        
        setPixel(x1, yPos,
                 color);
      }
    }
    else {
      // Horizontal line
      
      if ((y1 < 0) || (y1 >= h_)) {
        return;
      }
      
//      std::cout << "horiz: " << x1 << " " << x2 << std::endl;
      
      // (X positions are already correctly configured, so no swap is needed)
      drawHorizontalPixelLine(realX1, y1,
                              realXDist,
                              color);
/*      for (int i = 0; i <= xDist; i++) {
        int xPos = i + x1;
        
        if ((xPos < 0) || (xPos >= w_)) {
          continue;
        }
        
        setPixel(xPos, y1,
                 color);
      } */
    }
  }
  else {
    int realX2 = realX1 + realXDist;
    double currY = y1;
    for (int i = realX1; i <= realX2; i++) {
      // Don't draw outside the graphic's x-area
//      if ((i < 0) || (i >= w_)) {
//        continue;
//      }
    
      // Compute the height of the line from the base at this point
      double nextY = 0;
      // Compute the pixel y-position of the next
      // point on the line
      nextY = currY + slope;
      
//      std::cout << currY << " " << nextY << std::endl;

      // Calculate number of vertical pixels needed
      double numPixels = nextY - std::floor(currY);
      if (slope < -1) {
        numPixels = std::floor(nextY) - currY;
      }
      
      int numRealPixels = numPixels;
      
      if (numRealPixels == 0) {
        // Always draw at least one pixel
        if (slope > 0) {
          numRealPixels = 1;
        }
        else {
          numRealPixels = -1;
        }
      }
      
      if (numRealPixels > 0) {
        // Draw a column of pixels from the current y-position to the next
        for (int j = 0; j < numRealPixels; j++) {
          // Get actual target y-position
          int targetY = j + currY;
          
          // Don't draw outside the graphic's y-area
          if ((targetY < 0) || (targetY >= h_)
              || (targetY > y2)) {
            continue;
          }
          
          // Draw pixel
          setPixel(i, targetY,
                   color);
        }
      }
      else {
        // Draw a column of pixels from the current y-position to the next
        for (int j = 0; j > numRealPixels; j--) {
          // Get actual target y-position
          int targetY = j + currY;
          
          // Don't draw outside the graphic's y-area
          if ((targetY < 0) || (targetY >= h_)
              || (targetY < y2)) {
            continue;
          }
          
          // Draw pixel
          setPixel(i, targetY,
                   color);
        }
      }
      
      // Move to next y-position
      currY = nextY;
    }
  }
}
                     
void Graphic::drawHorizontalPixelLine(int x1, int y1,
                             int distance,
                             Color color) {
  if ((size() <= 0)
      || (distance <= 0)) {
    return;
  }
  
  // Change color of first pixel
  setPixel(x1, y1, color, noTransUpdate);
  
  Tbyte* pos = imgdat(x1, y1);
  
  int totalBytesChanged = bytesPerPixel;
  int numBytesToChange = distance * bytesPerPixel;
  while (totalBytesChanged < numBytesToChange) {
    int tocopy = totalBytesChanged;
    if ((totalBytesChanged * 2) >= numBytesToChange) {
      tocopy = numBytesToChange - totalBytesChanged;
    }
    
    std::memcpy(pos + totalBytesChanged,
                pos,
                tocopy);
    
    totalBytesChanged *= 2;
  }
  
  // Mark transparency model
  if (color.a() == Color::fullAlphaTransparency) {
    std::memset(transModel_.model(x1, y1),
                TransModel::transparentBaseNum,
                distance);
  }
  else {
    std::memset(transModel_.model(x1, y1),
                TransModel::solidBaseNum,
                distance);
  }
}
                     
void Graphic::scaleInternal(Graphic& dst,
                            Box dstbox) {
  double scale = (double)h_ / (double)(dstbox.h());
  
  // If graphics are same size, just copy
  if ((scale == 1.00)) {
    dst.copy(*this,
             dstbox,
             transUpdate);
    return;
  }
  
  // Iterate over destination rows
  int lastNewGetRow = -1;
  int lastNewPutRow = -1;
  for (int i = 0; i < dstbox.h(); i++) {
    // Ensure the target putrow is valid
    if ((dstbox.y() + i < 0)
        || (dstbox.y() + i >= dst.h())) {
      continue;
    }
    
    // Get the corresponding source row in this graphic
    int getrow = (i * scale);
    // Make sure the row is within range
    if (getrow >= h_) {
      getrow = h_ - 1;
    }
    if (getrow < 0) {
      getrow = 0;
    }
    
    // Optimization: if new getrow is same as last, memcpy that row
    if (getrow == lastNewGetRow) {
      std::memcpy(dst.imgdat(0, i + dstbox.y()),
                  dst.imgdat(0, lastNewPutRow + dstbox.y()),
                  dstbox.w() * bytesPerPixel);
      continue;
    }
    else {
      lastNewGetRow = i * scale;
      lastNewPutRow = i;
    }
    
    // Scale the row and put it in dst
    scaleX(dst, dstbox, getrow, i + dstbox.y());
  }
  
}
  
void Graphic::scaleX(Graphic& dst,
                         Box dstbox,
                         int srcYPos,
                         int dstYPos) {
  double scale = (double)w_ / (double)(dstbox.w());
                         
//  for (int i = 0; i < dstbox.w(); i++) {
  for (int i = dstbox.x(); i < dstbox.w(); i++) {
    // Ensure the target putcol is valid
//    if ((dstbox.x() + i < 0)
    if ((dstbox.x() + i >= dst.w())) {
      break;
    }
    
    int getpos = (i * scale);
    if (getpos >= w_) {
      getpos = w_ - 1;
    }
    if (getpos < 0) {
      getpos = 0;
    }
    
    std::memcpy(dst.imgdat(i + dstbox.x(), dstYPos),
                imgdat(getpos, srcYPos),
                bytesPerPixel);
    
//    Color srccolor = getPixel(getpos,
//                              srcYPos);
    
//    dst.setPixel(i + dstbox.x(),
//                 dstYPos,
//                 srccolor);
  }
}
                 
void Graphic::blitOrCopyInternal(const Graphic& src,
                        Box dstbox,
                        Box srcbox,
                        TransBlitOption updateTrans,
                        CopyOrBlitCommand command) {
  // If either source dimension is invalid, blit whole surface
  if ((srcbox.w() <= 0)
      || (srcbox.h() <= 0)) {
    srcbox = Box(srcbox.x(),
                 srcbox.y(),
                 src.w_ - srcbox.x(),
                 src.h_ - srcbox.y());
  }
  
  // If either destination dimension is invalid, blit to whole surface
  if ((dstbox.w() <= 0)
      || (dstbox.h() <= 0)) {
    dstbox = Box(dstbox.x(),
                 dstbox.y(),
                 w_ - dstbox.x(),
                 h_ - dstbox.y());
  }
  
  // Remember original box x and y position (if negative, we will need
  // to use this to properly crop the image data later -- box::clip()
  // shifts the box to its "logical" position within the grid)
  int dstXOffset = -(dstbox.x());
  if (dstXOffset < 0) {
    dstXOffset = 0;
  }
  int dstYOffset = -(dstbox.y());
  if (dstYOffset < 0) {
    dstYOffset = 0;
  }
  
//  int srcXOffset = -(srcbox.x());
//  if (srcXOffset < 0) {
//    srcXOffset = 0;
//  }
//  int srcYOffset = -(srcbox.y());
//  if (srcYOffset < 0) {
//    srcYOffset = 0;
//  }
  
  // Clip srcbox to fit within dimensions
  srcbox.clip(Box(0, 0, src.w(), src.h()));
  
  // Return if srcbox doesn't intersect source graphic
  if ((srcbox.w() <= 0)
      || (srcbox.h() <= 0)) {
    return;
  }
  
  // Clip dstbox to fit within dimensions
  dstbox.clip(Box(0, 0, w_, h_));
  
  // Return if dstbox doesn't intersect with us
  if ((dstbox.w() <= 0)
      || (dstbox.h() <= 0)) {
    return;
  }
  
//  std::cout << "src: " << srcbox.x() << " " << srcbox.y()
//    << " " << srcbox.w() << " " << srcbox.h() << std::endl;
  
//  std::cout << "dst: " << dstbox.x() << " " << dstbox.y()
//    << " " << dstbox.w() << " " << dstbox.h() << std::endl;
  
  // Get source data pointer
  const Tbyte* getpos = src.const_imgdat(srcbox.x() + dstXOffset,
                                         srcbox.y() + dstYOffset);
  
  // Get starting position to place copied data
  Tbyte* putpos = imgdat(dstbox.x(),
                         dstbox.y());
                  
  // Get starting position in source transparency model
  const char* transgetpos
    = src.transModel_.const_model(srcbox.x() + dstXOffset,
                                  srcbox.y() + dstYOffset);
                  
  // Get starting position to place copied transparency model data
  char* transputpos
    = transModel_.model(dstbox.x(), dstbox.y());
  
  // Compute the number of rows and columns to copy, accounting for any
  // data which may be to the left of or above the blit area
  int rowsToCopy = std::min(srcbox.h() - dstYOffset,
                            dstbox.h());
  int columnsToCopy = std::min(srcbox.w() - dstXOffset,
                               dstbox.w());
                
  // Return if nothing to copy
  if ((rowsToCopy <= 0)
      || (columnsToCopy <= 0)) {
    return;
  }
  
  switch (command) {
  case blitCommand:
    blitInternal(rowsToCopy,
                 columnsToCopy,
                 src.bytesPerRow(),
                 src.transModel_.bytesPerRow(),
                 putpos,
                 getpos,
                 transputpos,
                 transgetpos);
    break;
  case copyCommand:
    copyInternal(rowsToCopy,
                 columnsToCopy,
                 src.bytesPerRow(),
                 src.transModel_.bytesPerRow(),
                 putpos,
                 getpos,
                 transputpos,
                 transgetpos);
    break;
  default:
    break;
  }
  
  // Copy transparency data
//  transModel_.copy(src.transModel_,
//                   srcbox,
//                   dstbox);
  
  if (updateTrans) {
    // Update transparency data
    transModel_.update(Box(dstbox.x(),
                           dstbox.y(),
                           rowsToCopy,
                           columnsToCopy));
  }
}
                 
void Graphic::blitOrCopyWrapInternal(const Graphic& src,
                        Box dstbox,
                        Box srcbox,
                        TransBlitOption updateTrans,
                        CopyOrBlitWrapCommand command) {
  // If either source dimension is invalid, blit whole surface
  if ((srcbox.w() <= 0)
      || (srcbox.h() <= 0)) {
    srcbox = Box(srcbox.x(),
                 srcbox.y(),
                 src.w_ - srcbox.x(),
                 src.h_ - srcbox.y());
  }
  
  // If either destination dimension is invalid, blit to whole surface
/*  if ((dstbox.w() <= 0)
      || (dstbox.h() <= 0)) {
    dstbox = Box(dstbox.x(),
                 dstbox.y(),
                 w_ - dstbox.x(),
                 h_ - dstbox.y());
  } */
  
  // If area of source to be blitted does not extend past right or bottom
  // of image, just do a regular blit and return
  if ((dstbox.x() + srcbox.w() < w_)
      && (dstbox.y() + srcbox.h() < h_)) {
    blit(src, dstbox, srcbox, updateTrans);
    return;
  }
              
  // Split blit into 4 subquadrants
  
  // Upper-left
  Box dstUL(dstbox.x(), dstbox.y(), srcbox.w(), srcbox.h());
  dstUL.clip(Box(0, 0, w_, h_));
  Box srcUL(srcbox);
  srcUL.clip(Box(0, 0, dstUL.w(), dstUL.h()));
  
  // Upper-right
  Box dstUR(0, dstUL.y(),
            srcbox.w() - dstUL.w(),
            dstUL.h());
  dstUR.clip(Box(0, 0, w_, h_));
  Box srcUR(srcbox.x() + srcUL.w(),
            srcbox.y(),
            srcbox.w() - srcUL.w(),
            srcUL.h());
  
  // Lower-left
  Box dstLL(dstbox.x(), 0,
            dstUL.w(),
            srcbox.h() - dstUL.h());
  dstLL.clip(Box(0, 0, w_, h_));
  Box srcLL(srcbox.x(),
            srcbox.y() + srcUL.h(),
            srcUL.w(),
            srcbox.h() - srcUL.h());
  
  // Lower-right
  Box dstLR(0, 0,
            srcbox.w() - dstUL.w(),
            srcbox.h() - dstUL.h());
  dstLR.clip(Box(0, 0, w_, h_));
  Box srcLR(srcbox.x() + srcUL.w(),
            srcbox.y() + srcUL.h(),
            srcbox.w() - srcUL.w(),
            srcbox.h() - srcUL.h());
  
  // Blit all boxes with a nonzero dimension
  switch (command) {
  case blitWrapCommand:
    if ((dstUL.w() != 0)
        && (dstUL.h() != 0)) {
      blit(src, dstUL, srcUL, updateTrans);
    }
    
    if ((dstUR.w() != 0)
        && (dstUR.h() != 0)) {
      blit(src, dstUR, srcUR, updateTrans);
    }
    
    if ((dstLL.w() != 0)
        && (dstLL.h() != 0)) {
      blit(src, dstLL, srcLL, updateTrans);
    }
    
    if ((dstLR.w() != 0)
        && (dstLR.h() != 0)) {
      blit(src, dstLR, srcLR, updateTrans);
    }
    break;
  case copyWrapCommand:
    if ((dstUL.w() != 0)
        && (dstUL.h() != 0)) {
      copy(src, dstUL, srcUL, updateTrans);
    }
    
    if ((dstUR.w() != 0)
        && (dstUR.h() != 0)) {
      copy(src, dstUR, srcUR, updateTrans);
    }
    
    if ((dstLL.w() != 0)
        && (dstLL.h() != 0)) {
      copy(src, dstLL, srcLL, updateTrans);
    }
    
    if ((dstLR.w() != 0)
        && (dstLR.h() != 0)) {
      copy(src, dstLR, srcLR, updateTrans);
    }
    break;
  default:
    break;
  }
}
                 
void Graphic::copyInternal(
                  int rowsToCopy,
                  int columnsToCopy,
                  int srcBytesPerRow,
                  int srcTransModelBytesPerRow,
                  Tbyte* putpos,
                  const Tbyte* getpos,
                  char* transputpos,
                  const char* transgetpos) {
  // Copy the pixel data
  for (int j = 0; j < rowsToCopy; j++) {
    // Copy the needed graphics from each row
    std::memcpy(putpos, getpos, columnsToCopy * bytesPerPixel);
    
    // Copy the needed transparency data from each row
    std::memcpy(transputpos,
                transgetpos,
                columnsToCopy * TransModel::bytesPerPixel);
    
    // Move to next row
    getpos += srcBytesPerRow;
    putpos += bytesPerRow();
    transgetpos += srcTransModelBytesPerRow;
    transputpos += transModel_.bytesPerRow();
  }
}
                 
void Graphic::blitInternal(int rowsToCopy,
                  int columnsToCopy,
                  int srcBytesPerRow,
                  int srcTransModelBytesPerRow,
                  Tbyte* putpos,
                  const Tbyte* getpos,
                  char* transputpos,
                  const char* transgetpos) {
//  std::cout << "rowsToCopy: " << rowsToCopy << std::endl;
//  std::cout << "columnsToCopy: " << columnsToCopy << std::endl;
  // Blit the pixel data
  for (int j = 0; j < rowsToCopy; j++) {
    int rowpos = 0;
    while (rowpos < columnsToCopy) {
      // Get number of pixels to copy or skip
      int numPixels = *(transgetpos + (rowpos * TransModel::bytesPerPixel));
      
//      std::cout << "rowpos: " << rowpos << std::endl;
//      std::cout << "numPixels: " << numPixels << std::endl;
      
      // Throw if the read value is zero (which is invalid)
      if (numPixels == 0) {
        throw TGenericException(
          TALES_SRCANDLINE,
          "Graphic::blit()",
          "Read zero from transparency array");
      }
      
      // <0: skip count
      if (numPixels < 0) {
        rowpos += std::abs(numPixels);
      }
      // >0: copy count
      else {
        // Don't copy more data than we can fit in the row
        if (rowpos + numPixels > columnsToCopy) {
          numPixels = columnsToCopy - rowpos;
        }
      
        // Copy graphic data
        std::memcpy(putpos + (rowpos * bytesPerPixel),
                    getpos + (rowpos * bytesPerPixel),
                    numPixels * bytesPerPixel);
        
        // Copy transparency data
        std::memcpy(transputpos + (rowpos * TransModel::bytesPerPixel),
                    transgetpos + (rowpos * TransModel::bytesPerPixel),
                    numPixels  * TransModel::bytesPerPixel);
        
        // Advance through columns
        rowpos += numPixels;
      }
    }
    
    // Move to next row
    getpos += srcBytesPerRow;
    putpos += bytesPerRow();
    transgetpos += srcTransModelBytesPerRow;
    transputpos += transModel_.bytesPerRow();
  }
}



};
