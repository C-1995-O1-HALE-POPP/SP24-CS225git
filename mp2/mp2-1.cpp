#include "Image.h"

using namespace cs225;

int main() {
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");
  
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");
  alma.readFromFile("alma.png");

  alma.scale(.5);
  alma.writeToFile("scale.5.png");
  alma.readFromFile("alma.png");

  alma.lighten();
  alma.writeToFile("lighten_default.png");
  
  alma.readFromFile("alma.png");
  alma.saturate();
  alma.writeToFile("saturate_default.png");

  alma.readFromFile("alma.png");
  alma.darken(0.2);
  alma.writeToFile("darken.png");
  
  alma.readFromFile("alma.png");
  alma.desaturate(0.2);
  alma.writeToFile("desaturate.png");

  alma.readFromFile("alma.png");
  alma.darken();
  alma.writeToFile("darken_default.png");
  
  alma.readFromFile("alma.png");
  alma.desaturate();
  alma.writeToFile("desaturate_default.png");

  alma.readFromFile("alma.png");
  alma.scale(114,514);
  alma.writeToFile("scale114514.png");
  
  alma.readFromFile("alma.png");
  alma.grayscale();
  alma.writeToFile("grayscale.png");

  alma.readFromFile("alma.png");
  alma.illinify();
  alma.writeToFile("illinify.png");
  
  alma.readFromFile("alma.png");
  alma.rotateColor(90);
  alma.writeToFile("rotateColor90.png");

  alma.readFromFile("alma.png");
  alma.rotateColor(270);
  alma.writeToFile("rotateColor270.png");


  alma.readFromFile("alma.png");
  alma.rotateColor(45);
  alma.writeToFile("rotateColor45.png");

  alma.readFromFile("alma.png");
  alma.scale(114,514);
  alma.writeToFile("scale114514.png");

  return 0;
}