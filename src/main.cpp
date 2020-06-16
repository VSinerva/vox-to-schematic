#include "vox_reader.h"
#include "schematic.h"

int main(int argc, char* argv[])
{
	intMatrix_t matrix{ readVoxFile(argv[1]) };	
	if(matrix.empty())
	{
		std::cerr << "Aborting...\n";
		return 1;
	}

	return 0;
}
