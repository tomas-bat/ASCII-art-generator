/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include <filesystem>
#include <chrono>
#include <thread>
#include <cmath>
#include "AnimatorController.hpp"
#include "Global.hpp"

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
            interface.print("First, you have to load the images created by the converter using command \"load\".\n"
                            "It is strongly recommended to convert these images with the width and color "
                            "matching your terminal (see converter help).\n"
                            "To show the animation, use \"show\".\n"
                            "You can view the frame position in the animation using command \"positions\".\n"
                            "You can also change the frame position using command \"swap <num> <num>\", which "
                            "will swap the two given frames.")
                     .end_line();
            return 1;
        }
    };
}

Command load(vector<string>& images) {
    return Command{
        "Loads images from converted folder.",
        [&images] (Interface& interface) {

            if (!glob_converted) {
                interface.print("You have to convert images before you can show an animation.")
                        .end_line();
                return 2;
            }
            // Check if it's a valid directory:
            try {
                fs::current_path(glob_folder_location + "/converted");
            }
            catch (const fs::filesystem_error& except) {
                interface.print(except.what())
                        .end_line();
                return 2;
            }
            images.clear();

            for (const auto& file : fs::directory_iterator(glob_folder_location + "/converted")) {
                if (file.path().extension() == ".ascii") {
                    interface.print("Found ")
                             .print(file.path().filename())
                             .end_line();
                    images.emplace_back(file.path());
                }
            }

            sort(images.begin(), images.end());

            if (images.empty()) {
                interface.print("No valid images have been found.")
                         .end_line();
            }


            return 1;
        }
    };
}

Command positions(vector<string>& images) {
    return Command{
        "Shows current positions of images in the animation.",
        [&images] (Interface& interface) {

            if (images.empty()) {
                interface.print("You have to specify the folder with valid images.")
                        .end_line();
                return 2;
            }

            int k = 0;
            for (const auto& image : images) {
                interface.print(to_string(++k))
                         .print(": ")
                         .print(fs::path(image).filename())
                         .end_line();
            }

            return 1;
        }
    };
}

Command swap(vector<string>& images) {
    return Command{
        "Swaps images in the animation.",
        [&images] (Interface& interface) {

            int num_1, num_2;
            try {
                num_1 = interface.get_int();
                num_2 = interface.get_int();
            }
            catch (const invalid_argument& except) {
                interface.print("Wrong input.")
                         .end_line()
                         .clear_line();
                return 2;
            }

            if (images.empty()) {
                interface.print("You have to specify the folder with valid images.")
                         .end_line();
                return 2;
            }

            if (   num_1 < 1 || num_1 > (int)images.size()
                || num_2 < 1 || num_2 > (int)images.size())
            {
                interface.print("Positions must be 1 - ")
                         .print(to_string(images.size()))
                         .end_line();
                return 2;

            }

            string& img1 = images[num_1 - 1];
            string& img2 = images[num_2 - 1];
            swap(img1, img2);

            return 1;
        }
    };
}

Command show(vector<string>& images, const int& fps) {
    return Command{
        "Show the animation.",
        [&images, &fps] (Interface& interface) {

            if (images.empty()) {
                interface.print("No images loaded.")
                         .end_line();
                return 2;
            }

            int milisec = floor(1.0/(fps * 1.0) * 1000);

            for (const auto& image : images) {
                system("clear");
                interface.read_file(image);
                this_thread::sleep_for(chrono::milliseconds(milisec));
            }

            return 1;
        }
    };
}

Command fps(int& fps) {
    return Command{
        "Sets the framerate of the animation.",
        [&fps] (Interface& interface) {

            int num;
            try {
                num = interface.get_int();
            }
            catch (const invalid_argument& except) {
                interface.print("Wrong input.")
                         .end_line();
                return 2;
            }
            if (num < 1) {
                interface.print("FPS must be 1 or more.")
                         .end_line();
                return 2;
            }
            fps = num;

            return 1;
        }
    };
}

AnimatorController::AnimatorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_animator());
    m_Commands.emplace("load", load(m_Images));
    m_Commands.emplace("show", show(m_Images, m_Fps));
    m_Commands.emplace("howto", how_to_animator());
    m_Commands.emplace("positions", positions(m_Images));
    m_Commands.emplace("swap", swap(m_Images));
    m_Commands.emplace("fps", fps(m_Fps));

    m_Welcome = "[ You're in the animator: ]\n";
}
