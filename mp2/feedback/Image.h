#ifndef IMAGE_H
#define IMAGE_H

// The headfile of the Image class
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include "cs225/PNG.h"
using namespace std;
namespace cs225
{
    class Image: public cs225::PNG
    {
    public:
        Image(): PNG(){};
        Image(unsigned w,unsigned h): PNG(w,h){};
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
    };
    
} // namespace name
#endif