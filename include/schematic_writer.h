#ifndef SCHEMATIC_WRITER_H
#define SCHEMATIC_WRITER_H

#include "matrix.h"
#include "zlib.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

const std::vector<uint8_t> blockIds
{
	1
};
const std::vector<uint8_t> dataValues
{
	2
};

void writeByte(uint8_t byte, std::ostream &file);
void writeShort(uint16_t integer, std::ostream &file);
void writeInt(uint32_t integer, std::ostream &file);
void writeString(const char* writeString, std::ostream &file);
void writeTag(uint8_t byte, const char* tagName, std::ostream &file);

void writeSize(intMatrix_t &matrix, std::ostream &file);
void writeBlocks(intMatrix_t &matrix, std::ostream &file);
void writeData(intMatrix_t &matrix, std::ostream &file);

int writeSchematicFile(intMatrix_t &matrix, char* filepath);

#endif
