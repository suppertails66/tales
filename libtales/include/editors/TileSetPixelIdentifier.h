#ifndef TILESETPIXELIDENTIFIER_H
#define TILESETPIXELIDENTIFIER_H


namespace Tales {


class TileSetPixelIdentifier {
public:
  TileSetPixelIdentifier();
  TileSetPixelIdentifier(int tileNum__, int x__, int y__);
  
  int tileNum() const;
  int x() const;
  int y() const;
  
  void setTileNum(int tileNum__);
  void setX(int x__);
  void setY(int y__);
protected:
  int tileNum_;
  int x_;
  int y_;
};


};


#endif
