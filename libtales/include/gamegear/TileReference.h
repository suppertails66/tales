#ifndef TILEREFERENCE_H
#define TILEREFERENCE_H


namespace Tales {


/**
 * A reference to a tile in VRAM.
 * Includes mirroring flags.
 */
class TileReference {
public:
  /**
   * Horizontal mirroring enum.
   */
  enum HorizontalMirroringOption {
    noHorizontalMirror = 0,   /**< Don't mirror horizontally. */
    horizontalMirror = 1      /**< Mirror horizontally. */
  };
  
  /**
   * Vertical mirroring enum.
   */
  enum VerticalMirroringOption {
    noVerticalMirror = 0,  /**< Don't mirror vertically. */
    verticalMirror = 1     /**< Mirror vertically. */
  };
  
  /**
   * Palette enum.
   */
  enum PaletteOption {
    palette0 = 0,   /**< First palette. */
    palette1 = 1    /**< Second palette. */
  };
  
  /**
   * Priority enum.
   */
  enum PriorityOption {
    priorityBG = 0,   /**< Priority: background. */
    priorityFG = 1    /**< Priority: foreground. */
  };

  /**
   * Default constructor.
   */
  TileReference();

  /**
   * Constructor from raw 16-bit VRAM identifier.
   * @param identifier 16-bit VRAM identifier.
   */
  TileReference(unsigned int identifier);
  
  /**
   * Constructor.
   * @param tileNum__ Number of the referenced tile.
   * @param horizontalMirroringOption__ Indicates whether the tile should be
   * flipped horizontally.
   * @param verticalMirroringOption__ Indicates whether the tile should be
   * flipped vertically.
   * @param paletteOption__ Indicates whether the tile uses palette 0 or 1.
   * @param priorityOption__ Indicates whether the tile has BG or FG priority.
   */
  TileReference(unsigned int tileNum__,
                HorizontalMirroringOption horizontalMirroringOption__,
                VerticalMirroringOption verticalMirroringOption__,
                PaletteOption paletteOption__,
                PriorityOption priorityOption__);
  
  /**
   * Returns the raw 16-bit VRAM identifier corresponding to a reference.
   * @return The raw 16-bit VRAM identifier corresponding to a reference.
   */
  unsigned int toRawIdentifier() const;

  /**
   * Getter.
   */
  unsigned int tileNum() const;

  /**
   * Getter.
   */
  HorizontalMirroringOption horizontalMirroringOption() const;

  /**
   * Getter.
   */
  VerticalMirroringOption verticalMirroringOption() const;

  /**
   * Getter.
   */
  PaletteOption paletteOption() const;

  /**
   * Getter.
   */
  PriorityOption priorityOption() const;
  
  /**
   * Setter.
   */
  void setTileNum(unsigned int tileNum__);
  
  /**
   * Setter.
   */
  void setHorizontalMirroringOption(
        HorizontalMirroringOption horizontalMirroringOption__);
  
  /**
   * Setter.
   */
  void setVerticalMirroringOption(
        VerticalMirroringOption verticalMirroringOption__);
  
  /**
   * Setter.
   */
  void setPaletteOption(
        PaletteOption paletteOption__);
  
  /**
   * Setter.
   */
  void setPriorityOption(
        PriorityOption priorityOption__);
  
protected:
  
  /**
   * Tile number shift.
   */
  const static int tileNumShift = 0;
  
  /**
   * Horizontal mirroring flag shift.
   */
  const static int horizontalMirroringShift = 9;
  
  /**
   * Vertical mirroring flag shift.
   */
  const static int verticalMirroringShift = 10;
  
  /**
   * Palette select shift.
   */
  const static int paletteShift = 11;
  
  /**
   * Priority flag shift.
   */
  const static int priorityShift = 12;
  
  /**
   * Tile number mask.
   */
  const static int tileNumMask
    = 0x1FF << tileNumShift;
  
  /**
   * Horizontal mirroring flag mask.
   */
  const static int horizontalMirroringMask
    = 0x1 << horizontalMirroringShift;
  
  /**
   * Vertical mirroring flag mask.
   */
  const static int verticalMirroringMask
    = 0x1 << verticalMirroringShift;
  
  /**
   * Palette select mask.
   */
  const static int paletteMask
    = 0x1 << paletteShift;
  
  /**
   * Priority flag mask.
   */
  const static int priorityMask
    = 0x1 << priorityShift;

  /**
   * The tile index in VRAM.
   */
  unsigned int tileNum_;
  
  /**
   * Horizontal mirroring flag.
   */
  HorizontalMirroringOption horizontalMirroringOption_;
  
  /**
   * Vertical mirroring flag.
   */
  VerticalMirroringOption verticalMirroringOption_;
  
  /**
   * Palette flag.
   */
  PaletteOption paletteOption_;
  
  /**
   * Priority flag.
   */
  PriorityOption priorityOption_;
  
};


};


#endif 
