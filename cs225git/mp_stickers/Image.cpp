#include "Image.h"
#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::cin;
using std::string;
using std::endl;
Image::Image():PNG(){

}

Image::Image(unsigned width, unsigned height):PNG(width, height)
{

}

Image::Image(const Image & other):PNG(other)
{

}

void Image::lighten(){

  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i, j);
      if (pixel.l < 0.9) pixel.l += 0.1;
      else pixel.l = 1;
    }
  }
  return;
}

void Image::darken(){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i, j);
      if (pixel.l > 0.1) pixel.l -= 0.1;
      else pixel.l = 0;
    }
  }
}

void Image::lighten(double amount){

    for (unsigned int i = 0; i < width(); i++){
      for (unsigned int j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i, j);
      if (pixel.l + amount < 1) pixel.l += amount;
      else pixel.l = 0;
      }
    }
}

void Image::darken(double amount){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
    cs225::HSLAPixel & pixel = getPixel(i, j);
    if (pixel.l - amount > 0) pixel.l -= amount;
    else pixel.l = 0;
    }
  }
}


void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i < width(); i++){
      for (unsigned int j = 0; j < height(); j++){
        cs225::HSLAPixel & pixel = getPixel(i, j);
        if (pixel.h + degrees >= 360) pixel.h = pixel.h + degrees - 360;
        else if (pixel.h + degrees <= 0) pixel.h = 360 + pixel.h + degrees;
        else
        pixel.h = pixel.h + degrees;
      }
    }
}

void Image::saturate(){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
    cs225::HSLAPixel & pixel = getPixel(i, j);
    if (pixel.s + 0.1 <= 1) pixel.s += 0.1;
    }
  }
}

void Image::desaturate(){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
    cs225::HSLAPixel & pixel = getPixel(i, j);
    if (pixel.s - 0.1 >= 0) pixel.s -= 0.1;
    }
  }
}

void Image::saturate(double amount){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i, j);
      if (pixel.s + amount <= 1) pixel.s += amount;
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i, j);
      if (pixel.s - amount >= 1) pixel.s -= amount;
    }
  }
}

void Image::scale(double factor){
    unsigned int width_ = width();
    unsigned int height_ = height();
    double new_width =  width_ * factor;
    double new_height =  height_ * factor;

    Image *canvas = new Image (new_width, new_height);
    for (unsigned i = 0; i < (unsigned) new_width; i++){
      for (unsigned j = 0; j < (unsigned) new_height; j++){
        cs225::HSLAPixel & new_pixel = canvas -> getPixel(i, j);
        cs225::HSLAPixel & old_pixel = getPixel((unsigned) i/factor, (unsigned) j/factor);
        new_pixel = old_pixel;
      }
    }
    resize(new_width, new_height);
    for (unsigned i = 0; i < (unsigned) new_width; i++){
      for (unsigned j = 0; j < (unsigned) new_height; j++){
        cs225::HSLAPixel & new_pixel = getPixel(i,  j);
        cs225::HSLAPixel & old_pixel = canvas -> getPixel(i, j);
        new_pixel = old_pixel;
      }
    }
    delete canvas;
}

void Image::scale(unsigned w, unsigned h){
    double width_ = width();
    double height_ = height();
    //Try width.
    if ((double) w / width_ * height_ < (double) h)
    {
      Image *canvas = new Image (w, (unsigned) w/width_ * height_);
      for (double i = 0; i < w; i++){
        for (double j = 0; j < (unsigned) w/width_ * height_; j++){
          cs225::HSLAPixel & new_pixel = canvas -> getPixel((unsigned) i, (unsigned) j);
          cs225::HSLAPixel & old_pixel = getPixel((unsigned) i * width_ / w, (unsigned) j * width_ / w );
          new_pixel = old_pixel;
        }
      }
      resize(w, (unsigned) w/width_ * height_);
      for (double i = 0; i < w; i++){
        for (double j = 0; j < (unsigned) w/width_ * height_; j++){
          cs225::HSLAPixel & new_pixel = getPixel((unsigned) i, (unsigned) j);
          cs225::HSLAPixel & old_pixel = canvas -> getPixel((unsigned) i, (unsigned) j);
          new_pixel = old_pixel;
        }
      }
      delete canvas;
    }
    else{
      Image *canvas = new Image ((unsigned) h/height_ * width_, h);
      for (double i = 0; i < (unsigned) h/height_ * width_; i++){
        for (double j = 0; j < h; j++){
          cs225::HSLAPixel & new_pixel = canvas -> getPixel((unsigned) i, (unsigned) j);
          cs225::HSLAPixel & old_pixel = getPixel((unsigned) i * height_ / h, (unsigned) j * height_ / h );
          new_pixel = old_pixel;
        }
      }
      resize((unsigned) h/height_ * width_, h);
      for (double i = 0; i < (unsigned) h/height_ * width_; i++){
        for (double j = 0; j < h; j++){
          cs225::HSLAPixel & new_pixel = getPixel((unsigned) i, (unsigned) j);
          cs225::HSLAPixel & old_pixel = canvas -> getPixel((unsigned) i, (unsigned) j);
          new_pixel = old_pixel;
        }
      }
      delete canvas;
    }

}

void Image::illinify(){
  for (unsigned int x = 0; x < width(); x++){
    for (unsigned int y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x,y);
      if (pixel.h >= (11+216)/2 && pixel.h <= (216+11+360)/2)
      pixel.h = 216;
      else pixel.h = 11;
    }
  }
}

void Image::grayscale(){
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}
