/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include <fstream>
#include <filesystem>
#include "EditorController.hpp"
#include "Command.hpp"
#include "Global.hpp"
#include "ImageASCII.hpp"

#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

using namespace std;

Command back_editor() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

Command images() {
    return Command{
        "Shows the images you can load.",
        [] (Interface& interface) {
            if (!glob_converted) {
                interface.print("You haven't converted any images.")
                         .end_line();
                return 2;
            }
            interface.print("You can load any of the following images:")
                     .end_line();
            try {
                for (const auto& file : fs::directory_iterator(glob_folder_location + "/converted/")) {
                    interface.print(file.path().filename())
                            .end_line();
                }
            }
            catch (const fs::filesystem_error& except) {
                interface.print("Error: No such folder \"converted\" in the given folder. ")
                         .print("Did you change the folder after converting?")
                         .end_line();
                return 2;
            }
            return 1;
        }
    };
}

Command load(string& filename) {
    return Command{
        "Loads the specified image.",
        [&filename] (Interface& interface) {
            string path = interface.get_string();
            if (interface.eof() || path.empty())
                return 2;

            if (!glob_converted) {
                interface.print("You have to convert the images before you can edit them.")
                         .end_line();
                return 2;
            }

            fstream file(glob_folder_location + "/converted/" + path);
            if (!file) {
                interface.print("Unable to open such file.")
                         .end_line();
                return 2;
            }
            if (fs::path(path).filename().extension() != ".ascii") {
                interface.print("Not a valid ASCII image file.")
                         .end_line();
                return 2;
            }
            filename = path;
            file.close();
            interface.print("Loaded ")
                     .print(fs::path(path).filename())
                     .end_line();
            return 1;
        }
    };
}

Command show_img(const string& filename) {
    return Command{
        "Shows the loaded ASCII image.",
        [&filename] (Interface& interface) {

            if (filename.empty()) {
                interface.print("No image loaded.")
                         .end_line();
                return 2;
            }

            system("clear");
            try {
                interface.read_file(glob_folder_location + "/converted/" + filename);
            }
            catch (const runtime_error& except) {
                interface.print(except.what())
                         .end_line();
                return 2;
            }
            return 1;
        }
    };
}

char brighten_darken(char c, const string& char_set, size_t pos, bool brighten) {
    if (brighten && pos == char_set.size() - 1)
        return c;
    if (!brighten && pos == 0)
        return c;
    if (brighten)
        return char_set[pos + 1];
    return char_set[pos - 1];
}

char negative_char(const string& char_set, size_t pos) {
    return char_set[char_set.size() - 1 - pos];
}

Command brighten(const string& filename) {
    return Command{
        "Brightens the ASCII image.",
        [&filename] (Interface& interface) {
            if (filename.empty()) {
                interface.print("No image loaded.")
                         .end_line();
                return 2;
            }
            ImageASCII ascii_image(glob_folder_location + "/converted/" + filename);
            for (size_t i = 0; i < ascii_image.get_height(); i++) {
                for (size_t j = 0; j < ascii_image.get_width(); j++) {
                    char c = ascii_image.at(i, j);
                    string& char_set = (glob_inverted ? glob_ASCII_transition_inverted : glob_ASCII_transition);
                    size_t pos = char_set.find(c);
                    if (pos == string::npos) {
                        interface.print("Error when brightening image. Are you sure you have set the correct "
                                        "character set in the converter?")
                                 .end_line();
                        return 2;
                    }
                    ascii_image.at(i, j) = brighten_darken(c, char_set, pos, true);
                }
            }
            ascii_image.save(glob_folder_location + "/converted/" + filename);
            return 1;
        }
    };
}

Command darken(const string& filename) {
    return Command{
            "Darkens the ASCII image.",
            [&filename] (Interface& interface) {
                if (filename.empty()) {
                    interface.print("No image loaded.")
                            .end_line();
                    return 2;
                }
                ImageASCII ascii_image(glob_folder_location + "/converted/" + filename);
                for (size_t i = 0; i < ascii_image.get_height(); i++) {
                    for (size_t j = 0; j < ascii_image.get_width(); j++) {
                        char c = ascii_image.at(i, j);
                        string& char_set = (glob_inverted ? glob_ASCII_transition_inverted : glob_ASCII_transition);
                        size_t pos = char_set.find(c);
                        if (pos == string::npos) {
                            interface.print("Error when darkening image. Are you sure you have set the correct "
                                            "character set in the converter?")
                                    .end_line();
                            return 2;
                        }
                        ascii_image.at(i, j) = brighten_darken(c, char_set, pos, false);
                    }
                }
                ascii_image.save(glob_folder_location + "/converted/" + filename);
                return 1;
            }
    };
}

Command negative(const string& filename) {
    return Command{
        "Creates a negative of the ASCII image.",
        [&filename] (Interface& interface) {
            if (filename.empty()) {
                interface.print("No image loaded.")
                        .end_line();
                return 2;
            }
            ImageASCII ascii_image(glob_folder_location + "/converted/" + filename);
            for (size_t i = 0; i < ascii_image.get_height(); i++) {
                for (size_t j = 0; j < ascii_image.get_width(); j++) {
                    char c = ascii_image.at(i, j);
                    string& char_set = (glob_inverted ? glob_ASCII_transition_inverted : glob_ASCII_transition);
                    size_t pos = char_set.find(c);
                    if (pos == string::npos) {
                        interface.print("Error when darkening image. Are you sure you have set the correct "
                                        "character set in the converter?")
                                .end_line();
                        return 2;
                    }
                    ascii_image.at(i, j) = negative_char(char_set, pos);
                }
            }
            ascii_image.save(glob_folder_location + "/converted/" + filename);

            return 1;
        }
    };
}

// todo: commands

EditorController::EditorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_editor());
    m_Commands.emplace("load", load(m_File_location));
    m_Commands.emplace("show", show_img(m_File_location));
    m_Commands.emplace("brighten", brighten(m_File_location));
    m_Commands.emplace("darken", darken(m_File_location));
    m_Commands.emplace("images", images());
    m_Commands.emplace("negative", negative(m_File_location));

    m_Welcome = "[ You're in the editor: ]\n";
}
