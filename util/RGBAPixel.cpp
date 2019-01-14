/*
 * This file's base code was obtained from my data structures and algorithms course
 * and changes have been made to support the functionlity for this project.
 */

#include "RGBAPixel.h"
#include <cmath>
#include <iostream>

using namespace std;

namespace util {
  RGBAPixel::RGBAPixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }
  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  RGBAPixel & RGBAPixel::operator=(RGBAPixel const & other) {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
    return *this;
  }

  bool RGBAPixel::operator== (RGBAPixel const & other) const {
    if ( a == 0 ) { return true; }
    if (fabs(a - other.a) > 0.01) { return false; }

    if (fabs(r - other.r) > 2) { return false; } 
    if (fabs(g - other.g) > 2) { return false; } 
    if (fabs(b - other.b) > 2) { return false; } 

    return true;
}

  bool RGBAPixel::operator!= (RGBAPixel const & other) const {
    return !(*this == other);
  }

  bool RGBAPixel::operator<  (RGBAPixel const & other) const {
    // order is reflected here. R->G->B.
    if (*this == other) { return false; }

    if (r < other.r)
        return true;
    else if ((r == other.r) && (g < other.g))
        return true;
    else if ((r == other.r) && (g == other.g) && (b < other.b))
        return true;

    return false;
  }

  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel) {
    out << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }
}