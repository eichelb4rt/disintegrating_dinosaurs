#include "images.h"
// needed for stb_image to work
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool load_image(std::vector<unsigned char>& image, const std::string& filename) {
    int x, y, n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, EXPECTED_N);
    if (n != EXPECTED_N || x != IMAGE_WIDTH || y != IMAGE_HEIGHT) {
        return false;
    }
    // std::cout << "x: " << x << std::endl << "y: " << y << std::endl << "n: " << n << std::endl;
    if (data != nullptr) {
        image = std::vector<unsigned char>(data, data + x * y);
    }
    stbi_image_free(data);
    return data != nullptr;
}

bool check_black_white(const std::vector<unsigned char>& image) {
    unsigned char pixel;
    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            pixel = get_pixel(image, x, y);
            if (!(pixel == PIXEL_EMPTY || pixel == PIXEL_FILLED))
                return false;
        }
    }
    return true;
}