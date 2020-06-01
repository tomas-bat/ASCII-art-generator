/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 24/05/2020
 */

#include <iostream>
#include <string>
#include "ImageRGB.hpp"

using namespace std;

char get_char(int gray_value) {
    string chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    double chars_len = chars.size();
    double interval = chars_len/256;

    return chars[gray_value * interval];
}

ImageRGB::ImageRGB(size_t height, size_t width) : m_Height(height), m_Width(width) {
    m_Data.resize(height);
    for (auto& row : m_Data) {
        row.resize(width);
    }
}

ImageASCII ImageRGB::to_ascii(size_t max_width) const {

    size_t out_width, out_height;
    double i_step = 1, j_step = 1;

    if (max_width != 0 && m_Width > max_width) {
        double ratio = (max_width * 1.0) / (m_Width * 1.0);
        out_width = m_Width * ratio;
        out_height = m_Height * ratio;
        i_step = (m_Height * 1.0) / (out_height * 1.0);
        j_step = (m_Width * 1.0) / (out_width * 1.0);
    }
    else {
        out_width = m_Width;
        out_height = m_Height;
    }

    ImageASCII ascii(out_height, out_width);

    double height_pos = 0;
    for (size_t i = 0; i < out_height; i++) {
        double width_pos = 0;
        for (size_t j = 0; j < out_width; j++) {
            // Grey value:
            size_t w = width_pos, h = height_pos;
            int g = m_Data[h][w].R/3 + m_Data[h][w].G/3 + m_Data[h][w].B/3;
            ascii.insert_to(i, j, get_char(g));
            width_pos += j_step;
        }
        height_pos += i_step;
    }
    return ascii;
}

void ImageRGB::test_print() const {
    for (const auto& row : m_Data) {
        for (const auto& pixel : row) {
            cout << "R(" << +pixel.R << ")G(" << +pixel.G << ")B(" << +pixel.B << ") ";
        }
        cout << endl;
    }
}
