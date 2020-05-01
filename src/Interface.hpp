/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once

#include <string>
#include <iostream>


class Interface {
public:
    Interface() : m_In(std::cin), m_Out(std::cout) {}
    Interface(std::istream & in, std::ostream & out) : m_In(in), m_Out(out) {}
    std::string get_command();
    void print_help(const std::string& cmd_name, const std::string& cmd_help) const;
    void print(const std::string& str) const;
private:
    std::istream & m_In;
    std::ostream & m_Out;
};

