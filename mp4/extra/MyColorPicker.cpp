#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
MyColorPicker::MyColorPicker(HSLAPixel pixel, double amp, double increment)
  : hue_(pixel.h), saturation_(pixel.s), luminance_(pixel.l), increment_(increment),
    upper(amp+pixel.l>1.0? 1.0: amp+pixel.l), lower(pixel.l-amp<0.0? 0.0: pixel.l-amp){ }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue_, saturation_, luminance_);
  if(luminance_+increment_>upper){
    luminance_=upper;
    increment_=increment_*(-1.0);
  }else if(luminance_+increment_<lower){
    luminance_=lower;
    increment_=increment_*(-1.0);
  }else luminance_+=increment_;
  return pixel;
}
