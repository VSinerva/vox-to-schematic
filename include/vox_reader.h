#ifndef VOX_READER_H
#define VOX_READER_H

#include "vox.h"
#include "matrix.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>


void readInt(uint32_t &integer, std::istream &file);
void readByte(uint8_t &byte, std::istream &file);
//TEMP!
//Rotation not implemented
uint8_t readRotation(std::istream &file);
std::vector<int> readTranslation(std::istream &file);
uint32_t tagToInt32(char a, char b, char c, char d);


bool isHeaderValid(std::istream &file);
std::vector<model> readModels(std::istream &file);
node readTranslationNode(std::istream &file);
node readGroupNode(std::istream &file);
node readShapeNode(std::istream &file);
std::vector<node> readNodes(std::istream &file);
//TEMP!
//Rotation not implemented
void applyRotations(std::vector<node> nodes, std::vector<model> &models);
void applyTranslations(std::vector<node> nodes, std::vector<model> &models);
std::vector<int> getSizeAndMinsForMatrix(std::vector<model> models);
intMatrix_t modelsToMatrix(std::vector<model> models);

intMatrix_t readVoxFile( char* filepath);

#endif
