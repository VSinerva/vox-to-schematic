#include "vox.h"


//XYZ
void xyz::translate(xyz translation)
{
	x += translation.x;
	y += translation.y;
	z += translation.z;
}


//MODEL
model::model(int _id, xyz _size) : id(_id), size(_size)
{
	//Store voxel for each xyz location to allow xyz-based indexing
	//without knowing anything about the model as a whole 
	data = std::vector<voxel>(size.x * size.y * size.z);

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

void model::translate(xyz translation)
{
	//Loop over all elements with nested for-loops instead of a for-each
	//because dynamic-arrays don't work with a for-each loop
	for( int x{ 0 }; x < size.x; ++x)
	{
		for( int y{ 0 }; y < size.y; ++y)
		{
			for( int z{ 0 }; z < size.z; ++z)
			{
				data[x + size.x*( y + z*size.y)].loc.translate(translation);
			}
		}
	}
}
