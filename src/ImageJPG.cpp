/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 *
 * @note    Some code inspired by libjpeg documentation.
 */

#include <cstdio>
#include <jpeglib.h>
#include <iostream>
#include "ImageJPG.hpp"

using namespace std;

/**
 * Custom JPEG error handler.
 * @note Inspired by https://stackoverflow.com/questions/19857766/error-handling-in-libjpeg
 */
void jpeg_error(j_common_ptr cinfo) {
    char jpeg_error_msg[JMSG_LENGTH_MAX];
    (*(cinfo->err->format_message))(cinfo, jpeg_error_msg);
    jpeg_destroy_decompress(reinterpret_cast<j_decompress_ptr>(&cinfo));
    throw runtime_error(jpeg_error_msg);
}

ImageRGB ImageJPG::extract(bool invert) const {

    (void)invert; // parameter is useless for JPEG, silencing warning

    // No need to check if the header contains "JFIF", already checked in ConverterController
    FILE* fp = fopen(m_Path.c_str(), "rb");

    // Check I/O errors:
    if (!fp)
        throw runtime_error("Unable to read image.");

    // Create library structs:
    jpeg_decompress_struct cinfo{};
    jpeg_error_mgr jerr{};

    cinfo.err = jpeg_std_error(&jerr);
    jerr.error_exit = jpeg_error;
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);
    jpeg_read_header(&cinfo, TRUE);

    // Get header info:
    JDIMENSION width = cinfo.image_width;
    JDIMENSION height = cinfo.image_height;
    int num_components = cinfo.num_components;

    // Start to decompress:
    jpeg_start_decompress(&cinfo);

    // Pixel data:
    auto data = new unsigned char[height * width * num_components];

    // Read pixels:
    while (cinfo.output_scanline < height) {
        unsigned char* ptr = data + cinfo.output_scanline * width * num_components;
        jpeg_read_scanlines(&cinfo, &ptr, 1);
    }

    ImageRGB rgb_image(height, width);

    // Read each pixel:
    for (JDIMENSION i = 0; i < height; i++) {
        size_t k = 0;
        for (JDIMENSION j = 0; j < num_components * width; j += num_components) {
            rgb_image.insert_to(i, k, data[i * width * num_components + j],
                                      data[i * width * num_components + j + 1],
                                      data[i * width * num_components + j + 2]);
            k++;
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);

    delete [] data;

    return rgb_image;
}
