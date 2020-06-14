/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <filesystem>
#include <fstream>
#include "Global.hpp"
#include "StartController.hpp"
#include "ConverterController.hpp"
#include "AnimatorController.hpp"
#include "EditorController.hpp"

#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

using namespace std;

// Global variables from Global.hpp:
string glob_ASCII_transition;
string glob_ASCII_transition_inverted;
bool glob_inverted;
bool glob_converted;
string glob_folder_location;


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

Command folder(string& folder_location) {
    return Command{
            "Specify the folder with images.",
            [&folder_location] (Interface& interface) {
                string path = interface.get_path("folder");
                if (interface.eof() || path.empty())
                    return 2;

                // Check if it's a valid directory:
                try {
                    fs::current_path(path);
                }
                catch (const fs::filesystem_error& except) {
                    interface.print(except.what())
                            .end_line();
                    return 2;
                }
                folder_location = path;
                glob_converted = false;
                return 1;
            }
    };
}

Command invert(bool& inverted){
    return Command{
            "Sets whether the ASCII image converts inverted or not.",
            [&inverted] (Interface& interface) {
                string input = interface.get_string();
                if (input == "true") {
                    inverted = true;
                    interface.print("Conversion set for a dark terminal.")
                            .end_line();
                }
                else if (input == "false") {
                    inverted = false;
                    interface.print("Conversion set for a white terminal.")
                            .end_line();
                }
                else {
                    interface.print(R"(Inverted must be "true" or "false".)")
                            .end_line();
                    return 2;
                }
                return 1;
            }
    };
}

Command custom(string& m_Transition, string& m_Transition_inverted) {
    return Command{
            "Loads a custom ASCII transitiom from a file.",
            [&m_Transition, &m_Transition_inverted] (Interface& interface) {
                string path = interface.get_path("file");
                ifstream file(path, ios::binary);
                if (!file) {
                    interface.print("Couldn't open such file.")
                            .end_line();
                    return 2;
                }
                string transition;
                getline(file, transition);
                if (transition.empty()) {
                    interface.print("No characters found.")
                            .end_line();
                    return 2;
                }
                m_Transition = transition;
                reverse(transition.begin(), transition.end());
                m_Transition_inverted = transition;
                interface.print("Custom characters loaded.")
                        .end_line();
                return 1;
            }
    };
}

StartController::StartController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("quit", quit_app());
    m_Commands.emplace("converter", go_to_converter(m_Interface, m_Welcome, m_Commands["help"]));
    m_Commands.emplace("animator", go_to_animator(m_Interface, m_Welcome, m_Commands["help"]));
    m_Commands.emplace("editor", go_to_editor(m_Interface, m_Welcome, m_Commands["help"]));
    m_Commands.emplace("folder", folder(glob_folder_location));
    m_Commands.emplace("invert", invert(glob_inverted));
    m_Commands.emplace("custom", custom(glob_ASCII_transition, glob_ASCII_transition_inverted));

    // Default transitions:
    glob_ASCII_transition = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    glob_ASCII_transition_inverted = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    glob_inverted = false;
    glob_converted = false;

    m_Welcome = "[ You're in the main menu: ]\n";
}
