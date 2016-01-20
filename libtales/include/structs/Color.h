#ifndef COLOR_H
#define COLOR_H


#include "structs/Tbyte.h"

namespace Tales {


/**
 * A color with 8-bit ARGB components.
 */
class Color {
public:
  /**
   * Alpha value for full opacity.
   */
  const static int fullAlphaOpacity = 0xFF;
  
  /**
   * Alpha value for full transparency.
   */
  const static int fullAlphaTransparency = 0x00;

  /**
   * Default constructor.
   * Initializes to pure black (all components zero).
   */
  Color();
  
  /**
   * Constructor.
   * Initializes to the specified color. Alpha defaults to zero
   * (full opacity) if unspecified.
   * @param r__ 8-bit red component.
   * @param g__ 8-bit green component.
   * @param b__ 8-bit blue component.
   * @param a__ 8-bit alpha component. Zero if unspecified.
   */
  Color(Tbyte r__,
        Tbyte g__,
        Tbyte b__,
        Tbyte a__ = 0);
  
  /**
   * Array-based constructor.
   * Initializes from an array of at least 4 bytes which species the ARGB
   * components of the color in that order.
   * @param src Const pointer to array of at least 4 bytes forming ARGB color.
   */
  Color(const Tbyte* src);
        
  /**
   * Getter for alpha component.
   * @return Alpha component of color.
   */
  Tbyte a() const;
        
  /**
   * Getter for red component.
   * @return Red component of color.
   */
  Tbyte r() const;
        
  /**
   * Getter for green component.
   * @return Green component of color.
   */
  Tbyte g() const;
        
  /**
   * Getter for blue component.
   * @return Blue component of color.
   */
  Tbyte b() const;
        
  /**
   * Setter for alpha component.
   * @param a__ New alpha component.
   */
  void setA(Tbyte a__);
        
  /**
   * Setter for red component.
   * @param r__ New red component.
   */
  void setR(Tbyte r__);
        
  /**
   * Setter for green component.
   * @param g__ New green component.
   */
  void setG(Tbyte g__);
        
  /**
   * Setter for blue component.
   * @param b__ New blue component.
   */
  void setB(Tbyte b__);
   
protected:

  /**
   * 8-bit alpha component.
   */
  Tbyte a_;
  
  /**
   * 8-bit red component.
   */
  Tbyte r_;
  
  /**
   * 8-bit green component.
   */
  Tbyte g_;
  
  /**
   * 8-bit blue component.
   */
  Tbyte b_;
  
};


};


#endif 
