#include "schematic_writer.h"

using namespace std;

void writeByte(uint8_t &byte, ostream &file)
{
	file.write(reinterpret_cast<char*>(&byte), sizeof(byte));
}

void writeShort(uint16_t integer, ostream &file)
{
	//Convert default little-endian short to big-endian
	integer = ((integer & 0b0000'0000'1111'1111) << 8) + ((integer & 0b1111'1111'0000'0000) >> 8);

	file.write(reinterpret_cast<char*>(&integer), sizeof(integer));
}

void writeString(const char* writeString, ostream &file)
{
	writeShort(static_cast<uint16_t>(strlen(writeString)), file);

	file.write(writeString, strlen(writeString));
}

void writeTag(uint8_t tagByte, const char* tagName, ostream &file)
{
	writeByte(tagByte, file);
	writeShort(static_cast<uint16_t>(strlen(tagName)), file);

	file.write(tagName, strlen(tagName));
}


void writeSize(intMatrix_t &matrix, ostream &file)
{
	uint16_t xSize{static_cast<uint16_t>(matrix.size())};
	uint16_t ySize{static_cast<uint16_t>(matrix[0].size())};
	uint16_t zSize{static_cast<uint16_t>(matrix[0][0].size())};

	writeTag(uint8_t{2}, "Width", file);
	writeShort(xSize, file);

	writeTag(uint8_t{2}, "Height", file);
	writeShort(ySize, file);

	writeTag(uint8_t{2}, "Length", file);
	writeShort(zSize, file);
}

void writeSchematicFile(intMatrix_t &matrix, char* filepath)
{
	ofstream file;

	file.open(filepath, ios::binary);

	if(file.is_open())
	{
		writeTag(uint8_t{10}, "Schematic", file);

		writeSize(matrix, file);

		writeTag(uint8_t{8}, "Materials", file);
		writeString("Alpha", file);

		file.close();
	}

	else
		cerr << "Unable to write file\n";
}
