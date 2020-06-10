/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 08/05/2020
 */

#include <fstream>
#include <iostream>
#include "ImageASCII.hpp"

using namespace std;

ImageASCII::ImageASCII(size_t height, size_t width) : m_Height(height), m_Width(width) {
    m_Data.resize(m_Height);
    for (auto& row : m_Data)
        row.resize(m_Width);
}

ImageASCII::ImageASCII(const string& file_path) {
    ifstream file(file_path);
    if (!file)
        throw runtime_error("Unable to read ASCII image file in ASCII image construction: \'" + file_path + "\'");

    string line;
    size_t height = 0;
    bool first = true;
    while (!file.eof()) {
        getline(file, line);
        m_Data.push_back(line);
        height++;
        if (first) {
            m_Width = line.size();
            first = false;
        }
    }
    m_Height = height - 1;
    file.close();
}

void ImageASCII::save(const string& path) {
    // Create the output file:
    ofstream out_file(path, ios::binary);
    if (!out_file)
        throw runtime_error("ASCII file cannot be written.");

    // Save the ASCII-art image to the output file:
    for (size_t i = 0; i < m_Height; i++) {
        if (!(out_file << m_Data[i]))
            throw runtime_error("Unexpected error when writing output.");
        if (!(out_file << endl))
            throw runtime_error("Unexpected error when writing output.");
    }
    out_file.close();
}
