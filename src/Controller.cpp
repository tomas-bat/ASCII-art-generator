/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <string>
#include "Controller.hpp"

using namespace std;

int Controller::run() {
    // Show help at the begginging:
    m_Interface.print(m_Welcome);
    m_Commands["help"].execute(m_Interface);

    while (true) {
        // Get the command from the interface:
        string command = m_Interface.get_command();
        auto it = m_Commands.find(command);

        if (it == m_Commands.end())
            m_Interface.print("Unknown command. Use \"help\" for help.\n");
        else {
            int ret = it->second.execute(m_Interface);
            if (ret == 0)
                return 0;
        }
    }
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

Controller::Controller(const Interface& interface) : m_Interface(interface) {
    m_Commands.emplace("help", help(m_Commands));
}
