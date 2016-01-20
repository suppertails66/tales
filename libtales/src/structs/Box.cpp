#include "structs/Box.h"
#include <iostream>

namespace Tales {


Box::Box()
  : x_(0),
    y_(0),
    w_(0),
    h_(0) { };

Box::Box(int x__, int y__, int w__, int h__)
  : x_(x__),
    y_(y__),
    w_(w__),
    h_(h__) { };

int Box::x() const {
  return x_;
}

int Box::y() const {
  return y_;
}

int Box::w() const {
  return w_;
}

int Box::h() const {
  return h_;
}
  
void Box::setX(int x__) {
  x_ = x__;
}

void Box::setY(int y__) {
  y_ = y__;
}

void Box::setW(int w__) {
  w_ = w__;
}

void Box::setH(int h__) {
  h_ = h__;
}


void Box::clip(const Box& srcbox) {
  // Clip in X
  clipAxis(x_, w_, srcbox.x(), srcbox.w());
  
  // Clip in Y
  clipAxis(y_, h_, srcbox.y(), srcbox.h());
}
  
bool Box::pointOverlaps(int pointX, int pointY) {
  if (pointX < x_) { return false; }
  if (pointY < y_) { return false; }
  if (pointX >= (x_ + w_)) { return false; }
  if (pointY >= (y_ + h_)) { return false; }
  
  return true;
}
  
bool Box::boxOverlaps(Box box) {
  if (pointOverlaps(box.x(), box.y())) { return true; }
  if (pointOverlaps(box.x() + box.w(), box.y())) { return true; }
  if (pointOverlaps(box.x(), box.y() + box.h())) { return true; }
  if (pointOverlaps(box.x() + box.w(), box.y() + box.h())) { return true; }
  
  if (box.pointOverlaps(x_, y_)) { return true; }
  if (box.pointOverlaps(x_ + w_, y_)) { return true; }
  if (box.pointOverlaps(x_, y_ + h_)) { return true; }
  if (box.pointOverlaps(x_ + w_, y_ + h_)) { return true; }
  
  return false;
}

/*void Box::clipX(const Box& srcbox) {
  // Get the x-position of the right edge of srcbox
  int srcboxR = srcbox.x() + srcbox.w();
  
  // Get the x-position of the right edge of this box
  int thisboxR = x_ + w_;
  
  // If this box's width is wholly enclosed by the box's, there's nothing to do
  if ((srcbox.x() <= x_)
      && (srcboxR > thisboxR)) {
    return;
  }
  
  // If right side of srcbox does not clip, no intersection
  if (srcboxR < x_) {
    x_ = 0;
    w_ = 0;
    return;
  }
  
  // If left side of srcbox does not clip, no intersection
  if (srcbox.x() >= thisboxR) {
    x_ = 0;
    w_ = 0;
    return;
  }
  
  // If srcbox's left side is left of this box's, clip right side of this box
  if (srcbox.x() <= x_) {
    // X position remains the same, but width decreases
    // by the distance between the right edges of the boxes
    w_ -= (srcboxR - thisboxR);
  }
  // If srcbox's left side is right of this box's, clip left side of this box
  else {
    
    // Remember number of pixels to remove from left side
    int leftPixelsToClip = srcbox.x() - x_;
    // Move left side of box to match srcbox
    x_ = srcbox.x();
    // Decrease width accordingly
    w_ -= leftPixelsToClip;
    
    // Compute the number of pixels to clip from the right side of this box
    int rightPixelsToClip = thisboxR - srcboxR;
    
    // Never increase the size of this box
    if (rightPixelsToClip <= 0) {
      return;
    }
    
    // Clip right side of this box
    w_ -= rightPixelsToClip;
  }
}

void Box::clipY(const Box& srcbox) {

} */


void Box::clipAxis(int& axis,
                   int& length,
                   int srcAxis,
                   int srcLength) {
  // Get the x-position of the right edge of srcbox
  int srcboxR = srcAxis + srcLength;
  
  // Get the x-position of the right edge of this box
  int thisboxR = axis + length;
  
  // If this box's width is wholly enclosed by the box's, there's nothing to do
  if ((srcAxis <= axis)
      && (srcboxR > thisboxR)) {
    return;
  }
  
  // If right side of srcbox does not clip, no intersection
  if (srcboxR < axis) {
    axis = 0;
    length = 0;
    return;
  }
  
  // If left side of srcbox does not clip, no intersection
  if (srcAxis >= thisboxR) {
    axis = 0;
    length = 0;
    return;
  }
  
//   std::cout << "axis: " << axis << std::endl;
//   std::cout << "length: " << length << std::endl;
//   std::cout << "srcAxis: " << srcAxis << std::endl;
//   std::cout << "srcLength: " << srcLength << std::endl;
//   std::cout << "thisboxR: " << thisboxR << std::endl;
//   std::cout << "srcboxR: " << srcboxR << std::endl;
  
  // If srcbox's left side is left of this box's, clip right side of this box
  if (srcAxis <= axis) {
//    std::cout << "clip distance: " << (thisboxR - srcboxR) << std::endl;
    // X position remains the same, but width decreases
    // by the distance between the right edges of the boxes
    length -= (thisboxR - srcboxR);
  }
  // If srcbox's left side is right of this box's, clip left side of this box
  else {
    
    // Remember number of pixels to remove from left side
    int leftPixelsToClip = srcAxis - axis;
    // Move left side of box to match srcbox
    axis = srcAxis;
    // Decrease width accordingly
    length -= leftPixelsToClip;
    
//    std::cout << "leftPixelsToClip: " << leftPixelsToClip << std::endl;
//    std::cout << "axis: " << axis << std::endl;
//    std::cout << "length: " << length << std::endl;
    
    // Compute the number of pixels to clip from the right side of this box
    int rightPixelsToClip = thisboxR - srcboxR;
    
    // Never increase the size of this box
    if (rightPixelsToClip <= 0) {
      return;
    }
    
    // Clip right side of this box
    length -= rightPixelsToClip;
  }
}



}; 
