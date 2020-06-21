#ifndef SCHEMATIC_WRITER_H
#define SCHEMATIC_WRITER_H

#include "matrix.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

void writeByte(uint8_t &byte, std::ostream &file);
void writeShort(uint16_t integer, std::ostream &file);
void writeString(const char* writeString, std::ostream &file);
void writeTag(std::vector<uint8_t> &bytes, const char* tagName, std::ostream &file);

void writeSize(intMatrix_t &matrix, std::ostream &file);

void writeSchematicFile(intMatrix_t &matrix, char* filepath);

#endif
