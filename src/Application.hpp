/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */
#pragma once


class Application {
public:
    Application() = default;
    int run();
private:
    Interface m_Interface;
};

