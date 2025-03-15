#include <iostream>
#include "huffman.cpp"
#include "file_database.cpp"

using namespace std;

void printUsage() {
    cout << "Usage: \n";
    cout << "  Compress:   ./file_compressor compress <input_file> <output_file>\n";
    cout << "  Decompress: ./file_compressor decompress <input_file> <output_file>\n";
    cout << "  Store:      ./file_compressor store <input_file>\n";
    cout << "  Retrieve:   ./file_compressor retrieve <input_file> <output_file>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }

    string command = argv[1];

    if (command == "compress" && argc == 4) {
        compressFile(argv[2], argv[3]);
    } 
    else if (command == "decompress" && argc == 4) {
        decompressFile(argv[2], argv[3]);
    } 
    else if (command == "store" && argc == 3) {
        string compressedFilename = string(argv[2]) + ".huff";
        compressFile(argv[2], compressedFilename);
        storeCompressedFile(argv[2], compressedFilename);
    } 
    else if (command == "retrieve" && argc == 4) {
        vector<unsigned char> compressedData = retrieveCompressedFile(argv[2]);
        if (!compressedData.empty()) {
            writeFile(argv[3], compressedData);
            decompressFile(argv[3], argv[2]);
        }
    } 
    else {
        printUsage();
    }

    return 0;
}
