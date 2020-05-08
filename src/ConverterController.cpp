/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <filesystem>
#include "ConverterController.hpp"
namespace fs = std::__fs::filesystem;

using namespace std;

Command back_converter() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

Command how_to(Interface& interface) {
    return Command{
        "Shows how to convert images.",
     [&interface] (const Interface&) {
            interface.print("First, you have to specify the folder in which the program will search for images "
                            "using command \"folder\", for example \"/home/users/john/imgs\".\n"
                            "After that, enter the command \"convert\" and a folder with converted images "
                            "will be saved in the folder you have entered before.\n");
            return 1;
        }
    };
}

Command folder(Interface& interface, string& folder_location, int& valid_files) {
    return Command{
        "Specify the folder with images.",
        [&interface, &folder_location, &valid_files] (const Interface&) {
            string path = interface.get_path();

            // Check if it's a valid directory:
            try {
                fs::current_path(path);
            }
            catch (const fs::filesystem_error& except) {
                interface.print("No such file or directory.\n");
                return 2;
            }
            folder_location = path;

            valid_files = 0;

            // Find supported formats:
            for (const auto& file : fs::directory_iterator(path)) {
                string extension = file.path().extension();
                if (   extension == ".png"
                    || extension == ".PNG"
                    || extension == ".jpg"
                    || extension == ".JPG" )
                {
                    interface.print("Found: ")
                             .print(file.path().filename())
                             .end_line();
                    valid_files++;
                }
            }
            interface.print("Found ")
                     .print(to_string(valid_files))
                     .print(" file(s) in total.")
                     .end_line();
            return 1;
        }
    };
}

// todo: commands

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_converter());
    m_Commands.emplace("howto", how_to(m_Interface));
    m_Commands.emplace("folder", folder(m_Interface, m_Folder_location, m_Valid_images));

    m_Welcome = "[ You're in the converter: ]\n";
}
