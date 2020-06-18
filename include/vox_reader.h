#ifndef VOX_READER_H
#define VOX_READER_H

#include "vox.h"

#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <cstdint>

using intMatrix_t = std::vector<std::vector<std::vector<int>>>;

void readInt(uint32_t &integer, std::istream &file);
void readByte(uint8_t &byte, std::istream &file);
std::vector<int> readTranslation(std::istream &file);
uint32_t tagToInt32(char a, char b, char c, char d);

//TEMP!
//Rotation not implemented
uint8_t readRotation(std::istream &file);

bool isHeaderValid(std::istream &file);
std::vector<model> readModels(std::istream &file);
std::vector<node> readNodes(std::istream &file);

intMatrix_t readVoxFile( char* filepath);

#endif
