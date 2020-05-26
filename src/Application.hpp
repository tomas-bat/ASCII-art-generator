/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 *
 * @note Structure inspired by https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
 */
#pragma once

#include "Interface.hpp"
#include "StartController.hpp"

/**
 * Class to control the whole application.
 */
class Application {
public:
    /**
     * Constructor to initialize the member variable m_Interface.
     *
     * @param[in] interface     The input interface.
     */
    explicit Application(Interface interface) : m_Interface(interface) {}

    /**
     * Forbidding the copy constructor of Application, because we want only one instance.
     */
    Application(const Application&) = delete;

    /**
     * Forbidding the operator= of Application, because we want only one instance.
     */
    Application& operator= (const Application&) = delete;

    /**
     * This function starts the application and controls the whole run.
     *
     * @return  Return value of the whole run.
     */
    int run() { return StartController(m_Interface).run(); }

private:
    Interface m_Interface;
};

