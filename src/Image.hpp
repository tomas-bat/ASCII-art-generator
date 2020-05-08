/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include <memory>
#include "ImageASCII.hpp"

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
     * A virtual method which will be able to convert an image of a specific format into an ASCII-art image.
     *
     * @param folder_location   Location of the folder, where the converted image will be saved.
     * @return                  The new image in ASCII-art (empty if the conversion fails).
     */
    virtual ImageASCII convert(const std::string& folder_location) = 0;

    // todo
private:
    // todo
};

