/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once

#include <string>
#include <iostream>


class Interface {
public:
    Interface(std::istream & in, std::ostream & out) : m_In(in), m_Out(out) {}
private:
    std::istream & m_In;
    std::ostream & m_Out;
};

