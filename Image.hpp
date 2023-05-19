#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    // define private fields for image state
    Color **pixel_;
    int width_, height_;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void invert();
    void to_gray_scale();
    void replace(Color color1, Color color2);
    void fill(int x, int y, int w, int h, Color color);
    void h_mirror();
    void v_mirror();
    void add(const Image& image_to_add, Color neutral_color, int x, int y);
    void copy(const Image& from_image, int x, int y, int w, int h);
    void rotate_left(const Image& from_image);
    void rotate_right(const Image& from_image);
    void median_filter(const Image& from_image, int ws);
  };
}
#endif
