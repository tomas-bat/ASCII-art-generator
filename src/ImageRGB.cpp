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

ImageASCII ImageRGB::to_ascii() const {

    ImageASCII ascii(m_Height, m_Width);

    for (size_t i = 0; i < m_Height; i++) {
        for (size_t j = 0; j < m_Width; j++) {
            // Grey value:
            int h = m_Data[i][j].R/3 + m_Data[i][j].G/3 + m_Data[i][j].B/3;
            ascii.insert_to(i, j, get_char(h));
        }
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
