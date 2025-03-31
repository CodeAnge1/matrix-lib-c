#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "../errors/errors.h"
#include "../../include/config.h"


typedef struct {
	size_t rows; ///< Количество строк
	size_t cols; ///< Количество столбцов
	MATRIX_TYPE** data; ///< Данные матрицы
} Matrix;

MatrixErrorCode createMatrix(size_t rows, size_t cols, Matrix **newMatrix);

void freeMatrix(Matrix** matrix);

#endif // MATRIX_H
