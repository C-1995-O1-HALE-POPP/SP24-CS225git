#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
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
ImageTraversal::Iterator::Iterator():
  end_(true),curr_(Point(0,0)),traversal_(nullptr){/** @todo [Part 1] */}
ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, Point & start, double & tolerance, PNG & image):
  end_(false),start_(start),traversal_(traversal),image_(image),tolerance_(tolerance){
  curr_=traversal->peek();
  visited_.resize(image.height()*image.width(),false);
}

ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */

  /** @todo [Part 1] */
  if(traversal_->empty()) {
    end_=true;
    return *this;
  }
  // lit up and remove current point in list
  traversal_->pop(); 
  visited_[curr_.x + curr_.y * image_.width()]=true;
  
  Point right_(curr_.x + 1, curr_.y);
  Point below_(curr_.x, curr_.y + 1);
  Point left_(curr_.x - 1, curr_.y);
  Point above_(curr_.x, curr_.y - 1);
  if(right_.x < image_.width() && right_.y < image_.height()){
    if(calculateDelta(*(image_.getPixel(right_.x, right_.y)),*(image_.getPixel(start_.x, start_.y)))<=tolerance_&&
      visited_[right_.x + right_.y * image_.width()]==false)traversal_->add(right_);
  }
  if(below_.x < image_.width() && below_.y < image_.height()){
    if(calculateDelta(*(image_.getPixel(below_.x, below_.y)),*(image_.getPixel(start_.x, start_.y)))<=tolerance_&&
      visited_[below_.x + below_.y * image_.width()]==false) traversal_->add(below_);
  }
  if(left_.x < image_.width() && left_.y < image_.height()){ 
    if(calculateDelta(*(image_.getPixel(left_.x, left_.y)),*(image_.getPixel(start_.x, start_.y)))<=tolerance_&&
      visited_[left_.x + left_.y * image_.width()]==false) traversal_->add(left_);
  }
  if(above_.x < image_.width() && above_.y < image_.height()){
    if(calculateDelta(*(image_.getPixel(above_.x, above_.y)),*(image_.getPixel(start_.x, start_.y)))<=tolerance_&&
      visited_[above_.x + above_.y * image_.width()]==false) traversal_->add(above_);
  }
  // move to next unexplored point
  while (!traversal_->empty() && visited_[traversal_->peek().x + traversal_->peek().y * image_.width()]==true) curr_ = traversal_->pop();
  // update return value
  if(!traversal_->empty()) curr_=traversal_->peek();
  else end_=true;
  return *this; 
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  // just to determine if the list is empty
  return !(end_&& other.end_);
}
