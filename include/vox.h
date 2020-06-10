#ifndef VOX_H
#define VOX_H

struct xyz
{
	int x;
	int y;
	int z;

	xyz(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
	{
	}
};

struct voxel
{
	xyz loc;
	int colorIndex;
	
	voxel(xyz _loc, int _colorIndex) : loc(_loc), colorIndex(_colorIndex)
	{
	}
};

#endif
