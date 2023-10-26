#include "Raster.h"
#include "Vector.h"
#include "Matrix.h"
#include <iostream>
using namespace std;

void printVector(Vector2 v)
{
  cout << v.x << "   " << v.y << endl;
}

int main()
{

  // Matrix4 A(1 , 2 , 3 , 4 ,
  //  5 , 6 , 7 , 8 ,
  //  9 , 10 , 11 , 12 ,
  //  13 , 14 , 15 , 16);
  // Matrix4 B(17 , 18 , 19 , 20 ,
  //  21 , 22 , 23 , 24 ,
  //  25 , 26 , 27 , 28 ,
  //  29 , 30 , 31 , 32);
  // Matrix4 C = A * B;
  // C.print( );
  // Vector2 v = Vector2(2,5);
  // Vector2 a = Vector2(3,1);
  // printVector(v + a);
  // printVector(v - a);
  // printVector(v * 2.0);
  // cout << "v dot a" << v.dot(a) << endl;
  // cout << "v's magnitude: " << v.magnitude() << endl;
  // printVector(v.normalize());
  // printVector(v.perpendicular());

  Raster myRaster = Raster(100, 100, White);
  /* Test triangle */
  // Triangle3D t(Vector4(0, 0, 0, 1), Vector4(40, 0, 0, 1), Vector4(40, 40, 0, 1), Red, Blue, Green);
  // Matrix4 m = Scale3D(0.5, 0.5, 1);
  // cout << "Before: " << t.v2.y << "< " << t.v3.y << endl;
  // t.transform(m);
  // cout << "After: " << t.v2.y << "< " << t.v3.y << endl;
  // myRaster.drawTriangle3D_Barycentric(t);
  // myRaster.writeToPPM();

  /* Test 3D model */
  Model teapot = Model();
  teapot.readFromOBJFile("./teapot.obj", Red);
  Matrix4 m = Translate3D(50, 50, 0) * RotateZ3D(-45.0) * Scale3D(0.5, 0.5, 1);
  teapot.transform(m);
  myRaster.drawModel(teapot);
  myRaster.writeToPPM();

  // raster.drawLine_DDA_Interpolated(20, 20, 50, 70, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 120, 20, Red, Green);
  // raster.drawLine_DDA_Interpolated(20, 20, 20, 50, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 80, 40, Red, Green);

  // raster.writeToPPM();
}