#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv) {
  Image wave, trees, temple, budapest1, budapest2, earth;
  // load all images
  if (!wave.load("../images/wave.png") || !trees.load("../images/trees.png")
        || !temple.load("../images/temple.png")
        || !budapest1.load("../images/budapest1.png")
        || !budapest2.load("../images/budapest2.png")
        || !earth.load("../images/earth.png")) {
    std::cout << "ERROR: failed to load image. Exiting..." << endl;
    exit(0);
  }

  // print dimensions
  printf("wave.png (%d x %d)\n", wave.width(), wave.height());
  printf("trees.png (%d x %d)\n", trees.width(), trees.height());
  printf("temple.png (%d x %d)\n", temple.width(), temple.height());
  printf("budapest1.png (%d x %d)\n", budapest1.width(), budapest1.height());
  printf("budapest2.png (%d x %d)\n", budapest2.width(), budapest2.height());
  printf("earth.png (%d x %d)\n", earth.width(), earth.height());

  Image swirl = temple.swirl().swirl();
  swirl.save("temple-swirl-swirl.png");

  Image waveAndTree = wave.add(trees);
  waveAndTree.save("wave-plus-trees.png");

  waveAndTree = wave.subtract(trees);
  waveAndTree.save("wave-minus-trees.png");

  waveAndTree = wave.multiply(trees);
  waveAndTree.save("wave-times-trees.png");

  waveAndTree = wave.difference(trees);
  waveAndTree.save("wave-minus-trees-abs.png");

  waveAndTree = wave.lightest(trees);
  waveAndTree.save("wave-trees-max.png");

  waveAndTree = wave.darkest(trees);
  waveAndTree.save("wave-trees-min.png");

  Image flip = earth.flipVertical();
  flip.save("earth-flip-vertical.png");

  Image rotated = budapest1.rotate90();
  rotated.save("budapest1-rotated.png");

  Image invert = budapest1.invert();
  invert.save("budapest1-invert.png");

  Image extract = budapest1.extractChannel(1);
  extract.save("budapest1-red.png");

  Image blur = earth.blur();
  blur.save("earth-blur.png");

  Image glow = earth.glow(200);
  glow.save("earth-glow.png");

  Image sobel = budapest1.sobelEdge();
  sobel.save("budapest1-sobel.png");

  invert = budapest1.grayscale().sobelEdge().invert();
  invert.save("budapest1-gray-sobel-invert.png");

  sobel = temple.sobelEdge();
  sobel.save("temple-sobel.png");

  sobel = budapest2.grayscale().invert().sobelEdge();
  sobel.save("budapest2-gray-invert-sobel.png");

  Image red = budapest1.subimage(166, 250, 166, 250).extractChannel(1);
  Image green = budapest1.subimage(332, 250, 166, 250).extractChannel(2);
  Image blue = budapest1.subimage(166, 500, 166, 250).extractChannel(3);
  Image orig = budapest1.subimage(332, 500, 166, 250);
  Image quad = budapest1.grayscale();
  quad.replace(red, 166, 250);
  quad.replace(green, 332, 250);
  quad.replace(blue, 166, 500);
  quad.replace(orig, 332, 500);
  quad.save("budapest1-quad.png");

  Image bitmap = budapest2.bitMap();
  bitmap.save("budapest2-bitmap.png");

  Image templeSubimage = temple.subimage(200, 125, 400, 250);
  Image treesSubimage = trees.subimage(300, 150, 400, 250);
  Image blend = templeSubimage.alphaBlend(treesSubimage, 0.35f);
  trees.replace(blend, 300, 150);
  trees.save("trees-temple-blend.png");
  
  return 0;
}

