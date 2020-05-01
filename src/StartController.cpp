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

Command help(map<string, Command>& commands) {
    return Command{
        "Displays this help.",
        [&commands] (const Interface& interface) {
            for (const auto& cmd : commands)
                interface.print_help(cmd.first, cmd.second.help());
            return 1;
        }
    };
}

Command go_to_converter(const Interface& interface) {
    return Command{
        "Opens the ASCII-art generator.",
        [&interface] (const Interface&) { return ConverterController(interface).run(); }
    };
}

StartController::StartController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("quit", quit_app());
    m_Commands.emplace("help", help(m_Commands));
    m_Commands.emplace("converter", go_to_converter(interface));
}
