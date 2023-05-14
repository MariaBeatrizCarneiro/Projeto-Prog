#include "Color.hpp"

namespace prog {

    // Default constructor
    Color::Color() {
        red_ = green_ = blue_ = 0;
    }

    // Copy constructor
    Color::Color(const Color& other) {
        red_ = other.red();
        green_ = other.green();
        blue_ = other.blue();
    }

    // Constructor with individual attributes
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        // Set private variables
        red_ = red;
        green_ = green;
        blue_ = blue;
    }

    // Equality operator -> test if equal
    bool Color::operator==(const Color& other) const {
        return (red_ == other.red_) && (green_ == other.green_) && (blue_ == other.blue_);
    }

    // Equality operator -> test if different
    bool Color::operator!=(const Color& other) const {
        return !operator==(other);
    }

    // Const member function
    rgb_value Color::red() const {
        return red_;
    }

    // Const member function
    rgb_value Color::green() const {
        return green_;
    }

    // Const member function
    rgb_value Color::blue() const {
        return blue_;
    }

    // Member function
    rgb_value& Color::red()  {
        return red_;
    }

    // Member function
    rgb_value& Color::green()  {
      return green_;
    }

    // Member function
    rgb_value& Color::blue()  {
      return blue_;
    }

    // Invert a color
    void Color::invert() {
        red_ = 255 - red_;
        green_ = 255 - green_;
        blue_ = 255 - blue_;
    }

    // Convert a color to gray scale
    void Color::to_gray_scale() {
        // Integer (unsigned char) division without rounding
        rgb_value v = (red_ + green_ + blue_) / 3;

        red_ = green_ = blue_ = v;
    }
}
