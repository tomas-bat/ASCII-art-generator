/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#pragma once

#include <vector>
#include "Controller.hpp"
#include "Image.hpp"



/**
 * Class to represent a controller that controls the ASCII-art converter.
 */
class ConverterController : public Controller {
public:
    /**
     * Constructor of ConverterController emplaces all commands of the controller into m_Commands and sets
     * the welcome message.
     *
     * @param[in] interface    The interface that the controller works with.
     */
    explicit ConverterController(const Interface& interface);

    /**
    * Copy constructor is deleted to forbid more than one instance.
    */
    ConverterController(const ConverterController&) = delete;

    /**
    * Operator= is deleted to forbid more than one instance.
    */
    ConverterController& operator= (const ConverterController&) = delete;

private:
    /**
     * This vector stores loaded images.
     */
    std::vector<std::unique_ptr<Image>> m_Images;

    /**
     * This vector stores paths to images with valid extension.
     */
    std::vector<std::string> m_Valid_images;

    /**
     * This number represents the maximum width of the converted ASCII image.
     */
    size_t m_Max_width = 0;
};

