#include "Triangle2D.h"

#include <iostream>

using namespace std;

Triangle2D::Triangle2D(){
  v1 = Vector2();
  v2 = Vector2();
  v3 = Vector2();
  c1 = Black;
  c2 = Black;
  c3 = Black;
}

Triangle2D::Triangle2D(Vector2 pV1, Vector2 pV2, Vector2 pV3, Color pC1, Color pC2, Color pC3) {
  v1 = pV1;
  v2 = pV2;
  v3 = pV3;
  c1 = pC1;
  c2 = pC2;
  c3 = pC3;
}

bool Triangle2D::inside(float x, float y) {
  Vector2 p = Vector2(x,y);
  
  Vector2 edge1 = v2 - v1;
  Vector2 edgePerp1 = edge1.perpendicular();
  Vector2 g1 = p - v1;
  float result1 = edgePerp1.dot(g1);

  Vector2 edge2 = v3 - v2;
  Vector2 edgePerp2 = edge2.perpendicular();
  Vector2 g2 = p - v2;
  float result2 = edgePerp2.dot(g2);

  Vector2 edge3 = v1 - v3;
  Vector2 edgePerp3 = edge3.perpendicular();
  Vector2 g3 = p - v3;
  float result3 = edgePerp3.dot(g3);  

  if (result1 >=0 && result2 >= 0 && result3 >= 0){
    return true;
  } else{
    return false;
  }
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3) {
  lambda1 = determinant(v2-v3, P-v3) / determinant(v2-v3, v1-v3);
  lambda2 = determinant(P-v3, v1-v3) / determinant(v2-v3, v1-v3);
  lambda3 = 1 - lambda1 - lambda2;
}