/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */

#include <filesystem>
#include <fstream>
#include <png.h>
#include <jpeglib.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>
#include "Global.hpp"
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
            [] (Interface&) { return 0; }
    };
}

Command how_to_converter() {
    return Command{
        "Shows help how to convert images.",
     [] (Interface& interface) {
            interface.print("First, you have to specify the folder in which the program will search for images "
                            "using command \"folder\", for example \"/home/users/john/imgs\".\n"
                            "Then, you have to tell the program to load all images from this folder using command "
                            "\"load\".\n"
                            "After that, enter the command \"convert\" and a folder with converted images "
                            "will be saved in the folder you have entered before.\n"
                            "You can also set the maximum image width using command \"width <num>\". "
                            "If not specified or if you enter 0, the converted image will keep\n"
                            "it's original dimensions. Command \"match\" will set the width to the width of your "
                            "terminal.\n"
                            "If you are displaying ASCII images in a dark terminal, it's recommended "
                            "to use \"invert true\", which will invert the ASCII conversion. You can then "
                            "set it back using \"invert false\".\n"
                            "If you want to load a custom ASCII transition from a file, use \"custom\" and then"
                            "enter the file location.")
                     .end_line();
            return 1;
        }
    };
}

Command width(size_t& max_width) {
    return Command{
        "Sets the maximum width of the converted image.",
        [&max_width] (Interface& interface) {
            size_t input_num;
            try {
                input_num = interface.get_num();
            }
            catch (const invalid_argument& except) {
                interface.print("Wrong input.")
                         .end_line()
                         .clear_line();
                return 2;
            }
            if (input_num == 0) {
                interface.print("Images will keep their original dimensions.")
                         .end_line();
                return 1;
            }
            max_width = input_num;
            interface.print("Maximum ASCII image width will now be ")
                     .print(to_string(max_width))
                     .print(" characters.")
                     .end_line();
            return 1;
        }
    };
}

Command match(size_t& max_width) {
    return Command{
        "Sets the maximum width to the width of user's terminal window.",
        [&max_width] (Interface& interface) {
            struct winsize w{};
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            max_width = w.ws_col;
            interface.print("Maximum ASCII image width will now be ")
                     .print(to_string(max_width))
                     .print(" characters.")
                     .end_line();
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

        FILE* fp = fopen(img_path.c_str(), "rb");
        if (!fp)
            throw runtime_error("Unable to read image.");
        size_t bytes_to_check = 8;
        char header[8 * sizeof(char)];
        fread(header, sizeof(char), bytes_to_check, fp);
        fclose(fp);

        // Not a PNG, check if it's a JPEG:
        if (png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, bytes_to_check)) {

            ifstream img(img_path, ios::binary);
            if (!img)
                throw runtime_error("Unable to read image.");

            string first_line;
            getline(img, first_line);

            if (!img_is_jpeg(first_line)) {
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

Command load(vector<unique_ptr<Image>>& images, vector<string>& valid_images, const string& path) {
    return Command{
        "Loads images from the given folder.",
        [&images, &valid_images, &path] (Interface& interface) {

            if (glob_folder_location.empty()) {
                interface.print("You have to specify a folder in the main menu.")
                         .end_line();
                return 2;
            }

            valid_images.clear();
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
                    valid_images.push_back(file.path());
                }
            }
            // Load images from folder to m_Images:
            load_images(images, valid_images, interface);
            return 1;
        }
    };
}

Command convert(const string& folder_location, vector<string>& valid_images,
                vector<unique_ptr<Image>>& images, const size_t& max_width, const bool& invert,
                const string& transition, const string& inverted) {
    return Command{
        "Converts all images from the given folder into ASCII-art.",
        [&folder_location, &valid_images, &images, &max_width, &invert,
         &transition, &inverted] (Interface& interface) {
            if (folder_location.empty()) {
                interface.print("No images have been loaded.")
                         .end_line();
                return 2;
            }
            if (valid_images.empty()) {
                interface.print("No valid images loaded.")
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
                ImageRGB rgb_image = image->extract(invert);

                // Convert the RGB image to an ASCII image:
                ImageASCII ascii_image = rgb_image.to_ascii(max_width, invert, transition, inverted);

                // Create folder converted/:
                fs::create_directory(folder_location + "/converted");

                // Get the path where the new image will be saved to:
                string save_path = folder_location + "/converted/" + image->get_name() + ".ascii";

                ascii_image.save(save_path);

                interface.print("Converted to: ")
                         .print(save_path)
                         .end_line();

                // Set the global variable showing that images have already been converted:
                glob_converted = true;
            }
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

Command reset(vector<unique_ptr<Image>>& images, vector<string>& valid_images,
              string& folder_location, string& transition, string& transition_inverted, size_t& max_width,
              bool& invert) {
    return Command{
        "Resets all settings to default.",
        [&images, &valid_images, &folder_location, &transition, &transition_inverted,
         &max_width, &invert] (Interface& interface) {
            images.clear();
            valid_images.clear();
            folder_location.clear();
            transition = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
            transition_inverted = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            max_width = 0;
            invert = false;
            interface.print("All settings changed to default.")
                     .end_line();
            return 1;
        }
    };
}

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_converter());
    m_Commands.emplace("howto", how_to_converter());
    m_Commands.emplace("load", load(m_Images, m_Valid_images, glob_folder_location));
    m_Commands.emplace("convert", convert(glob_folder_location, m_Valid_images, m_Images,
                                          m_Max_width, glob_inverted, glob_ASCII_transition, glob_ASCII_transition_inverted));
    m_Commands.emplace("width", width(m_Max_width));
    m_Commands.emplace("invert", invert(glob_inverted));
    m_Commands.emplace("custom", custom(glob_ASCII_transition, glob_ASCII_transition_inverted));
    m_Commands.emplace("reset", reset(m_Images, m_Valid_images, glob_folder_location, glob_ASCII_transition,
                                     glob_ASCII_transition_inverted, m_Max_width, glob_inverted));
    m_Commands.emplace("match", match(m_Max_width));

    m_Welcome = "[ You're in the converter: ]\n";
}
