/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include <vector>
#include <string>

/**
 * This class represents an image in ASCII-art
 */
class ImageASCII {
public:
    /**
     * This method returns a specified row of the ASCII-art image.
     *
     * @param row_idx   The row index we want to get.
     * @return          The row we want to get.
     */
    const std::string& get_row(size_t row_idx) const { return m_Data.at(row_idx); }

    /**
     * A getter for the image width.
     * @return The image width.
     */
    size_t get_width() const { return m_Width; };

    /**
     * A getter for the image height.
     * @return The image height.
     */
    size_t get_height() const { return m_Height; }

    // todo
private:
    std::vector<std::string> m_Data;
    size_t m_Width;
    size_t m_Height;
    // todo
};

