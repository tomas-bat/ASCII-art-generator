/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include <filesystem>
#include <chrono>
#include <thread>
#include "AnimatorController.hpp"

#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

using namespace std;

Command back_animator() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

Command how_to_animator() {
    return Command{
        "Show help how to show animation.",
        [] (Interface& interface) {
            interface.print("First, you have to specify the folder in which the program will look for "
                            "valid ASCII images using command \"folder\".\n"
                            "It is strongly recommended to get those images using this program's converter, "
                            "with the width and color matching your terminal (see converter help).\n"
                            "To show the animation, use \"show\".")
                     .end_line();
            return 1;
        }
    };
}

Command folder(vector<string>& images) {
    return Command{
        "Specify the folder with images.",
        [&images] (Interface& interface) {

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
            images.clear();

            for (const auto& file : fs::directory_iterator(path)) {
                if (file.path().extension() == ".txt") {
                    interface.print("Found ")
                             .print(file.path().filename())
                             .end_line();
                    images.push_back(file.path());
                }
            }

            if (images.empty()) {
                interface.print("No valid images have been found.")
                         .end_line();
            }


            return 1;
        }
    };
}

Command show(const vector<string>& images) {
    return Command{
        "Show the animation.",
        [&images] (Interface& interface) {

            if (images.empty()) {
                interface.print("You have to specify the folder with valid images.")
                         .end_line();
                return 2;
            }

            for (const auto& image : images) {
                system("clear");
                interface.read_file(image);
                this_thread::sleep_for(chrono::seconds(1));
            }

            return 1;
        }
    };
}

AnimatorController::AnimatorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_animator());
    m_Commands.emplace("folder", folder(m_Images));
    m_Commands.emplace("show", show(m_Images));
    m_Commands.emplace("howto", how_to_animator());

    m_Welcome = "[ You're in the animator: ]\n";
}
