#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using intMatrix_t = std::vector<std::vector<std::vector<int>>>;

void resizeMatrix(intMatrix_t &matrix, int size_x, int size_y, int size_z);

#endif
