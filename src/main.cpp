#include "vox_reader.h"
#include "schematic_writer.h"

int main(int argc, char* argv[])
{
	intMatrix_t matrix{ readVoxFile(argv[1]) };	
	if(matrix.empty())
	{
		std::cerr << "Aborting...\n";
	}

	writeSchematicFile(matrix, argv[2]);

	return 0;
}
