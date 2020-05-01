/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <map>
#include "StartController.hpp"
#include "ConverterController.hpp"

using namespace std;

Command quit_app() {
    return Command{
        "Ends the program.",
        [] (const Interface&) { return 0; }
    };
}

Command go_to_converter(const Interface& interface) {
    return Command{
        "Opens the ASCII-art generator.",
        [&interface] (const Interface&) {
            ConverterController(interface).run();
            return 1;
        }
    };
}

StartController::StartController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("quit", quit_app());
    m_Commands.emplace("converter", go_to_converter(interface));

    m_Interface.print("[ You're in the main menu. ]\n");
    m_Commands["help"].execute(m_Interface);
}
