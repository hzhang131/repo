#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
bool ImageTraversal::Iterator::addition_check(const Point & p){
  bool sol = !visited[p];
  ImageTraversal* some_traversal = traversal_;
  // Out of bound check.
  sol = sol && p.x < png_.width();
  sol = sol && p.x >= 0;
  sol = sol && p.y < png_.height();
  sol = sol && p.y >= 0;
  if (!sol) {
    return sol;
  }
  // Out of tolerance check.
  HSLAPixel& given = png_.getPixel(p.x, p.y);
  HSLAPixel& start = png_.getPixel(startPoint.x, startPoint.y);
  sol = sol && (calculateDelta(given, start) < traversal_ -> getTolerance());
  return sol;
}

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    traversal_ = nullptr;
    is_end = false;
}

/**
 * Custom iterator constructor.
 */
ImageTraversal::Iterator::Iterator(PNG& png, ImageTraversal* traversal, bool flag){
  traversal_ = traversal;
  startPoint = traversal_ -> peek();
  is_end = flag;
  current = startPoint;
  png_ = png;
  //each point -> false.
  for (unsigned i = 0; i < png.width(); i++){
      for (unsigned j = 0; j < png.height(); j++){
        visited.insert({Point(i,j), false});
      }
  }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point temp = traversal_ -> pop();

  if(visited[temp] == false) {
    visited[temp] = true;
  }
  if (addition_check(Point(temp.x+1, temp.y))){
    //if not out of bound and within a tolerance.
      traversal_ -> add(Point(temp.x+1, temp.y));
  }
  if (addition_check(Point(temp.x, temp.y+1))){
    traversal_ -> add(Point(temp.x, temp.y+1));
  }
  if (addition_check(Point(temp.x-1, temp.y))){
    traversal_ -> add(Point(temp.x-1, temp.y));
  }
  if (addition_check(Point(temp.x, temp.y-1))){
    traversal_ -> add(Point(temp.x, temp.y-1));
  }
  if (traversal_ -> empty() == true){
    this -> is_end = true;
    return *this;
  }

  if (traversal_ -> empty() != true){
    this -> current = traversal_ -> peek();
  
  while (traversal_ -> empty() != true && visited[traversal_ -> peek()]){
      this -> current = traversal_ -> pop();
      if (!traversal_ -> empty()){
        this -> current = traversal_ -> peek();
      }
    }
    if (traversal_ -> empty()) {
      this -> is_end = true;
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this -> current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return is_end != other.is_end;
}
