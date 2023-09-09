#include "Raster.h"
#include <iostream>
using namespace std;

int main() {

  // Testing Color struct
  // Color c1 = Color(1.0f, 0.25f, 0.25f);
  // Color c2 = Color(0.0f, 0.5f, 1.0f);
  // Color c3 = c1 * 2.0;
  // Color c3 = 2.0 * c1;
  //  Note: Color * float and not float * Color. Why ?
  //  The expression will find if an overload of the operator   //  is defined
  //  in the class of the variable on the left. class
  // cout << c3.red << endl;
  // cout << c3.green << endl;
  // cout << c3.blue << endl;

  // Testing Raster class
  Raster img = Raster(120, 140, Red);
  // img.setColorPixel(1, 1, Blue);
  // img.setColorPixel(0,0, Green);
  // img.drawLine_DDA(50, 12, 39, 70, Blue); // Steep line m negative (|m| > 1)
  // //img.drawLine_DDA(39, 70, 50, 12, Green); // Same but swap points
  // img.drawLine_DDA(10, 70, 10, 20, Black); // Vertical
  // img.drawLine_DDA(80, 50, 30, 50, Black); // Horizontal

  // // steep line m positive (m > 1)
  //  img.drawLine_DDA(50, 70, 39, 12, Blue);
  //  img.drawLine_DDA(20, 20, 50, 60, Blue);
  //  img.drawLine_DDA(30, 30, 45, 45, Blue);
  // // normal line m positive
  // img.drawLine_DDA(20, 20, 70, 30, Green);
  
  // Color ran = Color(0.5, 0.7, 1.0);
  // img.drawLine_DDA(80, 40, 50, 30, ran);
  // // // normal line m negative
  // // img.drawLine_DDA(30, 30, 70, 10, Green);

  // // img.drawLine_DDA();
  // img.writeToPPM();

  // drawing a star
  Color Yellow = Color ( 1.0, 1.0, 0);
  img.drawLine_DDA(50, 80, 40, 40, Yellow);
  img.drawLine_DDA(60, 40, 50, 80, Yellow);
  img.drawLine_DDA(30,60,60,40, Yellow);
  img.drawLine_DDA(40,40,70,60, Yellow);
  img.drawLine_DDA(30,60,70,60, Yellow);
  img.writeToPPM();
}