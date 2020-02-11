/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
  public:
        double h; // hue of the pixel, storing the value of the hue in degrees as a double from [0, 360).
        double s; //saturation of the pixel, storing the value as a double from [0, 1].
        double l; //luminance of the pixel, storing the value as a double from [0, 1].
        double a; //the alpha channel, how transparent the pixel is, storing the value as a double from [0, 1].
        HSLAPixel();
        HSLAPixel(double hue, double saturation, double luminance);
        HSLAPixel(double hue, double saturation, double luminance, double alpha);
};
}
