#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <vector>
#include <string>
#include <iostream>

#define EXPECTED_N 1
#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 16

#define PIXEL_EMPTY 0
#define PIXEL_FILLED 255

bool load_image(std::vector<unsigned char>& image, const std::string& filename);
bool check_black_white(const std::vector<unsigned char>& image);

inline unsigned char get_pixel(const std::vector<unsigned char>& image, int x, int y) {
    return image[y * IMAGE_WIDTH + x];
}


#endif // DISTANCE_H_