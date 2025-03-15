#ifndef FILE_DATABASE_H
#define FILE_DATABASE_H

#include <string>

void initializeDatabase();
void saveFileToDatabase(const std::string& originalFile, const std::string& processedFile, bool isCompressed);

#endif
