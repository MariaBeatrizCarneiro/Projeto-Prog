#include "XPM2.hpp"
#include <fstream>
#include <map>
using namespace std;

namespace prog {
    const string xpm2_header = "! XPM2";
    const int chars_per_color = 1;
    const char color_entry_type = 'c';

    Image* loadFromXPM2(const string& file) {
        
        ifstream infile;
        infile.open(file, ios::in);

        if(!infile.good())
            return nullptr;

        string file_header;
        getline(infile, file_header);
        
        cout << "file header: " << file_header << endl;

        if (file_header != xpm2_header)
            return nullptr;
        
        int w, h, n, c;
        infile >> w >> h >> n >> c;
        
        cout << "w: " << w << endl;
        cout << "h: " << h << endl;
        cout << "n: " << n << endl;
        cout << "c: " << c << endl;

        if (c != chars_per_color)
            return nullptr;

        char color_key, entry_type;
        string hexcode;
        rgb_value red, green, blue;
        Color color;
        map<char, Color> color_map;

        for(int i = 0; i < n; i++) {
            infile >> color_key >> entry_type >> hexcode;
            cout << "color_key: " << color_key << endl;
            cout << "entry_type: " << entry_type << endl;
            cout << "hexcode: " << hexcode << endl;

            if (entry_type != color_entry_type)
                return nullptr;

            red = (rgb_value)stoi(hexcode.substr(1, 2), 0, 16);
            green = (rgb_value)stoi(hexcode.substr(3, 2), 0, 16);
            blue = (rgb_value)stoi(hexcode.substr(5, 2), 0, 16);

            cout << "red: " << (int)red << endl;
            cout << "green: " << (int)green << endl;
            cout << "blue: " << (int)blue << endl;

            color = {red, green, blue};

            color_map[color_key] = color;
        }

        map<char, Color>::iterator it = color_map.begin();
        while(it != color_map.end()) {
            cout << "Color: " << it->first << " (" << (int)(it->second).red() << "," << (int)(it->second).green() << "," << (int)(it->second).blue() << ")" << endl;
            ++it;
        }

        Image *image = new Image(w, h);
        char clr_key;

        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                infile >> clr_key;
                image -> at(x, y) = color_map.at(clr_key);
            }
        }

        return image;
    }









    void saveToXPM2(const string& file, const Image* image) {
        ofstream outfile(file);
        
        if(!outfile.good())
            return;

        string file_header;
        
        // Write File Header
        outfile << xpm2_header << endl;

        int w, h, n;
        w = image->width();
        h = image->height();

        map<Color, char> color_map;
        Color color;

        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                Color color = image -> at(x, y);
                color_map[color] = ' ';
            }
        }

        
        n = color_map.size();
        
        // Write image dimensions and number of colors.
        outfile << w << " " << h << " " << n << " " << chars_per_color << endl;

        cout << "n: " << n << endl;

        map<Color, char>::iterator it = color_map.begin();
        int ascii_val = 33;
        char color_key;

        while(it != color_map.end()) {
            color_key = char(ascii_val);

            it->second = color_key;

            outfile << color_key << " " << color_entry_type << " #";
            outfile << setfill('0') << setw(2) << hex << (int)it->first.red();
            outfile << setfill('0') << setw(2) << hex << (int)it->first.green();
            outfile << setfill('0') << setw(2) << hex << (int)it->first.blue() << endl;


            ++it;
            ascii_val++;
        }

        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                color = image -> at(x, y);
                auto it = color_map.find(color);
                outfile << it->second;
            }
            outfile << endl;
        }

        outfile.close();
        return;
    }
}
