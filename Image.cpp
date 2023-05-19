#include "Image.hpp"
#include <vector>
#include <algorithm>

namespace prog
{
  // Constructor for a single color image
  Image::Image(int w, int h, const Color &fill)

    // Set private variables 
    : pixel_(new Color*[w]), width_(w), height_(h) {

    // Allocate memory for the pixel_ 2D array
    for (int i = 0; i < w; i++) {
      pixel_[i] = new Color[h];
    }

    // Change all color items with the "fill" color
    for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
        pixel_[i][j] = fill;
      }
    }
  }

  // Destructor
  Image::~Image() {
    // Free the memory allocated for the pixel_ 2D array
    if (pixel_ != nullptr) {
      for (int i = 0; i < width_; i++) {
        delete[] pixel_[i];
      }
    delete[] pixel_;
    }
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
      return pixel_[x][y];
  }

  // Const member function
  const Color& Image::at(int x, int y) const {
      return pixel_[x][y];
  }

  // Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b) -> invert image
  void Image::invert() {
    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {
        pixel_[x][y].invert();
      }
    }
  }

  // Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3 -> convert an image to gray scale
  void Image::to_gray_scale() {
    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {
        pixel_[x][y].to_gray_scale();
      }
    }
  }

  // Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2) -> change a color in the whole image
  void Image::replace(Color color1, Color color2) {
    if (color1 != color2) {
      for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
          if (pixel_[x][y] == color1)
            pixel_[x][y] = color2;
        }
      }
    }
  }

  // Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h
  void Image::fill(int x, int y, int w, int h, Color color) {
    bool limites_do_retangulo;
    for (int i = 0; i < width_; i++) {
      for (int j = 0; j < height_; j++) {
        limites_do_retangulo = (x <= i) && (i < x + w) && (y <= j) && (j < y + h);
        if (limites_do_retangulo) {
          pixel_[i][j] = color;
        }
      }
    }
  }

  // Pixels (x, y) and (width() - 1 - x, y) for all 0 <= x < width() / 2 and 0 <= y < height().
  void Image::h_mirror() {
    for (int x = 0; x < width_ / 2; x++) {
      for (int y = 0; y < height_; y++) {
        Color tmp = pixel_[x][y];
        pixel_[x][y] = pixel_[width_ - 1 - x][y];
        pixel_[width_ - 1 - x][y] = tmp;
      }
    }
  }

  // Pixels (x, y) and (x, height() - 1 - y) for all 0 <= x < width() and 0 <= y < height() / 2.
  void Image::v_mirror() {
    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_ / 2; y++) {
        Color tmp = pixel_[x][y];
        pixel_[x][y] = pixel_[x][height_ - 1 - y];
        pixel_[x][height_ - 1 - y] = tmp;
      }
    }
  }

  // Copy all pixels from image stored in PNG file filename, except pixels in that image with “neutral” color (r, g, b), to the rectangle of the current image with top-left corner (x, y) of the current image.
  void Image::add(const Image& image_to_add, Color neutral_color, int x, int y) {
    for (int i = 0; i < image_to_add.width_; i++) {
      for (int j = 0; j < image_to_add.height_; j++) {
        if ((x + i >= 0 && x + i < width_) && (y + j >= 0 && y + j < height_)) {
          if(image_to_add.pixel_[i][j] != neutral_color) {
            pixel_[x+i][y+j] = image_to_add.pixel_[i][j];
          }
        }
      }
    }
  }

  // Copy from_image starting at (x,y) for given width and height. 
  void Image::copy(const Image& from_image, int x, int y, int w, int h) {
    for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
        if ((i + x >= 0 && i + x < from_image.width_) && (j + y >= 0 && j + y < from_image.height_))
          pixel_[i][j] = from_image.pixel_[i+x][j+y];
      }
    }
  }

  // Copy from_image rotating coordinates left by 90 degrees.
  void Image::rotate_left(const Image& from_image) {
    for (int y = 0; y < height_; y++) {
      for (int x = 0; x < width_; x++) {
          pixel_[x][height_ - y - 1] = from_image.pixel_[y][x];
      }
    }
  }

  // Copy from_image rotating coordinates right by 90 degrees.
  void Image::rotate_right(const Image& from_image) {
    for (int y = 0; y < height_; y++) {
      for (int x = 0; x < width_; x++) {
          pixel_[width_ - x - 1][y] = from_image.pixel_[y][x];
      }
    }
  }

  // Apply a median filter with window size ws >= 3 to the current image.
  void Image::median_filter(const Image& from_image, int ws) {
    std::vector<int> redValues(ws * ws);
    std::vector<int> greenValues(ws * ws);
    std::vector<int> blueValues(ws * ws);

    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {

        int vector_size = 0;
        redValues.clear();
        greenValues.clear();
        blueValues.clear();

        for (int nx = std::max(0, x - ws / 2); nx <= std::min(width() - 1, x + ws / 2); nx++) {
          for (int ny = std::max(0, y - ws / 2); ny <= std::min(height() - 1, y + ws / 2); ny++) {

            redValues.push_back(from_image.pixel_[nx][ny].red());
            greenValues.push_back(from_image.pixel_[nx][ny].green());
            blueValues.push_back(from_image.pixel_[nx][ny].blue());
            vector_size++;
          }
        }

        sort(redValues.begin(), redValues.end());
        sort(greenValues.begin(), greenValues.end());
        sort(blueValues.begin(), blueValues.end());

        int middle_index = vector_size / 2;
        int red, green, blue;

        if (vector_size % 2 == 0) {
          red = (redValues[middle_index - 1] + redValues[middle_index]) / 2;
          green = (greenValues[middle_index - 1] + greenValues[middle_index]) / 2;
          blue = (blueValues[middle_index - 1] + blueValues[middle_index]) / 2;
        }
        else {
          red = redValues[middle_index];
          green = greenValues[middle_index];
          blue = blueValues[middle_index];
        }

        pixel_[x][y] = Color(red, green, blue);
      }
    }
  }
}
