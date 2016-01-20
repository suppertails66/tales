#ifndef GGCOLOR_H
#define GGCOLOR_H


namespace Tales {


/**
 * Representation of a Game Gear color.
 */
class GGColor {
public:
  /**
   * Constructor.
   * Initializes to 000000 (pure black).
   */
	GGColor();
	
  /**
   * Destructor.
   */
	~GGColor();
	
  /**
   * Returns the color in native 16-bit Game Gear color format.
   * The format of the color is xxxxbbbbggggrrrr, where
   * r = red, g = green, b = blue, and x = unused
   * @return The native Game Gear color value for this color.
   */
	int nativeColor() const;
	
  /**
   * Returns the true 8-bit red component of this color.
   * @return The true 8-bit red component of this color.
   */
	int realR() const;
	
  /**
   * Returns the true 8-bit green component of this color.
   * @return The true 8-bit green component of this color.
   */
	int realG() const;
	
  /**
   * Returns the true 8-bit blue component of this color.
   * @return The true 8-bit blue component of this color.
   */
	int realB() const;

  /**
   * Sets the color to the given native Game Gear color value.
   * @param color A 16-bit native Game Gear color value.
   */
	void setNativeColor(int color);

  /**
   * Sets the color to the given RGB value.
   * @param r The true 8-bit red component of the new value.
   * @param g The true 8-bit green component of the new value.
   * @param b The true 8-bit blue component of the new value.
   */
	void setRGB(int r, int g, int b);

protected:

  /**
   * The native Game Gear format value of the color.
   */
	int nativeColor_;

  /**
   * The true 8-bit red component of the color.
   */
	int realR_;

  /**
   * The true 8-bit green component of the color.
   */
	int realG_;

  /**
   * The true 8-bit blue component of the color.
   */
	int realB_;

};


};


#endif
