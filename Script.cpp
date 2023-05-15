#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
        image(nullptr), input(filename) {
        
    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }

            if (command == "invert") {
                invert();
                continue;
            }

            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }

            if (command == "replace") {
                replace();
                continue;
            }

            if (command == "fill") {
                fill();
                continue;
            }

            if (command == "h_mirror") {
                h_mirror();
                continue;
            }

            // TODO ...

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert() {
        // Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b).
        image->invert();
    }
    void Script::to_gray_scale() {
        // Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3.
        image->to_gray_scale();
    }
    void Script::replace() {
        // Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2).
        Color color1, color2;
        input >> color1 >> color2;
        image->replace(color1, color2);
    }
    void Script::fill() {
        // Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h.
        Color color;
        int x, y, w, h;
        input >> x >> y >> w >> h >> color;
        image->fill(x, y, w, h, color);
    }

    void Script::h_mirror() {
        // Mirror image horizontally.
        image->h_mirror();
    }
}
