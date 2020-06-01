/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <filesystem>
#include <fstream>
#include <png.h>
#include <jpeglib.h>
#include "ConverterController.hpp"
#include "ImageJPG.hpp"
#include "ImagePNG.hpp"


#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

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
                            "will be saved in the folder you have entered before.\n"
                            "You can also set the maximum image width using command \"width <num>\","
                            "if not specified or if you enter 0, the converted image will keep\n"
                            "it's original dimensions.")
                     .end_line();
            return 1;
        }
    };
}

Command width(Interface& interface, size_t& max_width) {
    return Command{
        "Sets the maximum width of the converted image.",
        [&interface, &max_width] (const Interface&) {
            size_t input_num = interface.get_num();
            if (input_num == 0) {
                interface.print("Images will keep their original dimensions.")
                         .end_line();
            }
            max_width = input_num;
            return 1;
        }
    };
}

bool img_is_jpeg(const string& first_line) {
    return first_line.find("JFIF") != string::npos;
}

void load_images(vector<unique_ptr<Image>>& images, vector<string>& valid_images, Interface& interface) {
    int imgs_loaded = 0;
    for (const auto& img_path : valid_images) {
        bool is_png = true, is_jpeg = true;

        FILE* fp = fopen(img_path.c_str(), "rb");
        if (!fp)
            throw runtime_error("Unable to read image.");
        size_t bytes_to_check = 8;
        char header[8 * sizeof(char)];
        fread(header, sizeof(char), bytes_to_check, fp);
        fclose(fp);

        // Not a PNG, check if it's a JPEG:
        if (png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, bytes_to_check)) {
            is_png = false;

            ifstream img(img_path, ios::binary);
            if (!img)
                throw runtime_error("Unable to read image.");

            string first_line;
            getline(img, first_line);
            is_jpeg = img_is_jpeg(first_line);

            if (!is_jpeg) {
                interface.print(fs::path(img_path).filename())
                         .print(" is not a valid PNG or JPEG.")
                         .end_line();
                continue;
            }
            images.push_back(make_unique<ImageJPG>(img_path));
            imgs_loaded++;
        }
        // Image is a PNG:
        else {
            images.push_back(make_unique<ImagePNG>(img_path));
            imgs_loaded++;
        }
    }
    interface.print("Loaded ")
            .print(to_string(imgs_loaded))
            .print(" image(s) in total.")
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
            images.clear();

            // Find supported formats:
            for (const auto& file : fs::directory_iterator(path)) {
                string extension = file.path().extension();
                if (   extension == ".png"
                    || extension == ".PNG"
                    || extension == ".jpg"
                    || extension == ".JPG"
                    || extension == ".jpeg"
                    || extension == ".JPEG")
                {
                    interface.print("Found: ")
                             .print(file.path().filename())
                             .end_line();
                    valid_files.push_back(file.path());
                }
            }
            // Load images from folder to m_Images:
            load_images(images, valid_files, interface);
            return 1;
        }
    };
}

Command convert(Interface& interface, const string& folder_location, vector<string>& valid_images,
                vector<unique_ptr<Image>>& images, size_t& max_width) {
    return Command{
        "Converts all images from the given folder into ASCII-art.",
        [&interface, &folder_location, &valid_images, &images, &max_width] (const Interface&) {
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

            // Convert all images into their RGB representation, then convert to ASCII:
            for (const auto& image : images) {
                interface.print("Converting ")
                         .print(image->get_name())
                         .print("...")
                         .end_line();
                // Convert the image to a local RGB variable:
                ImageRGB rgb_image = image->extract();

                // Convert the RGB image to an ASCII image:
                ImageASCII ascii_image = rgb_image.to_ascii(max_width);

                // Create folder converted/:
                fs::create_directory(folder_location + "/converted");

                // Get the path where the new image will be saved to:
                string save_path = folder_location + "/converted/" + image->get_name() + ".txt";

                // Create the output file:
                ofstream out_file(save_path, ios::binary);
                if (!out_file)
                    throw runtime_error("File cannot be written.");

                // Save the ASCII-art image to the output file:
                for (size_t i = 0; i < ascii_image.get_height(); i++) {
                    for (size_t j = 0; j < ascii_image.get_width(); j++) {
                        if (!(out_file << ascii_image[i][j]))
                            throw runtime_error("Unexpected error when writing output.");
                    }
                    if (!(out_file << endl))
                        throw runtime_error("Unexpected error when writing output.");
                }

                interface.print("Converted to: ")
                         .print(save_path)
                         .end_line();
            }
            return 1;
        }
    };
}

// todo: commands

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_converter());
    m_Commands.emplace("howto", how_to(m_Interface));
    m_Commands.emplace("folder", folder(m_Interface, m_Folder_location, m_Valid_images, m_Images));
    m_Commands.emplace("convert", convert(m_Interface, m_Folder_location, m_Valid_images, m_Images, m_Max_width));
    m_Commands.emplace("width", width(m_Interface, m_Max_width));

    m_Welcome = "[ You're in the converter: ]\n";
}
