#ifndef RASTER_H
#define RASTER_H

#include "Color.h"
#include "Model.h"
#include "Triangle.h"
#include "Vector.h"
#include <iostream>
using namespace std;

class Raster {
private:
  int width;
  int height;
  Color *pixels;
  float *depthPixels;

public:
  Raster();
  Raster(int pWidth, int pHeight, Color pFillColor);
  ~Raster();
  int getWidth();
  int getHeight();
  float getDepthPixel(int x, int y);
  Color getColorPixel(int x, int y);
  void setDepthPixel(int x, int y, float depth);
  void setColorPixel(int x, int y, Color pFillColor);
  void clear(float depth);
  void clear(Color pFillColor);
  void writeToPPM();
  void drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor);
  void swap(float &x1, float &y1, float &x2, float &y2);
  bool inRange(float x, float y);

  void drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2,
                                 Color color1, Color color2);
  void drawTriangle2D_DotProduct(Triangle2D triangle2D);
  void drawTriangle3D_Barycentric(Triangle3D T);
  void drawModel(Model m);
};

#endif // RASTER_H