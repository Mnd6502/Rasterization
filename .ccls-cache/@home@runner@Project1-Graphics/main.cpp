#include "Color.h"
#include <iostream>
using namespace std;

int main() {
  Color c1 = Color(1.0f, 0.25f, 0.25f);
  Color c2 = Color(0.0f, 0.5f, 1.0f);
  Color c3 = c1 * 2.0;
  // Color c3 = 2.0 * c1;
  //  Note: Color * float and not float * Color. Why ?
  //  The expression will find an overload of the operator   //  defined in the
  //  class
  cout << c3.red << endl;
  cout << c3.green << endl;
  cout << c3.blue << endl;
}