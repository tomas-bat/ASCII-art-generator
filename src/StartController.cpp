/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include "Global.hpp"
#include "StartController.hpp"
#include "ConverterController.hpp"
#include "AnimatorController.hpp"
#include "EditorController.hpp"

using namespace std;

// Global variables from Global.hpp:
string glob_ASCII_transition;
string glob_ASCII_transition_inverted;
bool glob_inverted;


Command quit_app() {
    return Command{
        "Ends the program.",
        [] (const Interface&) { return 0; }
    };
}

Command go_to_converter(Interface& interface, const string& welcome, const Command& help) {
    return Command{
        "Opens the ASCII-art generator.",
        [&interface, &welcome, &help] (const Interface&) {
            if (ConverterController(interface).run() == -1)
                return 0;

            // After going back (and not at EOF), show welcome and help again:
            if (!interface.eof()) {
                interface.print(welcome);
                help.execute(interface);
            }
            return 1;
        }
    };
}

Command go_to_animator(Interface& interface, const string& welcome, const Command& help) {
    return Command{
        "Opens the ASCII-art image animator.",
        [&interface, &welcome, &help] (const Interface&) {
            if (AnimatorController(interface).run() == -1)
                return 0;


            // After going back (and not at EOF), show welcome and help again:
            if (!interface.eof()) {
                interface.print(welcome);
                help.execute(interface);
            }
            return 1;
        }
    };
}

Command go_to_editor(Interface& interface, const string& welcome, const Command& help) {
    return Command{
            "Opens the ASCII-art image editor.",
            [&interface, &welcome, &help] (const Interface&) {
                if (EditorController(interface).run() == -1)
                    return 0;

                // After going back (and not at EOF), show welcome and help again:
                if (!interface.eof()) {
                    interface.print(welcome);
                    help.execute(interface);
                }
                return 1;
            }
    };
}

StartController::StartController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("quit", quit_app());
    m_Commands.emplace("converter", go_to_converter(m_Interface, m_Welcome, m_Commands["help"]));
    m_Commands.emplace("animator", go_to_animator(m_Interface, m_Welcome, m_Commands["help"]));
    m_Commands.emplace("editor", go_to_editor(m_Interface, m_Welcome, m_Commands["help"]));

    // Default transitions:
    glob_ASCII_transition = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    glob_ASCII_transition_inverted = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    glob_inverted = false;

    m_Welcome = "[ You're in the main menu: ]\n";
}
