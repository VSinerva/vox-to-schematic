#include "vox.h"
#include <cstdint>

model::model(int _id, xyz _size) : id(_id), size(_size)
{
	//Store voxel for each xyz location to allow xyz-based indexing
	//without knowing anything about the model as a whole 
	data = new voxel[size.x * size.y * size.z]{};

	//Give locations within the model to each voxel
	for( int x{ 0 }; x < size.x; ++x)
	{
		for( int y{ 0 }; y < size.y; ++y)
		{
			for( int z{ 0 }; z < size.z; ++z)
			{
				data[x + size.x*( y + z*size.y)].loc = xyz(x, y, z);
			}
		}
	}
}

void model::translate(xyz trans)
{
	//Loop over all elements with nested for-loops instead of a for-each
	//because dynamic-arrays don't work with a for-each loop
	for( int x{ 0 }; x < size.x; ++x)
	{
		for( int y{ 0 }; y < size.y; ++y)
		{
			for( int z{ 0 }; z < size.z; ++z)
			{
				xyz temp = data[x + size.x*( y + z*size.y)].loc;

				data[x + size.x*( y + z*size.y)].loc = xyz(
						temp.x + trans.x,
						temp.y + trans.y,
						temp.z + trans.z);
			}
		}
	}
}

void model::rotate(std::uint8_t rotationMatrix)
{
	//TODO: Figure out rotation matrices
}
