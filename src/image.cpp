// Base code Copyright 2021, Aline Normoyle, alinen

/* image.cpp
 * Implementation of an Image class that uses the STB library to load an image
 * into a pixel representation and provides functions to transform the image
 * (e.g. color changes, resizing, cropping, blending, etc.); also allows
 * user to save/write the result to a .png file
 * JL
 * February 2, 2023
 *
 * STB documentation can be found at
 * https://github.com/nothings/stb/
 */

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl {

// helper function to free pixels
void Image::resetPixels() {
  if (_pixels != NULL) {
    _width = 0;
    _height = 0;
    _components = 0;
    if (_use_stbi_free) {
      // allocated with stbi_load, so must free with stbi_image_free
      stbi_image_free(_pixels);
      _use_stbi_free = false;
    } else {
      // regular array deallocation
      delete[] _pixels;
    }
    _pixels = NULL;
  }
}

// if no width/height provided, no need set instance variables
Image::Image() {  }

Image::Image(int width, int height): _width(width), _height(height) {
  resetPixels();
  _pixels = new struct Pixel[width * height];
}

Image::Image(const Image& orig) {
  resetPixels();
  _width = orig._width;
  _height = orig._height;
  _components = orig._components;
  _pixels = new struct Pixel[_width * _height];
  memcpy(_pixels, orig._pixels, sizeof(struct Pixel) * _width * _height);
}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }
  resetPixels();
  _width = orig._width;
  _height = orig._height;
  _components = orig._components;
  _pixels = new struct Pixel[_width * _height];
  memcpy(_pixels, orig._pixels, sizeof(struct Pixel) * _width * _height);
  return *this;
}

Image::~Image() {
  // must free pixel memory
  resetPixels();
}

int Image::width() const {
  return _width;
}

int Image::height() const {
  return _height;
}

char* Image::data() const {
  return (char *) _pixels;
}

void Image::set(int width, int height, unsigned char* data) {
  resetPixels();
  _width = width;
  _height = height;
  _pixels = new struct Pixel[_width * _height];
  memcpy(_pixels, data, sizeof(struct Pixel) * _width * _height);
}

bool Image::load(const std::string& filename, bool flip) {
  // if flip = true, will set stbi's flip variable to true also
  // auto conversion to bool (false = 0, true = 1)
  stbi_set_flip_vertically_on_load(flip);
  // free pixel memory first
  resetPixels();
  // stbi_load returns unsigned char *, so must cast to struct Pixel *
  // also must convert filename from string to char *
  // requesting only 3 channels (RGB)
  _pixels = (struct Pixel *) stbi_load(filename.c_str(), &_width, &_height,
      &_components, 3);
  _use_stbi_free = true;
  if (_pixels == NULL) {
    // allocation failure
    return false;
  } else {
    // successful load
    return true;
  }
}

bool Image::save(const std::string& filename, bool flip) const {
  // if flip = true, will set stbi's flip variable to true also
  stbi_flip_vertically_on_write(flip);
  int result = stbi_write_png(filename.c_str(), _width, _height, 3,
      _pixels, sizeof(struct Pixel) * _width);
  if (result == 0) {
    // failed to write file
    return false;
  } else {
    // successful write
    return true;
  }
}

Pixel Image::get(int row, int col) const {
  return _pixels[row * _width + col];
}

void Image::set(int row, int col, const Pixel& color) {
  _pixels[row * _width + col] = color;
}

Pixel Image::get(int i) const {
  return _pixels[i];
}

void Image::set(int i, const Pixel& c) {
  _pixels[i] = c;
}

Image Image::resize(int w, int h) const {
  Image result(w, h);
  for (int i = 0; i < h; i++) {
    float row_ratio = (float) i / (h - 1);
    int orig_row = floor(row_ratio * (_height - 1));
    for (int j = 0; j < w; j++) {
      float col_ratio = (float) j / (w - 1);
      int orig_col = floor(col_ratio * (_width - 1));
      // set new pixel to old pixel at the same relative position
      //   in the old image, proportionally
      result.set(i, j, get(orig_row, orig_col));
    }
  }
  return result;
}

Image Image::flipHorizontal() const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      // set new pixel to old pixel in mirrored half, folded horizontally
      result.set(i, j, get(_height - 1 - i, j));
    }
  }
  return result;
}

Image Image::flipVertical() const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      // set new pixel to old pixel in mirrored half, folded vertically
      result.set(i, j, get(i, _width - 1 - j));
    }
  }
  return result;
}

Image Image::rotate90() const {
  Image result(_height, _width);
  // width and height are switched (b/c image is transposed)
  for (int i = 0; i < _width; i++) {
    for (int j = 0; j < _height; j++) {
      result.set(i, j, get(j, _width - 1 - i));
    }
  }
  return result;
}

Image Image::subimage(int startx, int starty, int w, int h) const {
  Image sub(w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      sub.set(i, j, get(starty + i, startx + j));
    }
  }
  return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
  // only replace as many pixels as will fit onto original image
  int rows = std::min(_height - starty, image.height()); // num rows to replace
  int cols = std::min(_width - startx, image.width());  // num cols to replace
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      set(starty + i, startx + j, image.get(i, j));
    }
  }
}

Image Image::gammaCorrect(float gamma) const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      struct Pixel pixel = get(i, j);  // copy original pixel
      // RGB values must be converted to float in range [0, 1.0] first
      pixel.r = round(pow((pixel.r / 255.0f), 1.0f / gamma) * 255.0f);
      pixel.g = round(pow((pixel.g / 255.0f), 1.0f / gamma) * 255.0f);
      pixel.b = round(pow((pixel.b / 255.0f), 1.0f / gamma) * 255.0f);
      result.set(i, j, pixel);
    }
  }
  return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      struct Pixel under = get(i,j);  // back pixel from this image
      struct Pixel over = other.get(i, j);  // fore pixel from other image
      unsigned char new_red = round((over.r * alpha) +
                                    (under.r * (1 - alpha)));
      unsigned char new_green = round((over.g * alpha) +
                                      (under.g * (1 - alpha)));
      unsigned char new_blue = round((over.b * alpha) +
                                     (under.b * (1 - alpha)));
      struct Pixel corrected = {new_red, new_green, new_blue};
      result.set(i, j, corrected);
    }
  }
  return result;
}

Image Image::grayscale() const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      struct Pixel orig = get(i,j);
      unsigned char intensity = round((orig.r * 0.3) + (orig.g * 0.59) +
          (orig.b * 0.11));  // weighted average
      struct Pixel corrected = {intensity, intensity, intensity};
      result.set(i, j, corrected);
    }
  }
  return result;
}

Image Image::add(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::subtract(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::multiply(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::difference(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::swirl() const {
  Image result(0, 0);
  return result;
}

Image Image::lightest(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::darkest(const Image& other) const {
  Image result(0, 0);

  return result;
}

Image Image::invert() const {
  Image image(0, 0);

  return image;
}

Image Image::colorJitter(int size) const {
  Image image(0, 0);

  return image;
}

Image Image::bitmap(int size) const {
  Image image(0, 0);

  return image;
}

void Image::fill(const Pixel& c) {

}


}  // namespace agl
