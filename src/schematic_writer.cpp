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
	integer = ((integer & 0b0000'0000'0000'0000'0000'0000'1111'1111) << 24)
					+ ((integer & 0b0000'0000'0000'0000'1111'1111'0000'0000) << 8)
					+ ((integer & 0b0000'0000'1111'1111'0000'0000'0000'0000) >> 8)
					+ ((integer & 0b1111'1111'0000'0000'0000'0000'0000'0000) >> 24);

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

void writeBlocks(intMatrix_t &matrix, ostream &file)
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
				writeByte(blockIds[matrix[x][y][z]], file);
			}
		}
	}
}

void writeData(intMatrix_t &matrix, ostream &file)
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
				writeByte(dataValues[matrix[x][y][z]], file);
			}
		}
	}
}


int writeSchematicFile(intMatrix_t &matrix, char* filepath)
{
	fstream file;

	file.open(filepath, ios::binary | ios::out);

	if(file.is_open())
	{
		//Check size of matrix.
		//Max 256x256x256
		vector<int> sizes{getMatrixSize(matrix)};
		if(sizes[0] < 1 || sizes[0] > 256 ||
				sizes[1] < 1 || sizes[1] > 256 ||
				sizes[2] < 1 || sizes[2] > 256)
		{
			file.close();
			return 1;
		}

		writeTag(uint8_t{10}, "Schematic", file);

		writeSize(matrix, file);

		writeTag(uint8_t{8}, "Materials", file);
		writeString("Alpha", file);

		writeBlocks(matrix, file);
		writeData(matrix, file);

		//Write ending tag for file
		writeByte(0, file);

		//Close file and reopen in read mode
		file.close();
		file.open(filepath, ios::binary | ios::in | ios::ate);

		//Read contents of resulting file into memory for compression
		streampos size{file.tellg()};
		char* memBlock{new char[size]};
		file.seekg(0, ios::beg);
		file.read(memBlock, size);
		file.close();

		//Compress resulting file with gzip
		gzFile fi = gzopen(filepath,"wb");
		gzwrite(fi, memBlock, size);
		gzclose(fi);

		delete[] memBlock;
		return 0;
	}

	cerr << "Unable to write file\n";
	return 1;
}
