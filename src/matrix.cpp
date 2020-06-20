#include "matrix.h"

using namespace std;

void resizeMatrix(intMatrix_t &matrix, int size_x, int size_y, int size_z)
{
	matrix.resize(size_x);

	for(vector<vector<int>> &vec1 : matrix)
	{
		vec1.resize(size_y);

		for(vector<int> &vec2 : vec1)
		{
			vec2.resize(size_z);
		}
	}
}
