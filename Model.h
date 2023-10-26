#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "Triangle.h"
#include <string>

using namespace std;

class Model{
private:
  vector<Triangle3D> triangles;
public:
  Model();
  int numTriangles();
  Triangle3D operator[](int i);
  void transform(Matrix4 m);
  void readFromOBJFile(string filepath, Color pFillColor);
};

#endif // MODEL_H