/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include "Image.hpp"
#include <string>
#include <utility>

/**
 * This class represents a JPG image.
 */
class ImageJPG : public Image {
public:
    /**
     * Constructor of ImageJPG.
     *
     * @param path  Path of the file.
     */
    explicit ImageJPG(const std::string& path) { m_Path = path; }

    /**
     * A method which is used to clone the instance of a JPG image when copying.
     *
     * @return std::unique_ptr, a pointer to the new instance
     */
    std::unique_ptr<Image> clone() const override { return std::make_unique<ImageJPG>(*this); }

    /**
     * This method converts a JPG image into an universal RGB representation.
     *
     * @param invert    This parameter is useless for JPEG, because JPEG doesn't support transparency.
     * @return The new RGB image.
     */
    ImageRGB extract(bool invert) const override;

    /**
     * Destructor is defaulted for now.
     */
    ~ImageJPG() override = default;

    // todo
private:
    // todo
};

