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

Command location(string& filename) {
    return Command{
        "Specify the image location.",
        [&filename] (Interface& interface) {
            string path = interface.get_path("file");
            if (interface.eof() || path.empty())
                return 2;

            fstream file(path);
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
                interface.print("You have to specify a valid ASCII image location.")
                         .end_line();
                return 2;
            }

            system("clear");
            interface.read_file(filename);
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

Command brighten(const string& filename) {
    return Command{
        "Brightens the ASCII image.",
        [&filename] (Interface& interface) {
            ImageASCII ascii_image(filename);
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
            ascii_image.save(filename);
            return 1;
        }
    };
}

Command darken(const string& filename) {
    return Command{
            "Darkens the ASCII image.",
            [&filename] (Interface& interface) {
                ImageASCII ascii_image(filename);
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
                ascii_image.save(filename);
                return 1;
            }
    };
}

// todo: commands

EditorController::EditorController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_editor());
    m_Commands.emplace("location", location(m_File_location));
    m_Commands.emplace("show", show_img(m_File_location));
    m_Commands.emplace("brighten", brighten(m_File_location));
    m_Commands.emplace("darken", darken(m_File_location));

    m_Welcome = "[ You're in the editor: ]\n";
}
