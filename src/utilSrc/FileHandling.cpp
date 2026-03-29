#include "utils/FileHandling.h"

std::vector<uint32_t> FileHandling::ParseFile(const char* filePath){

     std::vector<uint32_t> buffer;

     FILE* file = fopen(filePath, "rb");


     if(!file){
         std::string fileName =filePath;
         throw std::runtime_error("Couldnt open file: " + fileName);
     }

     fmt::print("Parsing file: {}\n", filePath);

     uint32_t stepSize = sizeof(uint32_t);

     fseek(file, 0, SEEK_END);
     long fileSize = ftell(file);
     fseek(file, 0, SEEK_SET);

     if((fileSize == 0) || fileSize % stepSize != 0){
         throw std::runtime_error("Invalid spirv file");
     }

     uint32_t wordCount = fileSize / stepSize;

     buffer.resize(wordCount);
     fread(buffer.data(), stepSize, wordCount, file);

     fclose(file);

     return buffer;
}
