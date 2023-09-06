#include "Color.h"
#include <cmath>
#include <iostream>
using namespace std;

Color::Color() {
  red = 0.0;
  green = 0.0;
  blue = 0.0;
}

Color::Color(float pRed, float pGreen, float pBlue) {
  red = pRed;
  green = pGreen;
  blue = pBlue;
  clamp();
}

void Color::clamp() {
  red = fmin(fmax(red, 0), 1);
  green = fmax(green, 0);
  green = fmin(green, 1);
  blue = fmax(blue, 0);
  blue = fmin(blue, 1);
}

Color Color::operator+(const Color &b) {
  Color color;
  color.red = this->red + b.red;
  color.green = this->green + b.green;
  color.blue = this->blue + b.blue;
  color.clamp();
  return color;
}

Color Color::operator-(const Color &c) {
  Color color;
  color.red = this->red - c.red;
  color.green = this->green - c.green;
  color.blue = this->blue - c.blue;
  color.clamp();
  return color;
}

Color Color::operator*(const float scale) {
  Color color;
  color.red = this->red * scale;
  color.green = this->green * scale;
  color.blue = this->blue * scale;
  color.clamp();
  return color;
}