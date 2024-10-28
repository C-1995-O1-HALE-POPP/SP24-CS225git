
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;
int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  

  
  PNG png;
  png.readFromFile("demo.png");
  
  FloodFilledImage image(png);
  BFS bfs1(png,Point(780,600),.15);
  DFS dfs2(png, Point(300,300), .15);
  HSLAPixel sample(200,1,.7);

  MyColorPicker my(sample,.2,.00001);
  RainbowColorPicker rainbow(.01);

  image.addFloodFill( bfs1, rainbow );
  image.addFloodFill( dfs2, my );

  Animation animation = image.animate(30000);

  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
