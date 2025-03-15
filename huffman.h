#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>

void compressFile(const std::string& inputFile, const std::string& outputFile);
void decompressFile(const std::string& compressedFile, const std::string& outputFile);

#endif
