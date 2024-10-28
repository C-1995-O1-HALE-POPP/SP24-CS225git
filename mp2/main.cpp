#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;

int main() {

  Image base, meme, meme2;
  
  base.readFromFile("1.png");
  meme.readFromFile("meme.png");
  meme2.readFromFile("meme2.png");
  meme2.scale(150,200);
  StickerSheet output(base, 1);
  output.addSticker(meme, 500, 300);
  output.changeMaxStickers(5);
  output.addSticker(meme2, 200, 50);
  Image meme3=*(output.getSticker(0));
  meme3.scale(5);
  output.addSticker(meme3,100,100);
  Image meme4=*(output.getSticker(0));
  output.addSticker(meme4,0,0);
  output.removeSticker(3);
  Image meme5=*(output.getSticker(1));
  output.addSticker(meme5,0,0);
  output.translate(3,50,100);
  Image outputImage = output.render();
  outputImage.writeToFile("myImage.png");

  return 0;

}