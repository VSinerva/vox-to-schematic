#ifndef VOX_READER_H
#define VOX_READER_H

#include "vox.h"

#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <cstdint>

void readInt(uint32_t &integer, std::istream &file);

int idToInt(int a, int b, int c, int d);
bool isHeaderValid(std::istream &file);

std::vector<int> readVoxFile(char* filepath);

#endif
