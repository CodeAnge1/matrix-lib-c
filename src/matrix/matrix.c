#include "matrix.h"

MatrixResult createMatrix(const size_t rows, const size_t cols) {

	Matrix*		 newMatrix = (Matrix*)calloc(1, sizeof(Matrix));
	MatrixResult out	   = {.matrix = NULL, .error = SUCCESS};

	if (newMatrix == NULL) {
		out.error = STRUCT_MEM_ALLOC_ERR;
	} else if (checkMatrixSize(rows, cols) == SUCCESS) {
		(newMatrix)->rowC = rows;
		(newMatrix)->colC = cols;

		(newMatrix)->data =
			(MATRIX_TYPE**)(calloc(rows, sizeof(MATRIX_TYPE*)));

		if (newMatrix->data == NULL) out.error = DATA_MEM_ALLOC_ERR;

		for (size_t iter = 0; iter < rows && out.error == SUCCESS;
			 ++iter) {
			newMatrix->data[iter] =
				(MATRIX_TYPE*)(calloc(cols, sizeof(MATRIX_TYPE)));

			if (newMatrix->data[iter] == NULL) {
				out.error = DATA_MEM_ALLOC_ERR;
			}
		}
	}

	if (out.error != SUCCESS)
		freeMatrix(&newMatrix);
	else
		out.matrix = newMatrix;

	return out;
}

void freeMatrix(Matrix** matrix) {
	if (*matrix != NULL) {
		if ((*matrix)->data != NULL) {
			for (size_t iter = 0; iter < (*matrix)->rowC; ++iter) {
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

void freeMatrixResult(MatrixResult* res) {
	if (res != NULL) {
		freeMatrix(&res->matrix);
		res->matrix = NULL;
		res->error	= SUCCESS;
	}
}

void fillMatrix(MatrixResult* A, const MATRIX_TYPE* data) {
	if (A->matrix == NULL || A->matrix->data == NULL)
		A->error = NULL_PTR_ERR;
	else
		for (size_t row = 0; row < A->matrix->rowC; row++)
			for (size_t col = 0; col < A->matrix->colC; col++)
				A->matrix->data[row][col] =
					data[row * A->matrix->colC + col];
}

MatrixResult createMinor(MatrixResult A, size_t excludeRowIndex,
						 size_t excludeColIndex) {
	MatrixResult out = {.matrix = NULL, .error = SUCCESS};

	if (A.matrix == NULL) {
		out.error = NULL_PTR_ERR;
	} else {
		out.error = canExclude(A.matrix->rowC, excludeRowIndex) ||
					canExclude(A.matrix->colC, excludeColIndex);
	}

	if (out.error == SUCCESS) {

		out = createMatrix(A.matrix->rowC - 1, A.matrix->colC - 1);

		MATRIX_TYPE newMatrixData[out.matrix->colC * out.matrix->rowC];
		size_t		insertionIndex = 0;

		for (size_t row = 0; row < A.matrix->rowC; row++)
			for (size_t col = 0; col < A.matrix->colC; col++)
				if (!(row == excludeRowIndex || col == excludeColIndex))
					newMatrixData[insertionIndex++] =
						A.matrix->data[row][col];

		fillMatrix(&out, newMatrixData);
	}

	return out;
}

MatrixResult getSumOrDiffMatrices(const MatrixResult A,
								  const MatrixResult B, bool getDiff) {
	MatrixResult out = {.matrix = NULL, .error = SUCCESS};

	if (A.matrix == NULL || B.matrix == NULL) {
		out.error = NULL_PTR_ERR;
	} else if (matrixSizesIsEqual(A.matrix, B.matrix) != SUCCESS) {
		out.error = DIMENSIONS_MISMATCH_ERR;
	} else {
		out = createMatrix(A.matrix->rowC, A.matrix->colC);
		if (out.error == SUCCESS) {
			for (size_t row = 0; row < A.matrix->rowC; row++) {
				for (size_t col = 0; col < A.matrix->colC; col++)
					(out.matrix)->data[row][col] =
						A.matrix->data[row][col] +
						(B.matrix->data[row][col] *
						 (1 - 2 * (int8_t)getDiff));
			}
		}
	}

	return out;
}

MatrixResult getMatrixCopy(const MatrixResult source) {
	MatrixResult out = {.matrix = NULL, .error = SUCCESS};

	if (source.matrix == NULL) {
		out.error = NULL_PTR_ERR;
	} else {
		out = createMatrix(source.matrix->rowC, source.matrix->colC);
		if (out.error == SUCCESS) {
			for (size_t row = 0; row < source.matrix->rowC; row++) {
				for (size_t col = 0; col < source.matrix->colC; col++) {
					out.matrix->data[row][col] =
						source.matrix->data[row][col];
				}
			}
		}
	}

	return out;
}

MatrixResult transposeMatrix(const MatrixResult A) {
	MatrixResult out = {.matrix = NULL, .error = SUCCESS};

	if (A.matrix == NULL) {
		out.error = NULL_PTR_ERR;
	} else {
		out = createMatrix(A.matrix->colC, A.matrix->rowC);
		if (out.error == SUCCESS) {
			for (size_t row = 0; row < A.matrix->rowC; row++) {
				for (size_t col = 0; col < A.matrix->colC; col++)
					out.matrix->data[col][row] = A.matrix->data[row][col];
			}
		}
	}

	return out;
}

DeterminantResult findDeterminant(const MatrixResult A) {
	DeterminantResult out = {.determinant = (DETERMINANT_TYPE)0,
							 .error		  = SUCCESS};

	if (A.matrix == NULL || A.matrix->data == NULL)
		out.error = NULL_PTR_ERR;
	else if (A.matrix->rowC != A.matrix->colC)
		out.error = IS_NOT_SQUARE_ERR;
	else if (A.error != SUCCESS)
		out.error = A.error;
	else {
		const MATRIX_TYPE** M = (const MATRIX_TYPE**)A.matrix->data;
		switch (A.matrix->rowC) {
			case 1:
				out.determinant = A.matrix->data[0][0];
				break;
			case 2:
				out.determinant = M[0][0] * M[1][1] - M[0][1] * M[1][0];
				break;
			case 3:
				out.determinant = M[0][0] * M[1][1] * M[2][2] +
								  M[0][1] * M[1][2] * M[2][0] +
								  M[0][2] * M[1][0] * M[2][1] -
								  M[0][2] * M[1][1] * M[2][0] -
								  M[0][0] * M[1][2] * M[2][1] -
								  M[0][1] * M[1][0] * M[2][2];
				break;
			default:
				for (size_t col = 0;
					 col < A.matrix->colC && out.error == SUCCESS; col++) {
					MatrixResult	  minorMatrix = createMinor(A, 0, col);
					int8_t			  sign		  = (col & 1) ? -1 : 1;
					DeterminantResult minorDet =
						findDeterminant(minorMatrix);
					if (minorDet.error != SUCCESS) {
						out.error = minorDet.error;
					} else {
						out.determinant += sign * minorDet.determinant;
					}
					freeMatrixResult(&minorMatrix);
				}
		}
	}

	return out;
}

MatrixResult multiplyMatrices(MatrixResult A, MatrixResult B) {
	MatrixResult out = {.matrix = NULL, .error = SUCCESS};

	if (A.matrix == NULL || B.matrix == NULL) {
		out.error = NULL_PTR_ERR;
	} else if (canMultiplyMatrices(A.matrix, B.matrix) != SUCCESS) {
		out.error = DIMENSIONS_MISMATCH_ERR;
	} else {
		out = createMatrix(A.matrix->rowC, B.matrix->colC);
		if (out.error == SUCCESS)
			for (size_t rowIndex = 0; rowIndex < A.matrix->rowC; rowIndex++)
				for (size_t colIndex = 0; colIndex < B.matrix->colC; colIndex++)
					for (size_t rIndex = 0; rIndex < A.matrix->colC; rIndex++)
						out.matrix->data[rowIndex][colIndex] += A.matrix->data[rowIndex][rIndex] * B.matrix->data[rIndex][colIndex];
	}

	return out;
}

void printMatrix(const MatrixResult res) {
	for (size_t row = 0; row < res.matrix->rowC; row++) {
		for (size_t col = 0; col < res.matrix->colC; col++)
			printf("%lf ", res.matrix->data[row][col]);
		printf("\n");
	}
}
