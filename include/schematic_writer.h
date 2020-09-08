#ifndef SCHEMATIC_WRITER_H
#define SCHEMATIC_WRITER_H

#include "matrix.h"
#include "zlib.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

void writeByte(uint8_t byte, std::ostream &file);
void writeShort(uint16_t integer, std::ostream &file);
void writeInt(uint32_t integer, std::ostream &file);
void writeString(const char* writeString, std::ostream &file);
void writeTag(uint8_t byte, const char* tagName, std::ostream &file);

void writeSize(const intMatrix_t &matrix, std::ostream &file);
void writeBlocks(const std::vector<uint8_t> &blockIds, const intMatrix_t &matrix, std::ostream &file);
void writeData(const std::vector<uint8_t> &dataValues, const intMatrix_t &matrix, std::ostream &file);
void writeEntityLists(std::ostream &file);

void readPaletteFile(std::vector<uint8_t> &paletteVector, char* filepath);
int writeSchematicFile(	const std::vector<uint8_t> &blockIds,
												const std::vector<uint8_t> &dataValues,
												const intMatrix_t &matrix,
												const char* filepath);

#endif
