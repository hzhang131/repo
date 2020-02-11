/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include <iostream>
#include <string>


    class Image : public cs225::PNG{
    public:
      void lighten();
      void lighten(double amount);
      void darken();
      void darken(double amount);
      void saturate();
      void saturate(double amount);
      void desaturate();
      void desaturate(double amount);
      void grayscale();
      void rotateColor(double degrees);
      void illinify();
      void scale(double factor);
      void scale(unsigned w, unsigned h);
      //and of course, the RULE OF THREE are inherited from the base class.
      Image();
      Image(unsigned width, unsigned height);
      Image(const Image & other);
    };
