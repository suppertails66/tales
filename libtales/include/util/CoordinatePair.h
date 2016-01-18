#ifndef COORDINATEPAIR_H
#define COORDINATEPAIR_H


namespace Luncheon {


class CoordinatePair {
public:
  virtual ~CoordinatePair();

  CoordinatePair();
  CoordinatePair(int x__, int y__);

  virtual int x() const;
  virtual void setX(int x__);

  virtual int y() const;
  virtual void setY(int y__);

protected:
  int x_;
  int y_;
};


};


#endif 
