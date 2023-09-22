#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
using namespace std;

struct Vector2 {
  float x;
  float y;

  Vector2();
  Vector2(float pX, float pY);
  Vector2 operator*(const float scale);
  Vector2 operator+(const Vector2 &b);
  Vector2 operator-(const Vector2 &c);

  float magnitude();
  float dot(Vector2 v);
  Vector2 normalize();
  Vector2 perpendicular();

};

float determinant(Vector2 a, Vector2 b);
#endif // VECTOR2_H

// Hi , I am waiting to get take-away food so I will come later
// OKELA MINH DO