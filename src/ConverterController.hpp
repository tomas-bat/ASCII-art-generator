/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#pragma once

#include "Controller.hpp"

class ConverterController : public Controller {
public:
    explicit ConverterController(const Interface& interface) : Controller(interface) {}
};

