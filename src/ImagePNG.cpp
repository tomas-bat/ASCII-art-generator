/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 *
 * @note Some methods nspired by libpng documentation http://www.libpng.org/pub/png/libpng-1.4.0-manual.pdf
 */

#include <png.h>
#include <iostream>
#include "ImagePNG.hpp"

using namespace std;

ImageRGB ImagePNG::extract() const {

    // No need to check whether the file has a correct PNG header, that was already checked in ConverterController
    FILE* fp = fopen(m_Path.c_str(), "rb");

    // Check I/O errors:
    if (!fp)
        throw runtime_error("Unable to read image.");

    cout << "hello" << endl;

    // Create library structs for PNG file reading:
    png_infop info_ptr, end_info;
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(fp);
        throw runtime_error("Unexpected error when reading a PNG file.");
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
        throw runtime_error("Unexpected error when reading a PNG file.");
    }

    // Setting up input code:
    png_init_io(png_ptr, fp);

    // Read the file:
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

    // Get image width and height:
    png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);

    // Array to access pixels:
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    ImageRGB rgb_image(height, width);

    for (png_uint_32 i = 0; i < height; i++) {
        for (png_uint_32 j = 0; j < 4*width; j += 4 ) {
            rgb_image.insert_to(i, j, row_pointers[i][j], row_pointers[i][j + 1], row_pointers[i][j + 2]);
        }
    }

    // Free used memory
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    // todo: free rows


    return rgb_image;
}
