// Base code Copyright 2021, Aline Normoyle, alinen

/* image.cpp
 *
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


Image::Image() {  }

Image::Image(int width, int height): _width(width), _height(height) {
  _pixels = (struct Pixel *) malloc(sizeof(struct Pixel *) * width * height);
  _need_to_free_malloc = true;
}

Image::Image(const Image& orig) {
  _width = orig._width;
  _height = orig._height;
  _components = orig._components;
  _pixels = orig._pixels;
}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }
  _width = orig._width;
  _height = orig._height;
  _components = orig._components;
  _pixels = orig._pixels;
  return *this;
}

Image::~Image() {
  if (_need_to_free_stbi) {
    // was allocated by stbi_load, need to stbi free
    stbi_image_free(_pixels);
  } else if (_need_to_free_malloc) {
    // was malloc-ed, need to free
    free(_pixels);
  }
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
  _width = width;
  _height = height;
  _pixels = (struct Pixel *) data;
}

bool Image::load(const std::string& filename, bool flip) {
  // if flip = true, will set stbi's flip variable to true also
  // auto conversion to bool (false = 0, true = 1)
  stbi_set_flip_vertically_on_load(flip);
  // stbi_load returns unsigned char *, so must cast to struct Pixel *
  // also must convert filename from string to char *
  _pixels = (struct Pixel *) stbi_load(filename.c_str(), &_width, &_height,
      &_components, 3);
  _need_to_free_stbi = true;
  // reset to false for future calls
  stbi_set_flip_vertically_on_load(false);
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
      (void *) _pixels, sizeof(struct Pixel) * _width);
  // reset to false for future calls
  stbi_flip_vertically_on_write(flip);
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
      result.set(i, j, get(orig_row, orig_col));
    }
  }
  return result;
}

Image Image::flipHorizontal() const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      result.set(i, j, get(_height - 1 - i, j));
    }
  }
  return result;
}

Image Image::flipVertical() const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
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
  for (int i = 0; i < _height - starty; i++) {
    for (int j = 0; j < _width - startx; j++) {
      set(starty + i, startx + j, image.get(i, j));
    }
  }
}

Image Image::gammaCorrect(float gamma) const {
  Image result(_width, _height);
  for (int i = 0; i < _height; i++) {
    for (int j = 0; j < _width; j++) {
      struct Pixel pixel = get(i,j);  // copy original pixel
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
      struct Pixel under = get(i,j);  // background pixel from this image
      struct Pixel over = other.get(i, j);  // foreground pixel from other image
      unsigned char new_red = round((over.r * alpha) + (under.r * (1 - alpha)));
      unsigned char new_green = round((over.g * alpha) + (under.g * (1 - alpha)));
      unsigned char new_blue = round((over.b * alpha) + (under.b * (1 - alpha)));
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
