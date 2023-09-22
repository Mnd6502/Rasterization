#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "Vector2.h"
#include "Color.h"
#include <iostream>
using namespace std;

struct Triangle2D {
  Vector2 v1, v2, v3;
  Color c1, c2, c3;

  Triangle2D();  
  Triangle2D(Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3);
  bool inside(float x, float y);
  void calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3); 
};


#endif // TRIANGLE2D_H