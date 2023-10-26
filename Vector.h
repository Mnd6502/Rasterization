#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

struct Vector2
{
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

struct Vector4
{
  float x;
  float y;
  float z;
  float w;

  Vector4();
  Vector4(float pX, float pY, float pZ, float pW);
  Vector4 operator*(const float scale);
  Vector4 operator+(const Vector4 &b);
  Vector4 operator-(const Vector4 &c);

  float magnitude();
  float dot(Vector4 v);
  Vector4 normalize();
  Vector4 perpendicular();
  void print();
};

float determinant(Vector2 a, Vector2 b);

#endif // VECTOR_H
