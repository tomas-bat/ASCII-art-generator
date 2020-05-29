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
     * Constructor of ImageASCII sets the image width and height.
     *
     * @param height    Image height.
     * @param width     Image width.
     */
    ImageASCII(size_t height, size_t width);

    /**
     * A method to set a character of the ASCII-art image.
     *
     * @param height Position of the character.
     * @param width  Position of the character.
     * @param c      The character.
     */
    void insert_to(size_t height, size_t width, char c)
    { m_Data[height][width] = c; }

    std::string& operator[](size_t height)
    { return m_Data[height]; }

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
    size_t m_Height;
    size_t m_Width;
    // todo
};

