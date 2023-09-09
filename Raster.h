#ifndef RASTER_H
#define RASTER_H

#include "Color.h"
#include <iostream>
using namespace std;

class Raster {
private:
  int width;
  int height;
  Color *pixels;

public:
  Raster();
  Raster(int pWidth, int pHeight, Color pFillColor);
  ~Raster();
  int getWidth();
  int getHeight();
  Color getColorPixel(int x, int y);
  void setColorPixel(int x, int y, Color pFillColor);
  void clear(Color pFillColor);
  void writeToPPM();
  void drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor);
  void swap(float& x1, float& y1, float& x2, float& y2);
};

#endif // RASTER_H