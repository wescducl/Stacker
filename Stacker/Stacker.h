
#ifndef STACKER_H
#define STACKER_H

#include <string>
#include <vector>

struct Pixel {
    int red;
    int green;
    int blue;
};

class Stacker {
public:
    Stacker(const std::string& filename);
    void stack(const std::string& prefix, int num_images);
    void save(const std::string& filename) const;

private:
    std::string magic_number_;
    int width_;
    int height_;
    int max_color_;
    std::vector<Pixel> pixels_;
};

#endif
