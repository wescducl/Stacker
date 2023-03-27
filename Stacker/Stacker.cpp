#include "stacker.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Stacker::Stacker(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    string line;
    getline(ifs, line);
    if (line != "P3") {
        cerr << "Invalid file format: " << line << endl;
        exit(1);
    }
    magic_number_ = line;

    getline(ifs, line);
    istringstream iss(line);
    iss >> width_ >> height_;
    if (width_ <= 0 || height_ <= 0) {
        cerr << "Invalid image dimensions: " << width_ << " x " << height_ << endl;
        exit(1);
    }

    getline(ifs, line);
    iss.clear();
    iss.str(line);
    iss >> max_color_;
    if (max_color_ <= 0 || max_color_ > 255) {
        cerr << "Invalid color depth: " << max_color_ << endl;
        exit(1);
    }

    int r, g, b;
    while (ifs >> r >> g >> b) {
        if (r < 0 || r > max_color_ || g < 0 || g > max_color_ || b < 0 || b > max_color_) {
            cerr << "Invalid pixel value: " << r << " " << g << " " << b << endl;
            exit(1);
        }
        pixels_.push_back({ r, g, b });
    }
}

void Stacker::stack(const string& prefix, int num_images) {
    for (int i = 2; i <= num_images; i++) {
        string filename = prefix + "/" + prefix + "_" + to_string(i) + ".ppm";
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "Error opening file " << filename << endl;
            exit(1);
        }

        string line;
        getline(ifs, line); // discard magic number
        getline(ifs, line); // discard dimensions
        getline(ifs, line); // discard color depth

        int r, g, b;
        for (int i = 0; i < width_ * height_; i++) {
            ifs >> r >> g >> b;
            pixels_[i].red += r;
            pixels_[i].green += g;
            pixels_[i].blue += b;
        }
    }

    for (int i = 0; i < width_ * height_; i++) {
        pixels_[i].red /= num_images;
        pixels_[i].green /= num_images;
        pixels_[i].blue /= num_images;
    }
}

void Stacker::save(const string& filename) const {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    ofs << magic_number_ << endl;
    ofs << width_ << " " << height_ << endl;
    ofs << max_color_ << endl;

    for (const auto& p : pixels_) {
        ofs << p.red << " " << p.green << " " << p.blue << endl;
    }
}