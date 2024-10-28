#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(HSLAPixel pixel, double amp, double increment);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  double hue_, saturation_, luminance_, increment_,upper, lower;
};

#endif
