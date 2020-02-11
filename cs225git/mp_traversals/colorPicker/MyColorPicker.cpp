#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <stdlib.h>
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

 MyColorPicker::MyColorPicker(){
   /*Nothing */
   png.readFromFile("tests/Flag.png");
 }


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  return png.getPixel(x/1.3, y/1.3);
}
