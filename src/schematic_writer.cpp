#include "schematic_writer.h"

using namespace std;

void writeByte(uint8_t byte, ostream &file)
{
	file.write(reinterpret_cast<char*>(&byte), sizeof(byte));
}

void writeShort(uint16_t integer, ostream &file)
{
	//Convert default little-endian short to big-endian
	integer = ((integer & 0b0000'0000'1111'1111) << 8)
					+ ((integer & 0b1111'1111'0000'0000) >> 8);

	file.write(reinterpret_cast<char*>(&integer), sizeof(integer));
}

void writeInt(uint32_t integer, ostream &file)
{
	//Convert default little-endian int to big-endian
	integer = ((integer & 0b0000'0000'0000'0000'0000'0000'0000'1111) << 28)
					+ ((integer & 0b0000'0000'0000'0000'0000'0000'1111'0000) << 20)
					+ ((integer & 0b0000'0000'0000'0000'0000'1111'0000'0000) << 12)
					+ ((integer & 0b0000'0000'0000'0000'1111'0000'0000'0000) << 4)
					+ ((integer & 0b0000'0000'0000'1111'0000'0000'0000'0000) >> 4)
					+ ((integer & 0b0000'0000'1111'0000'0000'0000'0000'0000) >> 12)
					+ ((integer & 0b0000'1111'0000'0000'0000'0000'0000'0000) >> 20)
					+ ((integer & 0b1111'0000'0000'0000'0000'0000'0000'0000) >> 28);

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
	vector<int> sizes{getMatrixSize(matrix)};
	uint16_t xSize{static_cast<uint16_t>(sizes[0])};
	uint16_t ySize{static_cast<uint16_t>(sizes[1])};
	uint16_t zSize{static_cast<uint16_t>(sizes[2])};

	writeTag(uint8_t{2}, "Width", file);
	writeShort(xSize, file);

	writeTag(uint8_t{2}, "Height", file);
	writeShort(ySize, file);

	writeTag(uint8_t{2}, "Length", file);
	writeShort(zSize, file);
}

void writeBlocks(intMatrix_t &matrix, std::ostream &file)
{
	vector<int> sizes{getMatrixSize(matrix)};

	writeTag(7, "Blocks", file);
	writeInt(sizes[0] * sizes[1] * sizes[2], file);

	for(int y{0}; y < sizes[1]; ++y)
	{
		for(int z{0}; z < sizes[2]; ++z)
		{
			for(int x{0}; x < sizes[0]; ++x)
			{
				writeByte(blockIds[0], file);
			}
		}
	}
}

void writeData(intMatrix_t &matrix, std::ostream &file)
{
	vector<int> sizes{getMatrixSize(matrix)};

	writeTag(7, "Data", file);
	writeInt(sizes[0] * sizes[1] * sizes[2], file);

	for(int y{0}; y < sizes[1]; ++y)
	{
		for(int z{0}; z < sizes[2]; ++z)
		{
			for(int x{0}; x < sizes[0]; ++x)
			{
				writeByte(dataValues[0], file);
			}
		}
	}
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

		writeBlocks(matrix, file);
		writeData(matrix, file);

		//Write ending tag for file
		writeByte(0, file);

		file.close();
	}

	else
		cerr << "Unable to write file\n";
}
