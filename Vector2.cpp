#include "Vector2.h"
#include <iostream>
#include <cmath>

using namespace std;

Vector2::Vector2(){
  x= 0.0;
  y = 0.0;
}

Vector2::Vector2(float pX, float pY) {
  x = pX;
  y = pY;
}

Vector2 Vector2::operator*(const float scale) {
  Vector2 vector2;
  vector2.x = this->x * scale;
  vector2.y = this->y * scale;
  return vector2;
}

Vector2 Vector2::operator+(const Vector2 &b){
  Vector2 vector2;
  vector2.x = this->x + b.x;
  vector2.y = this->y + b.y;
  return vector2;
}

Vector2 Vector2::operator-(const Vector2 &c) {
  Vector2 vector2;
  vector2.x = this->x - c.x;
  vector2.y = this->y - c.y;
  return vector2;
}

float Vector2::magnitude(){
  return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

float Vector2::dot(Vector2 v){
  return this->x*v.x + this->y*v.y;
}

Vector2 Vector2::normalize() {
  Vector2 vector2;
  float mag = magnitude();
  vector2.x = this->x / mag;
  vector2.y = this->y / mag;
  return vector2;
}

Vector2 Vector2::perpendicular(){
  Vector2 vector2;
  vector2.x = this->y * (-1);
  vector2.y = this->x;
  return vector2;
}

float determinant(Vector2 a, Vector2 b) {
  return b.x*a.y - a.x*b.y;
}