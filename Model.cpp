#include "Model.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
using namespace std;

// Constructor
Model::Model(){
  triangles = vector<Triangle3D>();
}

int Model::numTriangles(){
  return triangles.size();
}

Triangle3D Model::operator[](int i){
  return triangles[i];
}

void Model::transform(Matrix4 m){
  for(int i = 0; i < numTriangles(); i++) {
    Triangle3D t = triangles[i];
    if(t.shouldDraw)
    {
      t.transform(m);
      triangles[i] = t;
    }
  }
}

void Model::readFromOBJFile(string filepath, Color pFillColor){
  ifstream myFile(filepath);
  if(myFile.is_open()) {
    string line;
    vector<Vector4> vertices;
    while (getline(myFile, line)) {
      istringstream s(line);
      string word;
      int tracker = 0;
      // If line starts with 'v'
      if(line[0] == 'v') {
        Vector4 vertex;
        vertex.w = 1;
        while(getline(s, word, ' ')) {
          if(word != "v") {
            if(tracker == 0) {
              vertex.x = atof(word.c_str());
              tracker++;
            } else if (tracker == 1) {
              vertex.y = atof(word.c_str());
              tracker++;
            } else {
              vertex.z = atof(word.c_str());
              tracker = 0;
            }
          }
        }
        vertices.push_back(vertex);
      }
      // If line starts with 'f'
      if(line[0] == 'f') {
        Triangle3D triangle;
        triangle.c1 = pFillColor;
        triangle.c2 = pFillColor;
        triangle.c3 = pFillColor;
        while(getline(s, word, ' ')) {
          if(word != "f") {
            int index = atoi(word.c_str());
            if(tracker == 0) {
              triangle.v1 = vertices[index-1];
              tracker++;
            }
            else if(tracker == 1) {
              triangle.v2 = vertices[index-1];
              tracker++;
            }
            else if(tracker == 2) {
              triangle.v3 = vertices[index-1];
              tracker++;
              triangles.push_back(triangle);
            }
            else if(tracker == 3) {
              Triangle3D triangle2;
              triangle2.c1 = pFillColor;
              triangle2.c2 = pFillColor;
              triangle2.c3 = pFillColor;
              triangle2.v1 = triangle.v1;
              triangle2.v2 = triangle.v3;
              triangle2.v3 = vertices[index-1];
              triangles.push_back(triangle2);
            }
          }
        }
        tracker = 0;
      }
    }
    myFile.close();
  }
}

void Model::homogenize(){
  for (int i = 0; i < numTriangles(); i++)
  {
    triangles[i].v1 = triangles[i].v1 * (1/triangles[i].v1.w);
    triangles[i].v2 = triangles[i].v2 * (1/triangles[i].v2.w);
    triangles[i].v3 = triangles[i].v3 * (1/triangles[i].v3.w);
  }
}

void Model::performBackfaceCulling(Vector4 eye, Vector4 spot){
  Vector4 look = (spot - eye).normalize();
  for (int i = 0; i < numTriangles(); i++){
    Triangle3D t = triangles[i];
    Vector4 edge1 = t.v3 - t.v2;
    Vector4 edge2 = t.v1 - t.v2;
    Vector4 normal = edge2.cross(edge1).normalize();
    float check = normal.dot(look);
    if (check >= 0.0){
      t.shouldDraw = false;
    }
    else{
      t.shouldDraw = true;
    }
    triangles[i] = t;
  }
}