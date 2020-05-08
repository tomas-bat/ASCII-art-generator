/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include "EditorController.hpp"
#include "Command.hpp"

using namespace std;

Command back_editor() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

// todo: commands

EditorController::EditorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_editor());

    m_Welcome = "[ You're in the editor ]\n";
}
