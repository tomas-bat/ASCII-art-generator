#include <climits>
/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */
#pragma once

#include <vector>
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
     * @param[in] interface     The interface that the controller works with.
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
    /**
     * A vector that stores paths to the loaded images.
     */
    std::vector<std::string> m_Images;

    /**
     * This number stores the framerate.
     */
    int m_Fps = 30;
};

