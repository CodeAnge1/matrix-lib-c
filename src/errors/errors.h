#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

typedef enum {
	SUCCESS = 0,
	NULL_PTR_ERR,
	STRUCT_MEM_ALLOC_ERR,
	DATA_MEM_ALLOC_ERR,
	INVALID_SIZE_ERR,
	DIMENSIONS_MISMATCH,
	IS_NOT_SQUARE_ERR,
	CANNOT_EXCLUDE_ROW_COL,
	FILE_READ_ERR,
	ERROR_COUNT
} MatrixErrorCode;

#include "../matrix/matrix.h"

const char*		getErrorMessage(const MatrixErrorCode errCode);
MatrixErrorCode checkMatrixSize(const size_t rows, const size_t cols);
MatrixErrorCode compareMatrixSizes(const Matrix* A, const Matrix* B);
MatrixErrorCode canExclude(const size_t count, const size_t currentIndex);

#endif