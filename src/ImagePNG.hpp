/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include "Image.hpp"

/**
 * This class represents a PNG image.
 */
class ImagePNG : public Image {
public:
    /**
     * Constructor of ImagePNG.
     *
     * @param path  Path of the image file.
     */
    explicit ImagePNG(const std::string& path) { m_Path = path; }

    /**
     * A method which is used to clone the instance of a PNG image when copying.
     *
     * @return std::unique_ptr, a pointer to the new instance
     */
    std::unique_ptr<Image> clone() const override { return std::make_unique<ImagePNG>(*this); }

    /**
     * This method converts a PNG image into an universal RGB image representation.
     *
     * @param invert    This parameter sets whether fully transparent pixels will be set to black or white.
     * @return The new RGB image.
     */
    ImageRGB extract(bool invert) const override;

    /**
     * Destructor is defaulted for now.
     */
    ~ImagePNG() override = default;

    // todo
private:
    // todo
};

