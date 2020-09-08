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

	std::vector<uint8_t> blockIds(256, 0);
	std::vector<uint8_t> dataValues(256, 0);

	readPaletteFile(blockIds, "./blockIds.config");
	readPaletteFile(dataValues, "./dataValues.config");
	if(writeSchematicFile(blockIds, dataValues, matrix, argv[2]) != 0)
	{
		std::cerr << "Aborting...\n";
		return 1;
	}

	return 0;
}
