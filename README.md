# File_compressor
A simple Huffman Encoding file compressor that supports database storage using SQLite.
This CLI tool allows you to compress, decompress, store, and retrieve files efficiently.

🚀 Features

✔ Huffman Compression - Lossless text compression using Huffman encoding.
✔ SQLite Database Storage - Store and retrieve compressed files from a database.
✔ Command-Line Interface (CLI) - Simple and easy-to-use commands.
✔ Fast & Efficient - Reads and writes files in binary mode for optimal performance.

Installation:
### **Linux (Ubuntu/Debian)**
1) Install dependencies:  
   ```sh
   sudo apt update && sudo apt install g++ cmake make sqlite3 libsqlite3-dev
2) Clone the repository.
   git clone https://github.com/Aughh2/file_compressor.git
   cd file_compressor
3) Compile the program.
   g++ main.cpp -o file_compressor -lsqlite3
4) Initialize the database.
   ./file_compressor init
   
### **Running on Windows**
Option 1: Enable WSL (if not installed).
          Open Powershell as an administrator and run "wsl --install".
          Run Ubuntu/Debian in WSL and follow the installation steps above.
Option 2: Virtual Machine (VM).
          Install VirtualBox or VMware.
          Set up an Ubuntu/Debian virtual machine.
          Follow the Linux installation steps inside the VM.
Option 3: Cygwin (Linux-like Terminal for Windows).
          Download and install Cygwin from https://cygwin.com/install.html.
          Install necessary packages (g++, make, sqlite3).
          Follow the Linux installation steps inside Cygwin.
          
Usage:
1) Compress a file.
   ./file_compressor compress input.txt compressed.huff
   Compresses input.txt into compressed.huff.
2) Decompress a file.
   ./file_compressor decompress compressed.huff output.txt
   Decompresses compressed.huff into output.txt.
3) Store compressed file in a database.
   ./file_compressor store input.txt
   Compresses input.txt and stores it in the database.
4) Retreive and decompress from a database.
   ./file_compressor retrieve input.txt output.txt


💡 How It Works

    Compression:
        Reads file contents and calculates character frequencies.
        Builds a Huffman Tree and generates binary codes.
        Saves compressed binary data to a file.

    Decompression:
        Reads the compressed file and reconstructs the Huffman Tree.
        Decodes the binary data back into the original file.

    Database Storage:
        Stores compressed binary data in an SQLite database.
        Allows retrieval and decompression of stored files.


Troubleshooting:
1) SQLite not found? Install it with:
   sudo apt install libsqlite3-dev   # Linux
   brew install sqlite3              # macOS
2) File not found? Ensure the input file exists before running commands.
3) Compilation error? Ensure you use -lsqlite3 when compiling.

   
  🎯 Future Enhancements

🔹 Support for binary files
🔹 Compression ratio improvements
🔹 GUI version using Qt
