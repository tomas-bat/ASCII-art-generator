/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 24/05/2020
 */

#include <iostream>
#include <string>
#include "ImageRGB.hpp"

using namespace std;

char get_char(int gray_value, bool invert, const string& transition, const string& inverted) {
    // chars, chars_len and interval are called many times during the conversion and they are not modified
    const static double chars_len = transition.size();
    const static double invert_chars_len = inverted.size();
    const static double interval = chars_len/256;
    const static double invert_interval = invert_chars_len/256;
    if (invert)
        return inverted[gray_value * invert_interval];
    return transition[gray_value * interval];
}

ImageRGB::ImageRGB(size_t height, size_t width) : m_Height(height), m_Width(width) {
    m_Data.resize(height);
    for (auto& row : m_Data) {
        row.resize(width);
    }
}

ImageASCII ImageRGB::to_ascii(size_t max_width, bool invert, const string& transition, const string& inverted) const {

    // One pixel is represented by two ASCII characters in width:
    max_width /= 2;

    size_t out_width, out_height;
    double i_step = 1, j_step = 0.5; // again, 2 characters for 1 pixel in width, hence the 0.5

    // If the width is smaller than the maximum width, we have to resize:
    if (max_width != 0 && m_Width > max_width) {
        double ratio = (max_width * 1.0) / (m_Width * 1.0);
        out_width = m_Width * ratio;
        out_height = m_Height * ratio;
        i_step = (m_Height * 1.0) / (out_height * 1.0);
        j_step = (m_Width * 1.0) / (out_width * 1.0) * 0.5; // again, 2 characters for 1 pixel in width, hence the 0.5
    }
    // No need to resize:
    else {
        out_width = m_Width;
        out_height = m_Height;
    }

    ImageASCII ascii(out_height, 2 * out_width);

    double height_pos = 0; // Height position in the original RGB image
    for (size_t i = 0; i < out_height; i++) {
        double width_pos = 0; // Width position in the original RGB image
        for (size_t j = 0; j < 2 * out_width; j++) {
            // Floored positions:
            size_t w = width_pos, h = height_pos;
            // Grey value:
            int g = m_Data[h][w].R/3 + m_Data[h][w].G/3 + m_Data[h][w].B/3;
            ascii.insert_to(i, j, get_char(g, invert, transition, inverted));
            width_pos += j_step;
        }
        height_pos += i_step;
    }
    return ascii;
}