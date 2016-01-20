#ifndef INPUTEVENTDATA_H
#define INPUTEVENTDATA_H


namespace Tales {


class InputEventData {
public:
  InputEventData();
  
  int x();
  void setX(int x__);
  
  int y();
  void setY(int y__);

  bool mouseLeftButton();
  void setMouseLeftButton(bool mouseLeftButton__);

  bool mouseRightButton();
  void setMouseRightButton(bool mouseRightButton__);

  bool mouseMiddleButton();
  void setMouseMiddleButton(bool mouseMiddleButton__);
  
  bool control();
  void setControl(bool control__);
  
  bool alt();
  void setAlt(bool alt__);
  
  bool shift();
  void setShift(bool shift__);

protected:
  int x_;
  int y_;

  bool mouseLeftButton_;
  bool mouseMiddleButton_;
  bool mouseRightButton_;
  
  bool control_;
  bool alt_;
  bool shift_;
  
};


};


#endif
