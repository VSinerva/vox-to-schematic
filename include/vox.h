#ifndef VOX_H
#define VOX_H

#include <cstdint> 
#include <vector>

class xyz
{
	public:

	int x;
	int y;
	int z;

	void translate(xyz translation);

	xyz() : x(0), y(0), z(0)
	{
	}

	xyz(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
	{
	}
};

struct voxel
{
	xyz loc;
	int colorIndex;

	voxel() : colorIndex(0)
	{
	}

	voxel(xyz _loc, int _colorIndex) : loc(_loc), colorIndex(_colorIndex)
	{
	}
};

class model
{
	public:
		int id;
		xyz size;

		std::vector<voxel> data;

		void translate(xyz translation);

		model(int _id, xyz _size);
};

class node
{
	public:
		xyz translation;

		std::vector<int> childNodes;

		void translate(xyz translation);
};

#endif
