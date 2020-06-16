#ifndef VOX_H
#define VOX_H

#include <cstdint> 
#include <vector>

struct voxel
{
	int x{0};
	int y{0};
	int z{0};
	int colorIndex{0};
};

using voxelMatrix_t = std::vector<std::vector<std::vector<voxel>>>;

class model
{
	public:
		int id;
		int size_x;
		int size_y;
		int size_z;

		voxelMatrix_t data;

		voxel& at(int x, int y, int z);
		void translate(int trans_x, int trans_y, int trans_z);

		model(int _id, int _size_x, int _size_y, int _size_z);
};

class node
{
	public:
		int translation_x;
		int translation_y;
		int translation_z;

		std::vector<int> childNodes;

		void translate(int trans_x, int trans_y, int trans_z);
};

#endif
