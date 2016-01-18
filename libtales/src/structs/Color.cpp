#include "structs/Color.h"

namespace Tales {


Color::Color()
 : a_(0),
   r_(0),
   g_(0),
   b_(0) { };

Color::Color(Tbyte r__,
      Tbyte g__,
      Tbyte b__,
      Tbyte a__)
  : a_(a__),
    r_(r__),
    g_(g__),
    b_(b__) { };

Color::Color(const Tbyte* src)
  : a_(src[3]),
    r_(src[2]),
    g_(src[1]),
    b_(src[0]) { };
        
Tbyte Color::a() const {
  return a_;
}

Tbyte Color::r() const {
  return r_;
}

Tbyte Color::g() const {
  return g_;
}

Tbyte Color::b() const {
  return b_;
}

void Color::setA(Tbyte a__) {
  a_ = a__;
}

void Color::setR(Tbyte r__) {
  r_ = r__;
}

void Color::setG(Tbyte g__) {
  g_ = g__;
}

void Color::setB(Tbyte b__) {
  b_ = b__;
}


};
