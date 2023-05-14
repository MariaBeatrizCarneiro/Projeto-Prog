#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    // define private fields for image state
    Color **colors_;
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
  };
}
#endif
