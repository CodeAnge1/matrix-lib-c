#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

typedef enum {
	SUCCESS = 0,
	NULL_PTR_ERR,
	STRUCT_MEM_ALLOC_ERR,
	DATA_MEM_ALLOC_ERR,
	INVALID_SIZE_ERR,
	DIMENSIONS_MISMATCH_ERR,
	IS_NOT_SQUARE_ERR,
	CANNOT_EXCLUDE_ROW_COL,
	CANNOT_MULTIPLY_MATRICES,
	FILE_WRITE_ERR,
	FILE_READ_ERR,
	EMPTY_FILE_ERR,
	INVALID_INPUT_DATA_ERR,
	NOT_ENOUGH_VALUES_ERR,
	TOO_MANY_VALUES_ERR,
	LINE_TOO_LONG_ERR,
	FAILED_CONVERT_TO_BUFFER,
	ERROR_COUNT
} MatrixErrorCode;

#include "../matrix/matrix.h"

const char*		getErrorMessage(const MatrixErrorCode errCode);
MatrixErrorCode checkMatrixSize(const size_t rows, const size_t cols);
MatrixErrorCode matrixSizesIsEqual(const Matrix* A, const Matrix* B);
MatrixErrorCode canExclude(const size_t count, const size_t currentIndex);
MatrixErrorCode canMultiplyMatrices(const Matrix* A, const Matrix* B);
MatrixErrorCode checkVariableCount(const Matrix* A, const size_t count);

#endif