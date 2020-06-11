/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 *
 * @note    Some code inspired by libpng documentation.
 */

#include <png.h>
#include <iostream>
#include "ImagePNG.hpp"

using namespace std;

// Creating global info pointers, so that they can be freed in error functions, which is necessary,
// because png error/warning functions only pass png_ptr
png_infop info_ptr, end_info;

void user_error_fn(png_structp png_ptr, png_const_charp error_msg) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    throw runtime_error(error_msg);
}

void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    throw runtime_error(warning_msg);
}

ImageRGB ImagePNG::extract(bool invert) const {

    // No need to check whether the file has a correct PNG header, that was already checked in ConverterController
    FILE* fp = fopen(m_Path.c_str(), "rb");

    // Check I/O errors:
    if (!fp)
        throw runtime_error("Unable to read PNG image:" + m_Path);

    // Create library structs for PNG file reading:
    // png_infop info_ptr, end_info;
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, user_error_fn, user_warning_fn);
    if (!png_ptr) {
        fclose(fp);
        throw runtime_error("Unexpected error when reading a PNG file: " + m_Path);
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)nullptr, (png_infopp)nullptr);
        fclose(fp);
        throw runtime_error("Unexpected error when reading a PNG file.");
    }
    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)nullptr);
        fclose(fp);
        throw runtime_error("Unexpected error when reading a PNG file: " + m_Path);
    }

    // Setting up input code:
    png_init_io(png_ptr, fp);

    // Read the file:
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

    // Get image width and height:
    png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);

    // Get the number of channels:
    int channels_cnt = (int)png_get_channels(png_ptr, info_ptr);

    // Array to access pixels:
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    ImageRGB rgb_image(height, width);

    bool alpha = (channels_cnt == 4);
    // Read each pixel (3 or 4 channels):
    for (png_uint_32 i = 0; i < height; i++) {
        int k = 0;
        for (png_uint_32 j = 0; j < channels_cnt * width; j += channels_cnt) {
            // If the image has an alpha channel and it's fully transparent, set pixel as white/black:
            if (alpha && row_pointers[i][j + 3] == 0) {
                if (invert)
                    rgb_image.insert_to(i, k, 0, 0, 0);
                else
                    rgb_image.insert_to(i, k, 255, 255, 255);
            }
            else
                rgb_image.insert_to(i, k, row_pointers[i][j], row_pointers[i][j + 1], row_pointers[i][j + 2]);
            k++;
        }
    }

    // Free used memory
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    return rgb_image;
}
