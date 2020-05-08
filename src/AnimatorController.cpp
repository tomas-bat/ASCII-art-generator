/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include "AnimatorController.hpp"

using namespace std;

Command back_animator() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

// todo: commands

AnimatorController::AnimatorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_animator());

    m_Welcome = "[ You're in the animator: ]\n";
}
