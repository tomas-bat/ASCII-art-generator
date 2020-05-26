/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 24/05/2020
 */
#pragma once

#include <vector>
#include "ImageASCII.hpp"

struct RGB {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

/**
 * Class to represent an universal RGB image.
 */
class ImageRGB {
public:
    ImageRGB(size_t height, size_t width);

    void insert_to(size_t height, size_t width, unsigned char red, unsigned char green, unsigned char blue)
    { m_Data[height][width] = RGB{red, green, blue}; }

    void test_print() const;

    ImageASCII to_ascii() const;
private:
    std::vector< std::vector<RGB> > m_Data;
    size_t m_Width;
    size_t m_Height;
};

