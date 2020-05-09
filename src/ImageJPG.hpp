/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include "Image.hpp"

/**
 * This class represents a JPG image.
 */
class ImageJPG : public Image {
public:
    /**
     * A method which is used to clone the instance of a JPG image when copying.
     *
     * @return std::unique_ptr, a pointer to the new instance
     */
    std::unique_ptr<Image> clone() const override { return std::make_unique<ImageJPG>(*this); }

    /**
     * This method converts a JPG image into an ASCII-art image.
     *
     * @return The new ASCII-art image.
     */
    ImageASCII convert() const override;

    /**
     * Destructor is defaulted for now.
     */
    ~ImageJPG() override = default;

    // todo
private:
    // todo
};

