#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>

using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) {  // Leaf node
        huffmanCodes[root->data] = code;
    }
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

//Build Huffman Tree
Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    return pq.top();
}

//Write Huffman Tree to file
void writeHuffmanTree(ofstream &outFile, Node* root) {
    if (!root) return;
    if (!root->left && !root->right) {
        outFile.put('1');  //Leaf indicator
        outFile.put(root->data);
    } else {
        outFile.put('0');  //Internal node indicator
    }
    writeHuffmanTree(outFile, root->left);
    writeHuffmanTree(outFile, root->right);
}

//Read Huffman Tree from file
Node* readHuffmanTree(ifstream &inFile) {
    char flag;
    inFile.get(flag);
    if (flag == '1') {
        char data;
        inFile.get(data);
        return new Node(data, 0);
    }
    Node* node = new Node('\0', 0);
    node->left = readHuffmanTree(inFile);
    node->right = readHuffmanTree(inFile);
    return node;
}

//Compress a file using Huffman coding
void compressFile(const string& inputFile, const string& outputFile) {
    unordered_map<char, int> freqMap;
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open " << inputFile << endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
    }
    inFile.clear();
    inFile.seekg(0);

    Node* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Could not create " << outputFile << endl;
        return;
    }

    //Write the Huffman Tree to the output file
    writeHuffmanTree(outFile, root);

    //Encode the file content as binary
    string bitString = "";
    while (inFile.get(ch)) {
        bitString += huffmanCodes[ch];
    }

    //Add padding to make it a multiple of 8 bits
    int padding = 8 - (bitString.length() % 8);
    if (padding != 8) {
        bitString.append(padding, '0');
    }
    
    //Store padding information
    outFile.put(padding);

    //Convert bitString to bytes and write
    for (size_t i = 0; i < bitString.size(); i += 8) {
        bitset<8> byte(bitString.substr(i, 8));
        outFile.put(static_cast<unsigned char>(byte.to_ulong()));
    }

    inFile.close();
    outFile.close();
}

//Decompress a file using Huffman coding
void decompressFile(const string& compressedFile, const string& outputFile) {
    ifstream inFile(compressedFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open " << compressedFile << endl;
        return;
    }

    //Read the Huffman Tree
    Node* root = readHuffmanTree(inFile);

    //Read the padding information
    char padding;
    inFile.get(padding);
    int padBits = static_cast<int>(padding);

    //Read compressed binary data
    string bitString = "";
    char byte;
    while (inFile.get(byte)) {
        bitString += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }
    if (padBits > 0) {
        bitString = bitString.substr(0, bitString.size() - padBits);
    }

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Could not create " << outputFile << endl;
        return;
    }

    //Decode binary data using Huffman Tree
    Node* node = root;
    for (char bit : bitString) {
        node = (bit == '0') ? node->left : node->right;
        if (!node->left && !node->right) {
            outFile.put(node->data);
            node = root;
        }
    }

    inFile.close();
    outFile.close();
}
