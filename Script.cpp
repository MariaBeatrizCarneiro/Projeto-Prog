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

            if (command == "v_mirror") {
                v_mirror();
                continue;
            }

            if (command == "add") {
                add();
                continue;
            }

            if (command == "crop") {
                crop();
                continue;
            }

            if (command == "rotate_left") {
                rotate_left();
                continue;
            }

            if (command == "rotate_right") {
                rotate_right();
                continue;
            }

            if (command == "median_filter") {
                median_filter();
                continue;
            }

            if (command == "xpm2_open") {
                xpm2_open();
                continue;
            }

            if (command == "xpm2_save") {
                xpm2_save();
                continue;
            }
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

    void Script::v_mirror() {
        // Mirror image vertically
        image->v_mirror();
    }

    void Script::add() {
        // Copy all pixels from image stored in PNG file filename, except pixels in that image with “neutral” color (r, g, b), to the rectangle of the current image with top-left corner (x, y) of the current image.
        Color neutral_color;
        Image *image_to_add;
        int x, y;
        string filename;

        // Read inputs
        input >> filename >> neutral_color >> x >> y;

        // Load image_to_add and process
        image_to_add = loadFromPNG(filename);
        image->add(*image_to_add, neutral_color, x, y);

        // Free memory
        delete image_to_add;
    }

    void Script::crop() {
        // Crop the image, reducing it to all pixels contained in the rectangle defined by top-left corner (x, y), width w, and height h.
        int x, y, w, h;

        input >> x >> y >> w >> h;

        Image *new_image = new Image(w, h);
        new_image->copy(*image, x, y, w, h);

        // Swap image pointers
        Image *image_to_delete = image;
        image = new_image;

        delete image_to_delete;
    }

    void Script::rotate_left() {
        // Rotate image left by 90 degrees.
        int new_image_width = image->height();
        int new_image_height = image->width();

        Image *new_image = new Image(new_image_width, new_image_height);
        new_image->rotate_left(*image);

        // Swap image pointers
        Image *image_to_delete = image;
        image = new_image;

        delete image_to_delete;
    }

    void Script::rotate_right() {
        // Rotate image right by 90 degrees.
        int new_image_width = image->height();
        int new_image_height = image->width();

        Image *new_image = new Image(new_image_width, new_image_height);
        new_image->rotate_right(*image);

        // Swap image pointers
        Image *image_to_delete = image;
        image = new_image;

        delete image_to_delete;
    }

    void Script::median_filter() {
        // Apply a median filter with window size ws >= 3 to the current image.
        int ws;
        input >> ws;

        Image *new_image = new Image(image->width(),image->height());
        new_image->median_filter(*image, ws);

        // Swap image pointers
        Image *image_to_delete = image;
        image = new_image;

        delete image_to_delete;
    }

    void Script::xpm2_open() {
        // Replace current image (if any) with image read from XPM2 file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }

    void Script::xpm2_save() {
        // Save current image to XPM2 file.
        string filename;
        input >> filename;
        saveToXPM2(filename, image);
    }
}
