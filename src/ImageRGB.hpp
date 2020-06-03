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
    /**
     * Constructor of ImageRGB reserves memory for the m_Data vector.
     *
     * @param height    Height of the image.
     * @param width     Width of the image.
     */
    ImageRGB(size_t height, size_t width);

    /**
     * This method sets a defined pixel to an RGB value.
     *
     * @param height  Height of the pixel.
     * @param width   Width of the pixel.
     * @param red     Red value of the pixel.
     * @param green   Green value of the pixel.
     * @param blue    Blue value of the pixel.
     */
    void insert_to(size_t height, size_t width, unsigned char red, unsigned char green, unsigned char blue)
    { m_Data[height][width] = RGB{red, green, blue}; }

    /**
     * This method converts the RGB image into an ASCII text of a maximum width.
     *
     * @param max_width     Maximum width of the ASCII image.
     * @return              The ASCII image.
     */
    ImageASCII to_ascii(size_t max_width, bool invert) const;

private:
    std::vector< std::vector<RGB> > m_Data;
    size_t m_Height;
    size_t m_Width;
};

