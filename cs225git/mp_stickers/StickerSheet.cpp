
#include "StickerSheet.h"
#include <iostream>
#include <string>

using namespace std;

unsigned skipped_index;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    //deep copy picture to base picture.
    base_picture = new Image(picture);
    //initialize sticker array.
    max_ = max;
    x = new int[max];
    y = new int[max];
    stickers_array = new Image*[max];
    for (unsigned int i = 0; i < max_ ; i++){
      stickers_array[i] = NULL;
      x[i] = -1;
      y[i] = -1;
      base_width = base_picture -> width();
      base_height = base_picture -> height();
    }
}
//--------------------------------------------------------------
//Rule of Three Functions.
StickerSheet::~StickerSheet(){
  _destroy();
}

StickerSheet::StickerSheet(const StickerSheet & other){
  _copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
  _destroy();
  if (this != &other) _copy(other);
  return *this;
}
//-----------------------------------------------------------------
//Below are member functions.
int StickerSheet::addSticker(Image & sticker, unsigned x_, unsigned y_){
  //check current_layer.
  unsigned int current_layer = 0;
  while (stickers_array[current_layer] != NULL){
    current_layer++;
    if (current_layer == max_) break;
  }

  if (current_layer < max_){

    //if image out of bound, resize the base image.
    if (x_ + sticker.width() > base_picture -> width()){
      base_picture -> resize(x_ + sticker.width(), base_picture -> height());
      //change base width.
      //base_width = base_picture -> width();
    }

    if (y_ + sticker.height() > base_picture -> height()){
      base_picture -> resize(base_picture -> width(), y_ + sticker.height());
      //change base height.
      //base_height = base_picture -> height();
    }


    stickers_array[current_layer] = new Image(sticker);
    x[current_layer] = (int) x_;
    y[current_layer] = (int) y_;
    return (int) current_layer;
  }
  return -1;

}

void StickerSheet::changeMaxStickers(unsigned max){
  if (max == 0){
    for (unsigned i = 0; i < max_; i++){
      delete stickers_array[i];
      stickers_array[i] = NULL;
      x[i] = -1;
      y[i] = -1;
    }
      max_ = 0;
      base_picture -> resize(base_width, base_height);
      return;
  }
  if (max_ == max) return;
  else if (max > max_){
    //initialize a new array and initialize every image element to zero.
    Image** new_array = new Image*[max];
    int* new_x = new int[max];
    int* new_y = new int[max];
    for (unsigned int i = 0; i < max; i++){
      new_array[i] = NULL;
      new_x[i] = -1;
      new_y[i] = -1;
    }
    //copy all everything over from original arrays to new arrays.
    for (unsigned int i = 0; i < max_; i++){
      if (stickers_array[i] == NULL) break;
      new_array[i] = new Image(*(stickers_array[i]));
      new_x[i] = x[i];
      new_y[i] = y[i];
    }
    //delete original array and set to NULL.
    for (unsigned int i = 0; i< max_; i++){
      delete stickers_array[i];
    }
    delete[] stickers_array;
    delete[] x;
    delete[] y;
    stickers_array = new_array;
    x = new_x;
    y = new_y;
    max_ = max;
  }
  else if(max < max_){
    Image** new_array = new Image*[max];
    int* new_x = new int[max];
    int* new_y = new int[max];
    for (unsigned int i = 0; i < max; i++){
      new_array[i] = NULL;
      new_x[i] = -1;
      new_y[i] = -1;
    }
    //copy all everything over from original arrays to new arrays.
    for (unsigned int i = 0; i < max; i++){
      if (stickers_array[i] == NULL) break;
      new_array[i] = new Image(*(stickers_array[i]));
      new_x[i] = x[i];
      new_y[i] = y[i];
    }
    //delete original array and set to NULL.
    for (unsigned int i = 0; i < max_; i++){
      delete stickers_array[i];
    }
    delete[] stickers_array;
    delete[] x;
    delete[] y;
    x = new_x;
    y = new_y;
    max_ = max;
    stickers_array = new_array;

  }

}

Image* StickerSheet::getSticker(unsigned index){
  if (index >= max_) return NULL;
  if (stickers_array[index] != NULL) return stickers_array[index];
  else return NULL;
}

void StickerSheet::removeSticker(unsigned index){
  //Check garbage index.
  if (index >= max_ || index < 0) return;
  if (stickers_array[index] == NULL) return;
  if (x[index] == -1) return;
  if (y[index] == -1) return;
  //Find the actual image ptr from stickers_array.
  //resize back.
  skipped_index = index;
  int temp_width = x[index] + stickers_array[index] -> width();
  int temp_height =  y[index] + stickers_array[index] -> height();
  //unsigned int org_bigger_width = _bigger_width(x);if (stickers_array[j+1] == NULL) break;
  //unsigned int org_bigger_height = _bigger_height(y);
  skipped_index = index;

  if ((unsigned) temp_width > _bigger_width(x) && (unsigned) temp_height > _bigger_height(y)){
    if (_bigger_width(x) > base_width && _bigger_height(y) > base_height ){
      base_picture -> resize(_bigger_width(x), _bigger_height(y));
      //base_width = base_picture -> width();
      //base_height = base_picture -> height();
    }
    else
    base_picture -> resize(base_width, base_height);
  }


  else if ((unsigned) temp_width > _bigger_width(x)) {
    if (_bigger_width(x) > base_picture -> width()){
      base_picture -> resize(_bigger_width(x), base_picture -> height());
      //base_width = base_picture -> width();
    }
    else
    base_picture -> resize(base_width, base_picture -> height());

  }


  else if ((unsigned) temp_height > _bigger_height(y)) {
    if (_bigger_height(y) > base_height){
      base_picture -> resize(base_picture -> width(), _bigger_height(y));
      //base_height = base_picture -> height();
    }
    else
    base_picture -> resize(base_picture -> width(), base_height);
  }

  //check how many image ptrs do we have in the stickers_array
  unsigned i = 0;
  while (stickers_array[i] != NULL){
    i++;
    if (i == max_) break;
  }
  //now we can delete the image safely and reorder the image ptrs.
  for (unsigned j = index; j < i - 1; j++){
    delete stickers_array[j];
    if (stickers_array[j+1] == NULL) break;
    stickers_array[j] = new Image(*stickers_array[j+1]);
    x[j] = x[j+1];
    y[i] = y[j+1];
  }
  delete stickers_array[i-1];
  stickers_array[i-1] = NULL;
  x[i-1] = -1;
  y[i-1] = -1;
}

bool StickerSheet::translate(unsigned index, unsigned x_, unsigned y_){
  //Check garbage index.
  if (index >= max_) return false;
  if (x[index] == -1 || y[index] == -1) return false;
  //change x and y coordinates accordingly.
  x[index] = x_;
  y[index] = y_;
  return true;
}

Image StickerSheet::render() const{
    if (stickers_array[0] == NULL){
      return *base_picture;
    }
    //make a deep copy of the original base_picture.
    Image* new_image = new Image(*base_picture);
    //check out how many images we have in our picture.
    unsigned index = 0;
    while (x[index] != -1){
      index++;
      if (index == max_) break;
    }
    /*
    //go through each image pointer in stickers array and mark the image with the largest width and height.
    unsigned stickers_index = 0;
    unsigned max_width = 0;
    unsigned max_height = 0;
    while (stickers_array[stickers_index] != NULL){
      max_width = (max_width > (x[stickers_index] + stickers_array[stickers_index] -> width()) ? max_width : (x[stickers_index] + stickers_array[stickers_index] -> width())) ;
      max_height = (max_height > (y[stickers_index] + stickers_array[stickers_index] -> height()) ? max_height : (y[stickers_index] + stickers_array[stickers_index] -> height())) ;
      stickers_index++;
    }
    if (max_width > base_picture -> width()) base_picture -> resize(max_width, base_picture -> height());
    if (max_height > base_picture -> height()) base_picture -> resize(base_picture -> width(), max_height);
    */
    //looping for choosing the images.
    for (unsigned i = 0; i < index; i++){
      //looping for width.
      for (unsigned j = x[i]; j < x[i] + stickers_array[i] -> width(); j++){
        //looping for height.
        for (unsigned k = y[i]; k < y[i] + stickers_array[i] -> height(); k++){
          //get original pixel from sticker.
          cs225::HSLAPixel & old_pixel = stickers_array[i] -> getPixel(j-x[i], k-y[i]);
          cs225::HSLAPixel & new_pixel = new_image -> getPixel(j, k);
          //If alpha value is not 0, copy the pixel's HSLA value over.
          if (old_pixel.a != 0){
            new_pixel = old_pixel;
          }
        }
    }
}
  Image returned_image = *new_image;
  delete new_image;
  return returned_image;
}
//-----------------------------------------------------------------
//Helper Functions: _copy and _destroy.
//

void StickerSheet::_copy(StickerSheet const & other){
  if (other.base_picture == NULL) {
    std::cout << "copy failed." << std::endl;
    return;
  }
  base_picture = new Image(*(other.base_picture));
  stickers_array = new Image*[other.max_];
  x = new int[other.max_];
  y = new int[other.max_];
  max_ = other.max_;
  base_width = other.base_width;
  base_height = other.base_height;
  for (unsigned int i = 0; i < max_ ; i++){
    if (other.stickers_array[i] == NULL) {
      stickers_array[i] = NULL;
      x[i] = -1;
      y[i] = -1;
      continue;
    }
    //*(stickers_array[i]) = *(other.stickers_array[i]);
    stickers_array[i] = new Image(*(other.stickers_array[i]));
    x[i] = other.x[i];
    y[i] = other.y[i];
  }
}



void StickerSheet::_destroy(){
  delete base_picture;
  delete[] x;
  delete[] y;
  for (unsigned int i = 0; i < max_; i++){
    delete stickers_array[i];
    stickers_array[i] = NULL;
  }
  delete[] stickers_array;
  stickers_array = NULL;
}

//-----------------------------------------------------------
//_bigger_width: returns the biggest value available in an array.
// if bigger_width is less than base width, return base width.
//_bigger_height: returns the bigger height available in an array.
// if bigger_height is less than base height, return base height.

unsigned int StickerSheet::_bigger_width(int* arr){
  unsigned largest = 0;
  unsigned int i = 0;
  while (arr[i] >= 0){
    if (i != skipped_index){
      largest = ((unsigned) arr[i] + stickers_array[i] -> width() >= largest ? (unsigned) arr[i] + stickers_array[i] -> width() : largest);
    }
    if (i == max_ - 1) break;
    i++;
  }
  if (largest <= base_width) return base_width;
  else return largest;
}


unsigned int StickerSheet::_bigger_height(int* arr){
  unsigned largest = 0;
  unsigned int i = 0;
  while (arr[i] >= 0){
    if (i != skipped_index){
      largest = ( (unsigned) arr[i] + stickers_array[i] -> height() >= largest ? (unsigned) arr[i] + stickers_array[i] -> height() : largest);
    }
    if (i == max_ - 1) break;
    i++;
  }
  if (largest <= base_height) return base_height;
  else return largest;
}
