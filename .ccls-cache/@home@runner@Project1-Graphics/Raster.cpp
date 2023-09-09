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
  int target = width * (height - 1 - y) + x;
  pixels[target] = pFillColor;
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

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor) {
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

void Raster::swap(float& x1, float& y1, float& x2, float& y2) {
  float tempX = x1;
  x1 = x2;
  x2 = tempX;
  float tempY = y1;
  y1 = y2;
  y2 = tempY;
}

