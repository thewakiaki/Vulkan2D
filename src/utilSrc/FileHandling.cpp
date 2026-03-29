#include "utils/FileHandling.h"

std::vector<char> FileHandling::ParseFile(const char* filePath){

     std::vector<char> buffer;

     FILE* file = fopen(filePath, "rb");


     if(!file){
         std::string fileName =filePath;
         throw std::runtime_error("Couldnt open file: " + fileName);
     }

     fseek(file, 0, SEEK_END);
     long fileSize = ftell(file);
     fseek(file, 0, SEEK_SET);

     buffer.resize(fileSize);
     fread(buffer.data(), sizeof(char), fileSize, file);

     fclose(file);

     return buffer;
}
