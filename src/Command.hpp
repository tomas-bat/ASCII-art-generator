/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 *
 * @note Structure inspired by https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
 */
#pragma once

#include <string>
#include <utility>
#include <functional>
#include "Interface.hpp"

/**
 * Class to represent a command - a help how to use it and the function of the command itself.
 */
class Command {
public:
    /**
     * Implicit constructor to allow creating uninitialized commands.
     */
    Command() = default;

    /**
     * Constructor of command.
     * @param[in] help  A string that says what the command does.
     * @param func      The function of the command, with a return value of int and a parameter of Interface&.
     */
    Command(std::string help, std::function<int (Interface&)> func) : m_Help(std::move(help)), m_Function(std::move(func)) {}

    /**
     * A getter for the help string.
     *
     * @return  The help string.
     */
    const std::string& help() const { return m_Help; };

    /**
     * A method that executes the function of the command.
     *
     * @param[in] interface     The interface to execute the command into.
     * @return                  Return value of the function.
     */
    int execute(Interface& interface) const { return m_Function(interface); }

private:
    std::string m_Help;
    std::function<int (Interface&)> m_Function;
};

