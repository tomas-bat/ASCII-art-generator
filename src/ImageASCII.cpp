/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include "ImageASCII.hpp"

using namespace std;

ImageASCII::ImageASCII(size_t height, size_t width) : m_Height(height), m_Width(width) {
    m_Data.resize(m_Height);
    for (auto& row : m_Data)
        row.resize(2 * m_Width);
}
