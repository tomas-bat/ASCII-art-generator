/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once

#include <string>


class Command {
public:
    const std::string& help() const { return m_Help; };
private:
    std::string m_Help;
};

