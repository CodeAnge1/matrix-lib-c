#include "matrix.h"

MatrixErrorCode createMatrix(size_t rows, size_t cols, Matrix **newMatrix){
    MatrixErrorCode resultStatus = MATRIX_SUCCESS;
    MatrixErrorCode sizeErr = checkMatrixSize(rows, cols);

    *newMatrix = (Matrix *)malloc(sizeof(Matrix));
    if (*newMatrix == NULL) {
        resultStatus = MATRIX_STRUCT_MEM_ALLOC_ERR;
    }

    if (resultStatus == MATRIX_SUCCESS && sizeErr == MATRIX_SUCCESS) {
        (*newMatrix)->rows = rows;
        (*newMatrix)->cols = cols;

        (*newMatrix)->data = (MATRIX_TYPE **)(calloc(rows, sizeof(MATRIX_TYPE*)));

        if ((*newMatrix)->data == NULL)
            resultStatus = MATRIX_DATA_MEM_ALLOC_ERR;

        for (size_t iter = 0; iter < rows && resultStatus == MATRIX_SUCCESS; ++iter){
            (*newMatrix)->data[iter] = (MATRIX_TYPE*)(calloc(cols, sizeof(MATRIX_TYPE)));
            
            if ((*newMatrix)->data[iter] == NULL){
                resultStatus = MATRIX_DATA_MEM_ALLOC_ERR;
            }
        }
    }

    if (resultStatus != MATRIX_SUCCESS) {
        freeMatrix(newMatrix);
    }

    return resultStatus;
}

void freeMatrix(Matrix** matrix){
    if (*matrix != NULL) {
        if ((*matrix)->data != NULL) {
            for (size_t iter = 0; iter < (*matrix)->rows; ++iter){
                if ((*matrix)->data[iter] != NULL)
                    free((*matrix)->data[iter]);
            }
            free((*matrix)->data);
            (*matrix)->data = NULL;
        }
        free(*matrix);
        *matrix = NULL;
    }
}
