/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include "Controller.hpp"

/**
 * Class to represent a controller that controls the ASCII-art editor.
 */
class EditorController : public Controller {
public:
    /**
     * Constructor of EditorController emplaces all commands of the controller into m_Commands and sets
     * the welcome message.
     *
     * @param[in] interface     The interface that the controller works with.
     */
    explicit EditorController(const Interface& interface);

    /**
    * Copy constructor is deleted to forbid more than one instance.
    */
    EditorController(const EditorController&) = delete;

    /**
    * Operator= is deleted to forbid more than one instance.
    */
    EditorController& operator= (const EditorController&) = delete;

private:
    /**
     * Full path to the ASCII image.
     */
    std::string m_File_location;
};

