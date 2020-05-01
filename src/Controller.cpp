/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <string>
#include "Controller.hpp"

using namespace std;

int Controller::run() {
    while (true) {
        string command = m_Interface.get_command();
        auto it = m_Commands.find(command);
        if (it == m_Commands.end())
            m_Interface.print("Unknown command. Use \"help\" for help.");
        else {
            int ret = it->second.execute(m_Interface);
            if (ret == 0)
                return 0;
        }
    }
}
