#include <string>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();

    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();

    // Create out.png
    PNG* output = new PNG(width,height);

    // iterate each pixel and reverse y and x axis
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned newX = width - 1 - x;
            unsigned newY = height - 1 - y;
            HSLAPixel* orig = original->getPixel(x,y);
            HSLAPixel* rev = output->getPixel(newX,newY);
            *rev = *orig;
        }
    }
    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete output;
    delete original;

}
