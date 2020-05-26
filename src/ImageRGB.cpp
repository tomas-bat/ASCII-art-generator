/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 24/05/2020
 */

#include <iostream>
#include "ImageRGB.hpp"

using namespace std;


ImageRGB::ImageRGB(size_t height, size_t width) : m_Height(height), m_Width(width) {
    m_Data.resize(height);
    for (auto& row : m_Data) {
        row.resize(width);
    }
}

ImageASCII ImageRGB::to_ascii() const {
    return ImageASCII();
}

void ImageRGB::test_print() const {
    for (const auto& row : m_Data) {
        for (const auto& pixel : row) {
            cout << "R(" << +pixel.R << ")G(" << +pixel.G << ")B(" << +pixel.B << ") ";
        }
        cout << endl;
    }
}
