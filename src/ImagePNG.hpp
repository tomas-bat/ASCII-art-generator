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
     * A method which is used to clone the instance of a PNG image when copying.
     *
     * @return std::unique_ptr, a pointer to the new instance
     */
    std::unique_ptr<Image> clone() const override { return std::make_unique<ImagePNG>(*this); }

    /**
     * This method converts a PNG image into an ASCII-art image.
     *
     * @return The new ASCII-art image.
     */
    ImageASCII convert() const override;

    /**
     * Destructor is defaulted for now.
     */
    ~ImagePNG() override = default;

    // todo
private:
    // todo
};

