#ifndef AREAMAPREFERENCE_H
#define AREAMAPREFERENCE_H


namespace Tales {


class AreaMapReference {
public:
  AreaMapReference();
  
  AreaMapReference(int areaNum__,
                   int mapNum__);
  
  int areaNum() const;
  int mapNum() const;
  
  void setAreaNum(int areaNum__);
  void setMapNum(int mapNum__);
protected:
  int areaNum_;
  int mapNum_;
};


};


#endif
