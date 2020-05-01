/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once

#include "Interface.hpp"
#include "StartController.hpp"


class Application {
public:
    explicit Application(Interface interface) : m_Interface(interface) {}
    Application(const Application&) = delete;
    Application& operator= (const Application&) = delete;
    int run() { return StartController(m_Interface).run(); }
private:
    Interface m_Interface;
};

