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
        red_ = red;
        green_ = green;
        blue_ = blue;
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

    rgb_value& Color::red()  {
        return red_;
    }
    rgb_value& Color::green()  {
      return green_;
    }
    rgb_value& Color::blue()  {
      return blue_;
    }
}
