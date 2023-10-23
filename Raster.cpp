#include "Raster.h"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

Raster::Raster() {
  width = 0;
  height = 0;
  pixels = NULL;
}

Raster::Raster(int pWidth, int pHeight, Color pFillColor) {
  width = pWidth;
  height = pHeight;
  pixels = new Color[width * height];
  for (int i = 0; i < width * height; i++) {
    pixels[i] = pFillColor;
  };
}

Raster::~Raster() { delete[] pixels; }

int Raster::getWidth() { return width; }

int Raster::getHeight() { return height; }

Color Raster::getColorPixel(int x, int y) {
  int target = width * (height - 1 - y) + x;
  return pixels[target];
}

void Raster::setColorPixel(int x, int y, Color pFillColor) {
  if (inRange(x, y)) {
    int target = width * (height - 1 - y) + x;
    pixels[target] = pFillColor;
  }
}

void Raster::clear(Color pFillColor) {
  for (int i = 0; i < width * height; i++) {
    pixels[i] = pFillColor;
  }
}

void Raster::writeToPPM() {
  ofstream MyFile("FRAME_BUFFER.ppm");

  MyFile << "P3" << endl;
  MyFile << width << " " << height << endl;
  MyFile << 255 << endl;

  for (int i = 0; i < width * height; i += width) {
    for (int j = i; j < i + width; j++) {
      Color pixel = pixels[j];
      MyFile << (int)round(pixel.red * 255) << " "
             << (int)round(pixel.green * 255) << " "
             << (int)round(pixel.blue * 255) << " ";
    }
    MyFile << endl;
  }
  MyFile.close();
}

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2,
                          Color fillColor) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  float m;
  if (dx == 0) {
    if (y2 < y1) {
      swap(x1, y1, x2, y2);
    }
    float x = x2;
    for (int y = round(y2); y >= round(y1); y--) {
      setColorPixel(x, y, fillColor);
    }
  } else {
    m = dy / dx;
    if (abs(m) <= 1) {
      if (x1 > x2) {
        swap(x1, y1, x2, y2);
      }
      float y = y1;
      for (int x = round(x1); x <= round(x2); x++) {
        setColorPixel(x, round(y), fillColor);
        y += m;
      }
    } else if (abs(m) > 1) {
      if (y2 < y1) {
        swap(x1, y1, x2, y2);
      }
      float x = x2;
      m = 1.0 / m;
      for (int y = round(y2); y >= round(y1); y--) {
        setColorPixel(round(x), y, fillColor);
        x -= m;
      }
    }
  }
}

void Raster::swap(float &x1, float &y1, float &x2, float &y2) {
  float tempX = x1;
  x1 = x2;
  x2 = tempX;
  float tempY = y1;
  y1 = y2;
  y2 = tempY;
}

bool Raster::inRange(float x, float y) {
  return (x >= 0) && (x < width) && (y >= 0) && (y < height);
}

void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2,
                                       Color color1, Color color2) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  float m;
  float p;
  if (dx == 0) {
    if (y2 < y1) {
      swap(x1, y1, x2, y2);
      Color temp = color1;
      color1 = color2;
      color2 = temp;
    }
    float x = x2;
    for (int y = round(y2); y >= round(y1); y--) {
      p = (y2 - y) / (y2 - y1);
      Color newColor = color1 * p + color2 * (1 - p);
      setColorPixel(x, y, newColor);
    }
  } else {
    m = dy / dx;
    if (abs(m) <= 1) {
      if (x1 > x2) {
        swap(x1, y1, x2, y2);
        Color temp = color1;
        color1 = color2;
        color2 = temp;
      }
      float y = y1;
      for (int x = round(x1); x <= round(x2); x++) {
        p = (x - x1) / (x2 - x1);
        Color newColor = color2 * p + color1 * (1 - p);
        setColorPixel(x, y, newColor);
        y += m;
      }
    } else if (abs(m) > 1) {
      if (y2 < y1) {
        swap(x1, y1, x2, y2);
        Color temp = color1;
        color1 = color2;
        color2 = temp;
      }
      float x = x2;
      m = 1.0 / m;
      for (int y = round(y2); y >= round(y1); y--) {
        p = (y2 - y) / (y2 - y1);
        Color newColor = color1 * p + color2 * (1 - p);
        setColorPixel(x, y, newColor);
        x -= m;
      }
    }
  }
}

void Raster::drawTriangle2D_DotProduct(Triangle2D triangle2D) {
  float minX = min(triangle2D.v1.x, min(triangle2D.v2.x, triangle2D.v3.x));
  float maxX = max(triangle2D.v1.x, max(triangle2D.v2.x, triangle2D.v3.x));
  float minY = min(triangle2D.v1.y, min(triangle2D.v2.y, triangle2D.v3.y));
  float maxY = max(triangle2D.v1.y, max(triangle2D.v2.y, triangle2D.v3.y));
  for (int x = round(minX); x <= round(maxX); x++) {
    for (int y = round(minY); y <= round(maxY); y++) {
      if (triangle2D.inside(x, y)) {
        setColorPixel(x, y, triangle2D.c1);
      }
    }
  }
}

void Raster::drawTriangle3D_Barycentric(Triangle3D T) {
  Triangle2D myTri = Triangle2D(T);
  float minX = min(T.v1.x, min(T.v2.x, T.v3.x));
  float maxX = max(T.v1.x, max(T.v2.x, T.v3.x));
  float minY = min(T.v1.y, min(T.v2.y, T.v3.y));
  float maxY = max(T.v1.y, max(T.v2.y, T.v3.y));
  float lambda1, lambda2, lambda3;
  for (int x = round(minX); x <= round(maxX); x++) {
    for (int y = round(minY); y <= round(maxY); y++) {
      myTri.calculateBarycentricCoordinates(Vector2(x, y), lambda1, lambda2, lambda3);
      if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
        Color newColor = T.c1 * lambda1 + T.c2 * lambda2 + T.c3 * lambda3;
        setColorPixel(x, y, newColor);
      }
    }
  }
}