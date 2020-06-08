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
        // If EOF is reached at input, end the program:
        if (m_Interface.eof())
            return 0;

        // Get the command from the interface:
        string command = m_Interface.get_command();

        // If EOF is reached at input, end the program:
        if (m_Interface.eof())
            return 0;

        auto it = m_Commands.find(command);

        if (it == m_Commands.end())
            m_Interface.print("Unknown command. Use \"help\" for help.\n");
        else {
            // 0 is to end the current controller
            // -1 is to quit the app from any controller
            // 1 is for command success
            int ret = it->second.execute(m_Interface);
            if (ret == 0 || ret == -1)
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
