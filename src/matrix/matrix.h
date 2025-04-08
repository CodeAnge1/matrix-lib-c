#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/config.h"

typedef struct {
	size_t		  rowC;
	size_t		  colC;
	MATRIX_TYPE** data;
} Matrix;

#include "../errors/errors.h"

typedef struct {
	Matrix*			matrix;
	MatrixErrorCode error;
} MatrixResult;

typedef struct {
	DETERMINANT_TYPE determinant;
	MatrixErrorCode	 error;
} DeterminantResult;

MatrixResult createMatrix(size_t rows, size_t cols);

void freeMatrix(Matrix** matrix);

void fillMatrix(MatrixResult* res, const MATRIX_TYPE* data);

MatrixResult createMinor(MatrixResult A, size_t excludeRowIndex,
						 size_t excludeColIndex);

MatrixResult getSumOrDiffMatrices(const MatrixResult A,
								  const MatrixResult B, bool getDiff);

MatrixResult getMatrixCopy(const MatrixResult source);

MatrixResult transposeMatrix(const MatrixResult A);

DeterminantResult findDeterminant(const MatrixResult A);

void printMatrix(const MatrixResult matrixResult);

#endif	// MATRIX_H
