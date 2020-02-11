/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once
#include <iostream>
#include <string>
#include "Image.h"

using std::string;

class StickerSheet{
public:

  StickerSheet(const Image & picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  const StickerSheet & operator=(const StickerSheet & other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x_, unsigned y_);
  bool translate(unsigned index, unsigned x_, unsigned y_);
  void removeSticker(unsigned index);
  Image* getSticker(unsigned index);
  Image render() const;
private:
  //Image array that holds a number of different image pointers.
  Image** stickers_array;
  int *x;
  int *y;
  unsigned int max_;
  Image* base_picture;
  unsigned int base_width;
  unsigned int base_height;
  void _copy(StickerSheet const & other);
  void _destroy();
  unsigned int _bigger_width(int* arr);
  unsigned int _bigger_height(int* arr);

};
