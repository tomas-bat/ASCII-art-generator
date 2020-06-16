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
     * @param[in] height    Image height.
     * @param[in] width     Image width.
     */
    ImageASCII(size_t height, size_t width);

    /**
     * Constructor of ImageASCII from a file.
     *
     * @param[in] file_path Path to the file.
     *
     * @throws std::runtime_error if unable to read file.
     */
    explicit ImageASCII(const std::string& file_path);

    /**
     * A method to set a character of the ASCII-art image.
     *
     * @param[in] height Position of the character.
     * @param[in] width  Position of the character.
     * @param[in] c      The character.
     *
     * @note Method doesn't check if the height and width are within range.
     */
    void insert_to(size_t height, size_t width, char c) noexcept
    { m_Data[height][width] = c; }

    /**
     * This operator returns the line at the given height.
     *
     * @param[in] height Row of the line.
     * @return The line string.
     * @note Method doesn't check if the height is within range.
     */
    std::string& operator[](size_t height) noexcept
    { return m_Data[height]; }

    /**
     * A getter for the image width.
     * @return The image width.
     */
    size_t get_width() const noexcept { return m_Width; };

    /**
     * A getter for the image height.
     * @return The image height.
     */
    size_t get_height() const noexcept { return m_Height; }

    /**
     * Returns the character at h, w.
     *
     * @param[in] h Row of the character.
     * @param[in] w Column of the character.
     * @return The character.
     * @note Method doesn't check if h, w is within range.
     */
    char& at(size_t h, size_t w) noexcept { return m_Data[h][w]; }

    /**
     * Method to save ASCII image to a file.
     *
     * @param[in] path  File path.
     *
     * @throws std::runtime_error if any error file file reading/writing occurs.
     */
    void save(const std::string& path);

private:
    /**
     * This vector stores lines of ASCII image characters.
     */
    std::vector<std::string> m_Data;

    /**
     * Height of the ASCII image in characters.
     */
    size_t m_Height;

    /**
     * Width of the ASCII image in characters.
     */
    size_t m_Width;
};

