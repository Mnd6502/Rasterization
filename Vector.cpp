#include "Vector.h"
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

// Vector4 

Vector4::Vector4(){
  x= 0.0;
  y = 0.0;
  z = 0.0;
  w = 0.0;
}

Vector4::Vector4(float pX, float pY, float pZ, float pW) {
  x = pX;
  y = pY;
  z = pZ;
  w = pW;
}

Vector4 Vector4::operator*(const float scale) {
  Vector4 vector4;
  vector4.x = this->x * scale;
  vector4.y = this->y * scale;
  vector4.z = this->z * scale;
  vector4.w = this->w * scale;
  return vector4;
}

Vector4 Vector4::operator+(const Vector4 &b){
  Vector4 vector4;
  vector4.x = this->x + b.x;
  vector4.y = this->y + b.y;
  vector4.z = this->z + b.z;
  vector4.w = this->w + b.w;
  return vector4;
}

Vector4 Vector4::operator-(const Vector4 &c) {
  Vector4 vector4;
  vector4.x = this->x - c.x;
  vector4.y = this->y - c.y;
  vector4.z = this->z - c.z;
  vector4.w = this->w - c.w;
  return vector4;
}

float Vector4::magnitude(){
  return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

Vector4 Vector4::normalize() {
  Vector4 vector4;
  float mag = magnitude();
  vector4.x = this->x / mag;
  vector4.y = this->y / mag;
  vector4.z = this->z / mag;
  vector4.w = this->w;
  return vector4;
}

float Vector4::dot(Vector4 v){
  return this->x*v.x + this->y*v.y + this->z*v.z + this->w*v.w;
}