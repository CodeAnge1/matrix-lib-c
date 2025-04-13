#ifndef MATRIX_H
#define MATRIX_H
#define _GNU_SOURCE

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#include "../output/output.h"

typedef struct {
	DETERMINANT_TYPE determinant;
	MatrixErrorCode	 error;
} DeterminantResult;

MatrixResult createMatrix(const size_t rows, const size_t cols);

void freeMatrix(Matrix** matrix);

void freeMatrixResult(MatrixResult* res);

void fillMatrix(MatrixResult* A, const MATRIX_TYPE* data);

MatrixResult loadMatrixFromFile(const char* filename);

MatrixResult createMinor(const MatrixResult A,
						 const size_t		excludeRowIndex,
						 const size_t		excludeColIndex);

MatrixResult getSumOrDiffMatrices(const MatrixResult A,
								  const MatrixResult B, bool getDiff);

MatrixResult getMatrixCopy(const MatrixResult source);

MatrixResult transposeMatrix(const MatrixResult A);

DeterminantResult findDeterminant(const MatrixResult A);

MatrixResult multiplyMatrices(const MatrixResult A, const MatrixResult B);

char* convertMatrixToBuffer(const MatrixResult A);

#endif	// MATRIX_H
