/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#pragma once

#include <map>
#include "Command.hpp"
#include "Interface.hpp"

class Controller {
public:
    explicit Controller(const Interface& interface) : m_Interface(interface) {}
    int run();
protected:
    std::map<std::string, Command> m_Commands;
    Interface m_Interface;
};

