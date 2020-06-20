#include "vox.h"
#include <vector>


//MODEL
model::model(int _id, int _size_x, int _size_y, int _size_z) :
	id(_id), size_x(_size_x), size_y(_size_y), size_z(_size_z)
{
	for(int x{0}; x < size_x; ++x)
	{
		data.push_back(std::vector<std::vector<voxel>>());
		for(int y{0}; y < size_y; ++y)
		{
			data.back().push_back(std::vector<voxel>(size_z));
		}
	}

	//Give locations within the model to each voxel
	for( int x{0}; x < size_x; ++x)
	{
		for( int y{0}; y < size_y; ++y)
		{
			for( int z{0}; z < size_z; ++z)
			{
				data[x][y][z].x = x;
				data[x][y][z].y = y;
				data[x][y][z].z = z;
			}
		}
	}
}

voxel& model::at(int x, int y, int z)
{
	return data[x][y][z];
}

//TEMP!
//Rotation not implemented
void model::rotate(uint8_t rot)
{
}

void model::translate(int trans_x, int trans_y, int trans_z)
{
	for( std::vector<std::vector<voxel>> &vec1 : data )
	{
		for( std::vector<voxel> &vec2 : vec1 )
		{
			for( voxel &vox : vec2 )
			{
				vox.x += trans_x;
				vox.y += trans_y;
				vox.z += trans_z;
			}
		}
	}
}


//NODE
//TEMP!
//Rotation not implemented
void node::rotate(uint8_t rot)
{
}

void node::translate(int trans_x, int trans_y, int trans_z)
{
	translation_x += trans_x;
	translation_y += trans_y;
	translation_z += trans_z;
}
