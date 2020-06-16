/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 24/05/2020
 */
#pragma once

#include <vector>
#include "ImageASCII.hpp"

/**
 * This struct represents one RGB pixel.
 */
struct RGB {
    /**
     * Red value of the pixel (0-255)
     */
    unsigned char R;

    /**
      * Green value of the pixel (0-255)
      */
    unsigned char G;

    /**
     * Blue value of the pixel (0-255)
     */
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
     * @param[in] height    Height of the image.
     * @param[in] width     Width of the image.
     */
    ImageRGB(size_t height, size_t width);

    /**
     * This method sets a defined pixel to an RGB value.
     *
     * @param[in] height  Height of the pixel.
     * @param[in] width   Width of the pixel.
     * @param[in] red     Red value of the pixel.
     * @param[in] green   Green value of the pixel.
     * @param[in] blue    Blue value of the pixel.
     */
    void insert_to(size_t height, size_t width, unsigned char red, unsigned char green, unsigned char blue) noexcept
    { m_Data[height][width] = RGB{red, green, blue}; }

    /**
     * This method converts the RGB image into an ASCII text of a maximum width.
     *
     * @param[in] max_width     Maximum width of the ASCII image.
     * @param[in] invert        Dark/bright terminal.
     * @param[in] transition    Transition char set.
     * @param[in] inverted      Inverted transition char set.
     * @return                  The ASCII image.
     */
    ImageASCII to_ascii(size_t max_width, bool invert, const std::string& transition, const std::string& inverted) const;

private:
    /**
     * This 2D vector stores all pixels of the image.
     */
    std::vector< std::vector<RGB> > m_Data;

    /**
     * Height of the image in pixels.
     */
    size_t m_Height;

    /**
     * Width of the image in pixels.
     */
    size_t m_Width;
};

