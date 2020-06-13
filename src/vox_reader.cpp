#include "vox_reader.h"

using namespace std;

void readInt(uint32_t &integer, istream &file)
{
	file.read(reinterpret_cast<char*>(&integer), sizeof(integer));
}	


int idToInt(int a, int b, int c, int d)
{
	return (a | b<<8 | c<<16 | d<<24);
}

bool isHeaderValid(std::istream &file)
{
	uint32_t temp_uint32;

	//Check the file is a vox file by checking for:
	//1) Starts with "VOX "
	//2) Followed by version number 150
	//3) Content starts with "MAIN"
	readInt(temp_uint32, file);
	if(temp_uint32 != idToInt('V', 'O', 'X', ' '))
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
	if(temp_uint32 != idToInt('M', 'A', 'I', 'N'))
	{
		cerr << "File does not appear to be a valid .vox file (No MAIN)\n";
		return false;
	}

	return true;
}

vector<int> readVoxFile( char* filepath)
{
	ifstream file;

	file.open(filepath, ios::binary);

	if(file.is_open())
	{
		if(isHeaderValid(file) == false)
			return vector<int>{};

		file.close();
		return vector<int>{1};
	}

	cerr << "Unable to read file\n";
	return vector<int>{};
}
