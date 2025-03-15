#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Initialize SQLite database
void initializeDatabase() {
    sqlite3* db;
    char* errMessage = nullptr;
    int rc = sqlite3_open("files.db", &db);
    
    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    } else {
        const char* sql = "CREATE TABLE IF NOT EXISTS Files ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "Filename TEXT UNIQUE, "
                          "Compressed BLOB);";
        rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMessage);
        
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMessage << endl;
            sqlite3_free(errMessage);
        }
    }
    sqlite3_close(db);
}

// Read file contents into a vector
vector<unsigned char> readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    return vector<unsigned char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Write file contents from a vector
void writeFile(const string& filename, const vector<unsigned char>& data) {
    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

// Store compressed file in the database
void storeCompressedFile(const string& filename, const string& compressedFilename) {
    sqlite3* db;
    sqlite3_open("files.db", &db);
    
    vector<unsigned char> compressedData = readFile(compressedFilename);
    
    string sql = "INSERT INTO Files (Filename, Compressed) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, filename.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, compressedData.data(), compressedData.size(), SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error storing compressed file: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Compressed file stored in database.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Retrieve a compressed file from the database
vector<unsigned char> retrieveCompressedFile(const string& filename) {
    sqlite3* db;
    sqlite3_open("files.db", &db);
    
    string sql = "SELECT Compressed FROM Files WHERE Filename = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, filename.c_str(), -1, SQLITE_STATIC);

    vector<unsigned char> compressedData;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int dataSize = sqlite3_column_bytes(stmt, 0);
        const unsigned char* dataPtr = static_cast<const unsigned char*>(sqlite3_column_blob(stmt, 0));
        compressedData.assign(dataPtr, dataPtr + dataSize);
    } else {
        cerr << "File not found in database.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return compressedData;
}
