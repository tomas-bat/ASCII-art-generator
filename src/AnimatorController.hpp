#include <climits>
/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include "Controller.hpp"


/**
 * Class to represent a controller that controls the ASCII-art animator.
 */
class AnimatorController : public Controller {
public:
    /**
     * Constructor of AnimatorController emplaces all commands of the controller into m_Commands and sets
     * the welcome message.
     *
     * @param interface[in]     The interface that the controller works with.
     */
    explicit AnimatorController(const Interface& interface);

    /**
    * Copy constructor is deleted to forbid more than one instance.
    */
    AnimatorController(const AnimatorController&) = delete;

    /**
    * Operator= is deleted to forbid more than one instance.
    */
    AnimatorController& operator= (const AnimatorController&) = delete;

private:
    __unused std::string m_Folder_location; // using __unused to silence warnings, variable will be used later
    __unused int m_Valid_images = 0; // using __unused to silence warnings, variable will be used later
};

