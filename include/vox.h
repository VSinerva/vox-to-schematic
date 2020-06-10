#ifndef VOX_H
#define VOX_H

#include <cstdint> 

struct xyz
{
	int x;
	int y;
	int z;

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
	private:
		int id;
		xyz size;

		voxel *data;

	public:
		int getId(){ return id; }
		void setId(int _id) { id=_id; }

		xyz getSize(){ return size; }
		void setSize(xyz _size){ size=_size; }

		void translate(xyz translation);
		void rotate(std::uint8_t rotationMatrix);

		model(int _id, xyz _size);

		~model()
		{
			delete[] data;
			data = nullptr;
		}
};

#endif
