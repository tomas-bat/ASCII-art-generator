/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#include "ConverterController.hpp"

using namespace std;

Command back() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back());

    m_Interface.print("[ You're in the converter: ]\n");
    m_Commands["help"].execute(m_Interface);
}
