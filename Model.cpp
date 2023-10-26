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
    triangles[i].transform(m);
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
        vertex.w = 1.0;
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