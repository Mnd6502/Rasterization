#include "Matrix.h"
#include "Raster.h"
#include "Vector.h"
#include "Model.h"
#include "Color.h"
#include <iostream>
using namespace std;

#define WIDTH 100
#define HEIGHT 100

void printVector(Vector2 v)
{
  cout << v.x << "   " << v.y << endl;
}

int main()
{
  // Matrix4 testTranslate = Translate3D(1, 2, 3);
  // Triangle3D triangle = Triangle3D(Vector4(0, 0, 0, 1), Vector4(7, 4, 0, 1),
  //                                  Vector4(1, 5, 10, 1), White, White, White);
  // triangle.transform(testTranslate);
  // cout << triangle.v2.x << "   " << triangle.v2.y << "   " << triangle.v2.z
  //      << endl;
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

  // Raster myRaster = Raster(100, 100, White);
  // Triangle3D t(Vector4(0,0,0,1), Vector4(40,0,0,1), Vector4(40,40,0,1), Red,
  // Blue, Green);
  // Model teapot = Model();
  // teapot.readFromOBJFile("./teapot.obj", Red);
  // Matrix4 m = Translate3D(50, 50, 0) * RotateZ3D(-45.0) * Scale3D(0.5, 0.5, 0.5);
  // // Matrix4 m =
  // //     Translate3D(50, 50, 0) * RotateZ3D(-45.0) * Scale3D(0.5, 0.5, 0.5);
  // teapot.transform(m);
  // myRaster.drawModel(teapot);
  // // t.transform(m);
  // // m.print();
  // // myRaster.drawTriangle3D_Barycentric(t);
  // myRaster.writeToPPM();

  // raster.drawLine_DDA_Interpolated(20, 20, 50, 70, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 120, 20, Red, Green);
  // raster.drawLine_DDA_Interpolated(20, 20, 20, 50, Red, Blue);
  // raster.drawLine_DDA_Interpolated(20, 20, 80, 40, Red, Green);

  // raster.writeToPPM();

  Raster myRaster(WIDTH, HEIGHT, White);

  Model teapot, bunny;
  teapot.readFromOBJFile("./teapot.obj", Red);
  bunny.readFromOBJFile("./bunny.obj", Blue);

  Matrix4 modelMatrixTeapot =
      Translate3D(50, 50, -30) *
      RotateZ3D(45.0) *
      Scale3D(0.5, 0.5, 0.5);

  // Matrix4 modelMatrixBunny =
  //     Translate3D(70, 30, -60)*
  //     RotateZ3D(-20.0) *
  //     Scale3D(500, 500, 500);

  Vector4 eye(50, 50, 30, 1);
  Vector4 spot(50, 50, -30, 1);
  teapot.performBackfaceCulling(eye, spot);

  Matrix4 viewMatrix = LookAt(
      eye,
      spot,
      Vector4(0, 1, 0, 0));

  Matrix4 perspectiveMatrix = Perspective(
      70.0,
      myRaster.getWidth() / myRaster.getHeight(),
      0.01,
      88.5);

  Matrix4 viewportMatrix = Viewport(
      0,
      0,
      myRaster.getWidth(),
      myRaster.getHeight());

  teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
  // bunny.transform(perspectiveMatrix*viewMatrix*modelMatrixBunny);

  teapot.homogenize();
  // bunny.homogenize();

  teapot.transform(viewportMatrix);
  // bunny.transform(viewportMatrix);

  myRaster.drawModel(teapot);
  // myRaster.drawModel(bunny);

  // teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
  // teapot.homogenize();
  // teapot.transform(viewportMatrix);
  // myRaster.drawModel(teapot);

  myRaster.writeToPPM();
}