/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once

#include <string>
#include <utility>
#include "Interface.hpp"

class Command {
public:
    Command() = default;
    Command(std::string help, std::function<int (const Interface&)> func) : m_Help(std::move(help)), m_Function(std::move(func)) {}
    const std::string& help() const { return m_Help; };
    bool execute(const Interface& interface) { return m_Function(interface); }
private:
    std::string m_Help;
    std::function<int (const Interface&)> m_Function;
};

