#ifndef BOX_H
#define BOX_H


namespace Tales {


/**
 * Class representing a box with an x-position, y-position, width, and height.
 */
class Box {
public:
  
  /** 
   * Default constructor.
   * Initializes all field to 0.
   */
  Box();
  
  /** 
   * Constructor.
   * Creates a box of the specified x- and y-positions, width, and height.
   * @param x__ Box x-position.
   * @param y__ Box y-position.
   * @param w__ Box width.
   * @param w__ Box height.
   */
  Box(int x__, int y__, int w__, int h__);
  
  /** 
   * X-position getter.
   * @return Box x-position.
   */
  int x() const;
  
  /** 
   * Y-position getter.
   * @return Box y-position.
   */
  int y() const;
  
  /** 
   * Width getter.
   * @return Box width.
   */
  int w() const;
  
  /** 
   * Height getter.
   * @return Box height.
   */
  int h() const;
  
  void setX(int x__);
  void setY(int y__);
  void setW(int w__);
  void setH(int h__);
  
  /** 
   * Clips this box to only the area intersecting with another box.
   * @param srcbox The Box used as reference for clipping this one.
   */
  void clip(const Box& srcbox);
  
  bool pointOverlaps(int pointX, int pointY);
  
  bool boxOverlaps(Box box);
  
protected:

  /** 
   * Box x-position.
   */
  int x_;

  /** 
   * Box y-position.
   */
  int y_;

  /** 
   * Box width.
   */
  int w_;

  /** 
   * Box height.
   */
  int h_;
  
  /** 
   * Clips this box's x and w to only the area intersecting with another box.
   * @param srcbox The Box used as reference for clipping this one.
   */
//  void clipX(const Box& srcbox);
  
  /** 
   * Clips this box's y and h to only the area intersecting with another box.
   * @param srcbox The Box used as reference for clipping this one.
   */
//  void clipY(const Box& srcbox); 
  
  /** 
   * Generic function to clip one of a box's axes.
   * @param axis Reference to the axis to update (x or y position).
   * @param length Reference to the length to update (width or height).
   * @param srcAxis The value of the axis for comparison (x or y position).
   * @param srcLength The value of the length for comparison (width or height).
   */
  void clipAxis(int& axis,
                int& length,
                int srcAxis,
                int srcLength);
  
};


};


#endif 
