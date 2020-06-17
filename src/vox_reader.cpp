#include "vox_reader.h"

using namespace std;

void readInt(uint32_t &integer, istream &file)
{
	file.read(reinterpret_cast<char*>(&integer), sizeof(integer));
}	

void readByte(uint8_t &byte, istream &file)
{
	file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
}	

uint32_t tagToInt32(char a, char b, char c, char d)
{
	return (a | b<<8 | c<<16 | d<<24);
}


bool isHeaderValid(istream &file)
{
	uint32_t temp_uint32;

	//Check the file is a vox file by checking for:
	//1) Starts with "VOX "
	//2) Followed by version number 150
	//3) Content starts with "MAIN"
	readInt(temp_uint32, file);
	if(temp_uint32 != tagToInt32('V', 'O', 'X', ' '))
	{
		cerr << "File does not appear to be a valid .vox file (No or incorrect filetype in header)\n";
		return false;
	}

	readInt(temp_uint32, file);
	if(temp_uint32 != 150)
	{
		cerr << "File does not appear to be a valid .vox file (No or incorrect version number)\n";
		return false;
	}

	readInt(temp_uint32, file);
	if(temp_uint32 != tagToInt32('M', 'A', 'I', 'N'))
	{
		cerr << "File does not appear to be a valid .vox file (No MAIN)\n";
		return false;
	}

	return true;
}

vector<model> readModels(uint32_t &tag, istream &file)
{
	readInt(tag, file);

	//Variable to assign sequential ids to models
	int id{0};

	uint32_t sizeTag	{ tagToInt32( 'S', 'I', 'Z', 'E') };
	vector<model> models{};

	while(tag == sizeTag )
	{
		//Skip chunk info after "SIZE" tag (8 bytes)
		file.seekg(8, ios::cur);

		uint32_t size_x;
		uint32_t size_y;
		uint32_t size_z;
		readInt(size_x, file);
		readInt(size_y, file);
		readInt(size_z, file);

		models.push_back( model(id++, size_x, size_y, size_z));

		//Skip "XYZI" tag and its chunk info (12 bytes)
		file.seekg(12, ios::cur);

		uint32_t nOfModels;
		uint8_t x{0};
		uint8_t y{0};
		uint8_t z{0};
		uint8_t colByte{0};
		readInt(nOfModels, file);
		for( int i{0}; i < nOfModels; ++i)
		{
			readByte(x, file);
			readByte(y, file);
			readByte(z, file);
			readByte(colByte, file);
			models.back().data[x][y][z].colorIndex = colByte;
		}

		//Read tag for next chunk
		readInt(tag, file);
	}

	return models;
}


intMatrix_t readVoxFile( char* filepath)
{
	ifstream file;

	file.open(filepath, ios::binary);

	if(file.is_open())
	{
		uint32_t tag{0};

		if(isHeaderValid(file) == false)
			return intMatrix_t{}; 

		//Skip chunk info after "MAIN" tag (8 bytes) and read next tag
		file.seekg(8, ios::cur);

		//Read models
		//Tag will contain first NON-MODEL (SIZE or XYZI) tag!
		vector<model> models{readModels(tag, file)};

		file.close();
		intMatrix_t tempMatrix{1};
		return tempMatrix; 
	}

	cerr << "Unable to read file\n";
	return intMatrix_t{}; 
}
