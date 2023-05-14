#include "Image.hpp"
#include <iostream>
using namespace std;

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

  void Image::invert() {
    cout << "inverting image" << endl;

    for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        colors_[i][j].invert();
      }
    }
  }
}
