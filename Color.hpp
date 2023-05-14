#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      // private fields required for color representation.
      rgb_value red_, green_, blue_;
    public:
      Color();
      Color(const Color& c);
      Color(rgb_value r, rgb_value g, rgb_value b);
      bool operator==(const Color& other) const;
      bool operator!=(const Color& other) const;
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
      void invert();
      void to_gray_scale();
  };
}
#endif
