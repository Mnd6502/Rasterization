#include "Matrix.h"

#include <iostream>
//#include <cmath>
using namespace std;

Matrix4::Matrix4() {
  ix = 1.0;
  iy = 0.0;
  iz = 0.0;
  iw = 0.0;
  jx = 0.0;
  jy = 1.0;
  jz = 0.0;
  jw = 0.0;
  kx = 0.0;
  ky = 0.0;
  kz = 1.0;
  kw = 0.0;
  ox = 0.0;
  oy = 0.0;
  ox = 0.0;
  ow = 1.0;
}

Matrix4::Matrix4(float ix, float jx, float kx, float ox, 
                 float iy, float jy, float ky, float oy, 
                 float iz, float jz, float kz, float oz,
                 float iw, float jw, float kw, float ow) {
  this->ix = ix;
  this->jx = jx;
  this->kx = kx;
  this->ox = ox;
  this->iy = iy;
  this->jy = jy;
  this->ky = ky;
  this->oy = oy;
  this->iz = iz;
  this->jz = jz;
  this->kz = kz;
  this->oz = oz;
  this->iw = iw;
  this->jw = jw;
  this->kw = kw;
  this->ow = ow;
}

Vector4 Matrix4::operator*(const Vector4 &b) {
  Vector4 vector4;
  vector4.x = b.x * ix + b.y * jx + b.z * kx + b.w * ox;
  vector4.y = b.x * iy + b.y * jy + b.z * ky + b.w * oy;
  vector4.z = b.x * iz + b.y * jz + b.z * kz + b.w * oz;
  vector4.w = b.x * iw + b.y * jw + b.z * kw + b.w * ow;
  return vector4;
}

Matrix4 Matrix4::operator*(const Matrix4 &b) {
  Matrix4 matrix4;
  Vector4 i = Vector4(b.ix, b.iy, b.iz, b.iw);
  Vector4 j = Vector4(b.jx, b.jy, b.jz, b.jw);
  Vector4 k = Vector4(b.kx, b.ky, b.kz, b.kw);
  Vector4 o = Vector4(b.ox, b.oy, b.oz, b.ow);

  Vector4 newI = this->operator*(i);
  Vector4 newJ = this->operator*(j);
  Vector4 newK = this->operator*(k);
  Vector4 newO = this->operator*(o);

  matrix4.ix = newI.x;
  matrix4.iy = newI.y;
  matrix4.iz = newI.z;
  matrix4.iw = newI.w;

  matrix4.jx = newJ.x;
  matrix4.jy = newJ.y;
  matrix4.jz = newJ.z;
  matrix4.jw = newJ.w;

  matrix4.kx = newK.x;
  matrix4.ky = newK.y;
  matrix4.kz = newK.z;
  matrix4.kw = newK.w;

  matrix4.ox = newO.x;
  matrix4.oy = newO.y;
  matrix4.oz = newO.z;
  matrix4.ow = newO.w;

  return matrix4;
}

void Matrix4::print() {
  cout << ix << ", " << jx << ", " << kx << ", " << ox << endl;
  cout << iy << ", " << jy << ", " << ky << ", " << oy << endl;
  cout << iz << ", " << jz << ", " << kz << ", " << oz << endl;
  cout << iw << ", " << jw << ", " << kw << ", " << ow << endl;
}

Matrix4 Translate3D(float tX, float tY, float tZ) {
  // Matrix4 matrix4 = Matrix4();
  // matrix4.ox = tX;
  // matrix4.oy = tY;
  // matrix4.oz = tZ;
  return Matrix4(1, 0, 0, tX, 0, 1, 0, tY, 0, 0, 1, tZ, 0, 0, 0, 1);
}

Matrix4 Scale3D(float sX, float sY, float sZ) {
  Matrix4 matrix4 = Matrix4();
  matrix4.ix = sX;
  matrix4.jy = sY;
  matrix4.kz = sZ;
  return matrix4;
}

Matrix4 RotateX3D(float degrees) {
  Matrix4 matrix4 = Matrix4();
  float radians = degrees * M_PI / 180.0;
  matrix4.jy = cos(radians);
  matrix4.ky = sin(radians);
  matrix4.jz = -sin(radians);
  matrix4.kz = cos(radians);
  return matrix4;
}

Matrix4 RotateY3D(float degrees) {
  Matrix4 matrix4 = Matrix4();
  float radians = degrees * M_PI / 180.0;
  matrix4.ix = cos(radians);
  matrix4.kx = -sin(radians);
  matrix4.iz = sin(radians);
  matrix4.kz = cos(radians);
  return matrix4;
}

Matrix4 RotateZ3D(float degrees) {
  Matrix4 matrix4 = Matrix4();
  float radians = degrees * M_PI / 180.0;
  matrix4.ix = cos(radians);
  matrix4.jx = sin(radians);
  matrix4.iy = -sin(radians);
  matrix4.jy = cos(radians);
  return matrix4;
}

Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ) {
  return RotateZ3D(degreesZ) * (RotateY3D(degreesY) * RotateX3D(degreesX));
}

Matrix4 Rotate3D(float degrees, Vector4 vec) {
  float alpha = atanf(vec.x / vec.z) * 180.0 / M_PI;
  Matrix4 RotAlp = RotateY3D(alpha);
  float beta = acosf(vec.y / vec.magnitude()) * 180.0 / M_PI;
  Matrix4 RotBet = RotateX3D(beta);
  Matrix4 RotAround = RotateY3D(degrees);
  Matrix4 Rot_Bet = RotateX3D(-beta);
  Matrix4 Rot_Alp = RotateY3D(-alpha);
  return Rot_Alp * (Rot_Bet * (RotAround * (RotBet * RotAlp)));
}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up) {
  Vector4 look = (spot - eye).normalize();
  Vector4 right = look.cross(up).normalize();
  Vector4 up2 = right.cross(look).normalize();
  Matrix4 step1 = Translate3D(-eye.x, -eye.y, -eye.z);
  Matrix4 step2(  right.x,  right.y,  right.z,  0,
                  up2.x, up2.y, up2.z,  0,
                  -look.x, -look.y, -look.z,  0,
                  0, 0, 0, 1);
  Matrix4 view = step2 * step1;
  return view;
}

Matrix4 Orthographic(float minX, float maxX, float minY,float maxY, float minZ,float maxZ){
  Matrix4 step1 = Translate3D(-(minX+maxX)/2, -(minY+maxY)/2, -(minZ+maxZ)/2);
  Matrix4 step2 = Scale3D(2/(maxX-minX), 2/(maxY-minY), 2/(maxZ-minZ));
  Matrix4 orthographic = step2 * step1;
  return orthographic;
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ){
  // float f = 1.0f/tanf(fovY/2);
  float radians = fovY * M_PI / 180.0;
  float f = 1.0f/tanf(radians/2);
  Matrix4 perspective( f/ aspect, 0, 0, 0,
                        0, f, 0, 0,
                        0, 0, (farZ+nearZ)/(nearZ-farZ), 2*nearZ*farZ/(nearZ-farZ),
                        0, 0, -1, 0);
  return perspective;
}

Matrix4 Viewport(float x, float y, float width, float height){

  Matrix4 step1 = Translate3D(1, 1, -1);
  Matrix4 step2 = Scale3D(0.5, 0.5, 0.5);
  Matrix4 step3 = Scale3D(width, height, 1);
  Matrix4 step4 = Translate3D(x, y, 0);
  Matrix4 viewport = step4 * step3 * step2 * step1;
  return viewport;
}
