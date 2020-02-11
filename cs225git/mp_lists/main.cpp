#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

int main() {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-waterfall.png");

  List<HSLAPixel> list = imageToList(in);
  list.waterfall();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-waterfall.png");

  INFO("Your output image saved as actual-waterfall.png");
  REQUIRE( expected == out );
}
