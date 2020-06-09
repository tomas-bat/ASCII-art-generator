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
     * @note One RGB pixel is represented as two ASCII characters.
     *
     * @param height    Image height.
     * @param width     Image width.
     */
    ImageASCII(size_t height, size_t width);

    /**
     * Constructor of ImageASCII from a file.
     *
     * @param file_path Path to the file.
     */
    explicit ImageASCII(const std::string& file_path);

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

    char& at(size_t h, size_t w) { return m_Data[h][w]; }

    /**
     * Method to save ASCII image to a file.
     *
     * @param path  File path.
     */
    void save(const std::string& path);

private:
    std::vector<std::string> m_Data;
    size_t m_Height;
    size_t m_Width;
};

