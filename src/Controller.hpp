/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#pragma once

#include <map>
#include <utility>
#include <string>
#include "Command.hpp"
#include "Interface.hpp"

/**
 * Controller is a parent class used for all controllers, which manage navigation.
 * All controllers have certain commands, an interface they work with and a welcome message. They're all able
 * to display help for the commands they have.
 */
class Controller {
public:
    /**
     * A constructor of Controller emplaces all commands of the Controller into m_Commands.
     *
     * @param[in] interface     The interface we want to use with the Controller.
     */
    explicit Controller(const Interface& interface);

    /**
     * Copy constructor of Controller is deleted to forbid more than one instance.
     */
    Controller(const Controller&) = delete;

    /**
     * Operator= of Controller is deleted to forbid more than one instance.
     */
    Controller& operator= (const Controller&) = delete;

    /**
     * Method to control the whole run of the Controller. The method always shows help at the beginning of it's run
     * and then it keeps prompting for commands and executes them.
     *
     * @return  Return value of the whole run.
     */
    int run();

protected:
    /**
     * A map that stores all commands of the controller.
     */
    std::map<std::string, Command> m_Commands;

    /**
     * An interface associated with this controller. Usually given by the application.
     */
    Interface m_Interface;

    /**
     * Welcome message of the controller.
     */
    std::string m_Welcome = "[ You shouldn't be here. ]\n";
};

