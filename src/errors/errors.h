#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

typedef enum {
    MATRIX_SUCCESS = 0,
    MATRIX_NULL_PTR_ERR,
    MATRIX_STRUCT_MEM_ALLOC_ERR,
    MATRIX_DATA_MEM_ALLOC_ERR,
    MATRIX_INVALID_SIZE_ERR,
    MATRIX_DIMENSIONS_MISMATCH,
    MATRIX_IS_NOT_SQUARE_ERR,
    MATRIX_FILE_READ_ERR,
    MATRIX_ERROR_COUNT
} MatrixErrorCode;

const char *getErrorMessage(const MatrixErrorCode errCode);
MatrixErrorCode checkMatrixSize(size_t rows, size_t cols);

#endif