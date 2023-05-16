#include "Image.hpp"

namespace prog
{
  // Constructor for a single color image
  Image::Image(int w, int h, const Color &fill) {
    // Allocate memory for the colors_ 2D array
    colors_ = new Color*[w];
    for (int i = 0; i < w; i++) {
      colors_[i] = new Color[h];
    }

    // Change all color items with the "fill" color
    for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
        colors_[i][j] = fill;
      }
    }
    
    // Set private variables
    width_ = w;
    height_ = h;
  }

  // Destructor
  Image::~Image() {
    // Free the memory allocated for the colors_ 2D array
    for (int i = 0; i < width_; i++) {
      delete[] colors_[i];
    }
    delete[] colors_;
  }

  // Const member function
  int Image::width() const {
    return width_;
  }

  // Const member function
  int Image::height() const {
    return height_;
  }

  // Member function
  Color& Image::at(int x, int y) {
    return colors_[x][y];
  }

  // Const member function
  const Color& Image::at(int x, int y) const {
    return colors_[x][y];
  }

  // Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b) -> invert image
  void Image::invert() {
    for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        colors_[i][j].invert();
      }
    }
  }

  // Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3 -> convert an image to gray scale
  void Image::to_gray_scale() {
    for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        colors_[i][j].to_gray_scale();
      }
    }
  }

  // Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2) -> change a color in the whole image
  void Image::replace(Color color1, Color color2) {
   for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        if (colors_[i][j] == color1)
          colors_[i][j] = color2;
      }
    }
  }

  // Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h
  void Image::fill(int x, int y, int w, int h, Color color) {
   for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        if ((x <= i) && (i < x + w) && (y <= j) && (j < y + h)) {
          colors_[i][j] = color;
        }
      }
    }
  }

  // Pixels (x, y) and (width() - 1 - x, y) for all 0 <= x < width() / 2 and 0 <= y < height().
  void Image::h_mirror() {
   Color tmp;
   for (int i = 0; i < width_ / 2; i++) {
      for (int j = 0; j < height_; j++) {
        tmp = colors_[i][j];
        colors_[i][j] = colors_[width_ -1 -i][j];
        colors_[width_ -1 -i][j] = tmp;
      }
    }
  }

  // Pixels (x, y) and (x, height() - 1 - y) for all 0 <= x < width() and 0 <= y < height() / 2.
  void Image::v_mirror() {
   Color tmp;
   for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_ / 2; j++) {
        tmp = colors_[i][j];
        colors_[i][j] = colors_[i][height_ -1 -j];
        colors_[i][height_ -1 -j] = tmp;
      }
    }
  }

  // Copy all pixels from image stored in PNG file filename, except pixels in that image with “neutral” color (r, g, b), to the rectangle of the current image with top-left corner (x, y) of the current image.
  void Image::add(const Image& image_to_add, Color neutral_color, int x, int y) {
   for (int i = 0; i < image_to_add.width_; i++) {
      for (int j = 0; j < image_to_add.height_; j++) {
        if(image_to_add.colors_[i][j] != neutral_color) {
          colors_[x+i][y+j] = image_to_add.colors_[i][j];
        }
      }
    }
  }

  // Copy from_image starting at (x,y) for given width and height. 
  void Image::copy(const Image& from_image, int x, int y, int w, int h) {
   for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
          colors_[i][j] = from_image.colors_[i+x][j+y];
      }
    }
  }

  // Copy from_image rotating coordinates left by 90 degrees.
  void Image::rotate_left(const Image& from_image) {
    for (int i = 0; i < height_; i++) {
      for (int j = 0; j < width_; j++) {
          colors_[j][height_ - i - 1] = from_image.colors_[i][j];
      }
    }
  }

  // Copy from_image rotating coordinates right by 90 degrees.
  void Image::rotate_right(const Image& from_image) {
    for (int i = 0; i < height_; i++) {
      for (int j = 0; j < width_; j++) {
          colors_[width_ - j - 1][i] = from_image.colors_[i][j];
      }
    }
  }
}
