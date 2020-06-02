/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include <cstdio>
#include <jpeglib.h>
#include <iostream>
#include "ImageJPG.hpp"

using namespace std;

ImageRGB ImageJPG::extract() const {

    // No need to check if the header contains "JFIF", already checked in ConverterController
    FILE* fp = fopen(m_Path.c_str(), "rb");

    // Check I/O errors:
    if (!fp)
        throw runtime_error("Unable to read image.");

    // Create library structs:
    jpeg_decompress_struct cinfo{};
    jpeg_error_mgr jerr{};

    cinfo.err = jpeg_std_error(&jerr);
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
