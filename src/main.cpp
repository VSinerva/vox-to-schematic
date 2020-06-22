#include "vox_reader.h"
#include "schematic_writer.h"

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cerr << "Incorrect number of arguments!\n";
		return 1;
	}

	intMatrix_t matrix{ readVoxFile(argv[1]) };	
	if(matrix.empty())
	{
		std::cerr << "Aborting...\n";
		return 1;
	}

	if(writeSchematicFile(matrix, argv[2]) != 0)
	{
		std::cerr << "Aborting...\n";
		return 1;
	}

	return 0;
}
