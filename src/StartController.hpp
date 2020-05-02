/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#pragma once

#include "Controller.hpp"

/**
 * Class to represent a controller that the application starts with.
 */
class StartController : public Controller {
public:
    /**
     * Constructor of StartController emplaces all commands of the controller into m_Commands and sets
     * the welcome message.
     *
     * @param interface[in]     The interface that the controller works with.
     */
    explicit StartController(const Interface& interface);

    /**
     * Copy constructor is deleted to forbid more than one instance.
     */
    StartController(const StartController&) = delete;

    /**
     * Operator= is deleted to forbid more than one instance.
     */
    StartController& operator= (const StartController&) = delete;
};

