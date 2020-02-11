#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cstdlib>
#include <string>
#include <cmath>
using cs225::PNG;
using cs225::HSLAPixel;

int comp(unsigned x, unsigned y){
  if (x <= y) return (int)(x - y);
  else return (int) (y - x);

}
void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  //creates a default png file.
  cs225::PNG png;
  //creates a new blank png file waiting to be filled in.
  png.readFromFile(inputFile);

  cs225::PNG new_png(png.width(), png.height());
  //converts inputFile to standard png file and extracts information.


    for (unsigned x = 0; x < png.width(); x++){
      for (unsigned y = 0; y < png.height(); y++){
        cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
        cs225::HSLAPixel & new_pixel = new_png.getPixel(png.width()-1-x, png.height()-1-y);
        //Pass in information from the old pixel to the new pixel.
        new_pixel.h = current_pixel.h;
        new_pixel.l = current_pixel.l;
        new_pixel.s = current_pixel.s;
        new_pixel.a = current_pixel.a;

      }
    }
    //Finished filling in information, now start to convert to outputFile.

    new_png.writeToFile(outputFile);
    return;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  for (unsigned x = 0; x < png.width(); x++){
    int diff;
    if ((x >= 0 && x <= png.width()/40)) diff = png.width()/40 - x;
    else if (x >= png.width()*39.0/40) diff = x - png.width()*39.0/40;
    else diff = 0;
    for (unsigned y = 0 + diff; y < png.width()- diff; y++){
      cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
      current_pixel.h = 136.0;
      current_pixel.l = 0.353;
      current_pixel.s = 0.467;
      current_pixel.a = 1.0;

    }

  }
  for (unsigned x = 0; x <= png.width()/20; x++){
    for (unsigned y = 0; y <= png.width()/20; y++){
      if ((comp(x, png.width()/40) * comp(x, png.width()/40))  + (comp(y, png.width()/40) * comp(y, png.width()/40)) <= ((int)(png.width()/40) * (int)(png.width()/40) )){
        cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
        current_pixel.h = 136.0;
        current_pixel.l = 0.353;
        current_pixel.s = 0.467;
        current_pixel.a = 1.0;
      }

    }
  }

  for (unsigned x = png.width()*19.0/20; x < png.width(); x++){
    for (unsigned y = 0; y <= png.width()/20; y++){
      if ((comp(x, png.width()*39.0/40) * comp(x, png.width()*39.0/40))  + (comp(y, png.width()/40) * comp(y, png.width()/40)) <= ((int)(png.width()/40) * (int)(png.width()/40) )){
        cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
        current_pixel.h = 136.0;
        current_pixel.l = 0.353;
        current_pixel.s = 0.467;
        current_pixel.a = 1.0;
      }

    }
  }

  for (unsigned x = png.width()*19.0/20; x < png.width(); x++){
    for (unsigned y = png.width()*19.0/20; y < png.width(); y++){
      if ((comp(x, png.width()*39.0/40) * comp(x, png.width()*39.0/40))  + (comp(y, png.width()*39.0/40) * comp(y, png.width()*39.0/40)) <= ((int)(png.width()/40) * (int)(png.width()/40) )){
        cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
        current_pixel.h = 136.0;
        current_pixel.l = 0.353;
        current_pixel.s = 0.467;
        current_pixel.a = 1.0;
      }

    }
  }

  for (unsigned x = 0; x <= png.width()/20; x++){
    for (unsigned y = png.width()*19.0/20; y < png.width(); y++){
      if ((comp(x, png.width()/40) * comp(x, png.width()/40))  + (comp(y, png.width()*39.0/40) * comp(y, png.width()*39.0/40)) <= ((int)(png.width()/40) * (int)(png.width()/40) )){
        cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
        current_pixel.h = 136.0;
        current_pixel.l = 0.353;
        current_pixel.s = 0.467;
        current_pixel.a = 1.0;
      }

    }
  }



  for (unsigned x = png.width()/6 - png.width()/12; x<= png.width()/6 + png.width()/12; x++){
    for (unsigned y = png.width()/6 - png.width()/12; y<= png.width()/6 + png.width()/12; y++){
    cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
   if ((comp(x, png.width()/6) * comp(x, png.width()/6))  + (comp(y, png.width()/6) * comp(y, png.width()/6)) <= ((int)(png.width()/12) * (int)(png.width()/12) )) {
    if (y > (png.width()/6 - png.width()/12) && (y - png.width()/6 + png.width()/12 ) < png.width()/23 ){
    current_pixel.h = 11.0;
    current_pixel.l = 0.53;
    current_pixel.s = 0.81;
    current_pixel.a = 1.0;
  }
  else{
    current_pixel.h = 216.0;
    current_pixel.l = 0.18;
    current_pixel.s = 0.6;
    current_pixel.a = 1.0;
  }
}

  if ((comp(x, png.width()/6) * comp(x, png.width()/6))  + (comp(y, png.width()/6) * comp(y, png.width()/6)) <= ((int)(png.width()/12) * (int)(png.width()/12) ) && (comp(x, png.width()/6) * comp(x, png.width()/6))  + (comp(y, png.width()/6) * comp(y, png.width()/6)) >= ((int)(png.width()/12.5) * (int)(png.width()/12.5) )) {
  current_pixel.h = 0.0;
  current_pixel.s = 0.0;
  current_pixel.l = 1.0;
  current_pixel.a = 1.0;

}

  }
}

  for (unsigned x = 0; x < png.width(); x++){
    for (unsigned y = png.width()/3 - png.width()/400; y <= png.width()/3 + png.width()/400; y++){
    cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
    current_pixel.h = 0.0;
    current_pixel.s = 0.0;
    current_pixel.l = 1.0;
    current_pixel.a = 1.0;
    }
    for (unsigned y = png.width()*2.0/3 - png.width()/400; y <= png.width()*2.0/3 + png.width()/400; y++){
    cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
    current_pixel.h = 0.0;
    current_pixel.s = 0.0;
    current_pixel.l = 1.0;
    current_pixel.a = 1.0;
    }
  }

for (unsigned x = 0; x < png.width(); x++){
  for (unsigned y = png.width()/3+ png.width()/40; y< png.width()*2.0/3 - png.width()/40; y++){
    if (rand() % 25 == 1) {
      cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
      current_pixel.h = 0.0;
      current_pixel.s = 0.0;
      current_pixel.l = 1.0;
      current_pixel.a = 1.0;
    }
  }
}

for (unsigned x = 0; x < png.width(); x++){
  for (unsigned y = png.width()*2.0/3+ png.width()/40; y< png.width() - png.width()/40 ; y++){
    if (rand() % 25 == 1) {
      cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
      current_pixel.h = 0.0;
      current_pixel.s = 0.0;
      current_pixel.l = 1.0;
      current_pixel.a = 1.0;
    }
  }
}
   for (unsigned x = png.width()*5.0/6 - png.width()/5; x < png.width()*5.0/6 + png.width()/12; x++ ){
     for (unsigned y = png.width()/6 - png.width()/12; y < png.width()/6 + png.width()/12; y++){
       cs225::HSLAPixel & current_pixel = png.getPixel(x, y);
       current_pixel.h = 51.0;
       current_pixel.s = 1.0;
       current_pixel.l = 0.5;
       current_pixel.a = 1.0;
     }
   }

  return png;
}
