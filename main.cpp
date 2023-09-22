#include "Raster.h"
#include "Vector2.h"
#include <iostream>
using namespace std;

void printVector(Vector2 v) {
  cout << v.x << "   " << v.y << endl;
}

int main() {
  // Vector2 v = Vector2(2,5);
  // Vector2 a = Vector2(3,1);
  // printVector(v + a);
  // printVector(v - a);
  // printVector(v * 2.0);
  // cout << "v dot a" << v.dot(a) << endl;
  // cout << "v's magnitude: " << v.magnitude() << endl;
  // printVector(v.normalize());
  // printVector(v.perpendicular());

  Raster raster = Raster(100, 100, White);
  // raster.drawLine_DDA_Interpolated(20, 20, 50, 70, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 120, 20, Red, Green);
  // raster.drawLine_DDA_Interpolated(20, 20, 20, 50, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 80, 40, Red, Green);
  // raster.drawLine_DDA_Interpolated(60, 40, 10, 70, Green, Red);
  // raster.drawLine_DDA_Interpolated(10, 70, 60, 40, Red, Green);
  Triangle2D triangle(Vector2(2, 15), Vector2(45, 80), Vector2(72, 10), Red, Green, Blue);
  raster.drawTriangle_Barycentric(triangle);
  raster.writeToPPM();
}