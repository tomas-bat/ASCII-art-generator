/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <filesystem>
#include <fstream>
#include <png.h>
#include <jpeglib.h>
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

void load_images(vector<unique_ptr<Image>>& images, vector<string>& valid_images, Interface& interface) {
    for (const auto& name : valid_images)
        interface.print(name)
                 .end_line();

}

Command folder(Interface& interface, string& folder_location, vector<string>& valid_files,
               vector<unique_ptr<Image>>& images) {
    return Command{
        "Specify the folder with images.",
        [&interface, &folder_location, &valid_files, &images] (const Interface&) {
            string path = interface.get_path();
            if (interface.eof())
                return -1;

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

            valid_files.clear();

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
                    valid_files.push_back(file.path());
                }
            }
            // Load images from folder to m_Images:
            load_images(images, valid_files, interface);

            interface.print("Found ")
                     .print(to_string(valid_files.size()))
                     .print(" file(s) in total.")
                     .end_line();
            return 1;
        }
    };
}

Command convert(Interface& interface, const string& folder_location, const vector<string>& valid_images,
                const vector<unique_ptr<Image>>& images) {
    return Command{
        "Converts all images from the given folder into ASCII-art.",
        [&interface, &folder_location, &valid_images, &images] (const Interface&) {
            if (folder_location.empty()) {
                interface.print("You have to specify the folder first.")
                         .end_line();
                return 2;
            }
            if (valid_images.empty()) {
                interface.print("No valid images have been found.")
                         .end_line();
                return 2;
            }

            // Load images from folder to m_Images:
            // todo

            // Convert all images to ASCII-art and save them:
            for (const auto& image : images) {
                // Convert the image to a local variable:
                ImageASCII ascii_image = image->convert();

                // Get the path where the new image will be saved to:
                string save_path = folder_location + "/converted/" + image->get_name() + ".txt";

                // Create the output file:
                ofstream out_file(save_path, ios::binary);
                if (!out_file)
                    throw runtime_error("File cannot be written.");

                // Save the ASCII-art image to the output file:
                for (size_t i = 0; i < ascii_image.get_height(); i++) {
                    if (!(out_file << ascii_image.get_row(i)))
                        throw runtime_error("Unexpected error when writing output.");
                }
            }

            // todo
            interface.print("--not implemeted--")
                     .end_line();
            return 1;
        }
    };
}

// todo: commands

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_converter());
    m_Commands.emplace("howto", how_to(m_Interface));
    m_Commands.emplace("folder", folder(m_Interface, m_Folder_location, m_Valid_images, m_Images));
    m_Commands.emplace("convert", convert(m_Interface, m_Folder_location, m_Valid_images, m_Images));

    m_Welcome = "[ You're in the converter: ]\n";
}
