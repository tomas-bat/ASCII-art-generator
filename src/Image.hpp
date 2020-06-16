/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include "ImageASCII.hpp"
#include "ImageRGB.hpp"

#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

/**
 * This abstract class represents an image of a supported file format.
 */
class Image {
public:
    /**
     * A virtual method which is used to clone the instance of an image when copying.
     *
     * @return std::unique_ptr, a pointer to the new instance
     */
    virtual std::unique_ptr<Image> clone() const = 0;

    /**
     * Virtual destructor is default for now.
     */
    virtual ~Image() = default;

    /**
     * A virtual method which will be able to convert an image of a specific format into an universal RGB image.
     *
     * @param[in] invert        Specifies whether a fully transparent pixel is set to a white pixel or a black pixel.
     *                          False is made for white backgrounds, true is made for black backgrounds. This only
     *                          works with file formats that support transparency.
     * @return                  The new image in universal RGB representation (empty if the conversion fails).
     */
    virtual ImageRGB extract(bool invert) const = 0;

    /**
     * A getter for the image filename.
     *
     * @return The image filename.
     */
    std::string get_name() const { return fs::path(m_Path).filename(); }

    /**
     * A getter for the image path.
     *
     * @return The image path.
     */
    std::string get_path() const { return m_Path; }
protected:
    /**
     * Full path to the image.
     */
    std::string m_Path;
};

