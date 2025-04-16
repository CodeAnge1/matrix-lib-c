/**
 * @file tests_matrix.c
 * @brief Модуль реализации тестов для matrix.c
 */
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/matrix/matrix.h"

void test_matrix_creation(void) {
  {
	MatrixResult matr = createMatrix(2, 3);
	CU_ASSERT_PTR_NOT_NULL(matr.matrix);
	CU_ASSERT_PTR_NOT_NULL(matr.matrix->data);
	CU_ASSERT_EQUAL(matr.matrix->rowC, 2);
	CU_ASSERT_EQUAL(matr.matrix->colC, 3);
	CU_ASSERT_EQUAL(matr.error, SUCCESS);
	freeMatrixResult(&matr);
  }

  {
	MatrixResult invalid = createMatrix(-1, 0);
	CU_ASSERT_PTR_NULL(invalid.matrix);
	CU_ASSERT_NOT_EQUAL(invalid.error, SUCCESS);
	freeMatrixResult(&invalid);
  }
}

void test_matrix_addition(void) {
  {
	MatrixResult A = createMatrix(2, 2);
	MatrixResult B = createMatrix(2, 2);

	for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 2; j++) {
		A.matrix->data[i][j] = i + j;		 // A = [[0, 1], [1, 2]]
		B.matrix->data[i][j] = (i + j) * 2;	 // B = [[0, 2], [2, 4]]
	  }
	}

	MatrixResult result = getSumOrDiffMatrices(A, B, 0);

	CU_ASSERT_EQUAL(result.error, SUCCESS);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[0][0], 0.0, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[1][1], 6.0, 0.001);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }

  {
	MatrixResult A		= createMatrix(3, 2);
	MatrixResult B		= createMatrix(1, 1);
	MatrixResult result = getSumOrDiffMatrices(A, B, 0);

	CU_ASSERT_NOT_EQUAL(result.error, SUCCESS);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }
}

void test_matrix_subtraction(void) {
  {
	MatrixResult A = createMatrix(2, 2);
	MatrixResult B = createMatrix(2, 2);

	for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 2; j++) {
		A.matrix->data[i][j] = i + j;		 // A = [[0, 1], [1, 2]]
		B.matrix->data[i][j] = (i + j) * 2;	 // B = [[0, 2], [2, 4]]
	  }
	}

	MatrixResult result = getSumOrDiffMatrices(A, B, true);

	CU_ASSERT_EQUAL(result.error, SUCCESS);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[0][0], 0.0, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[1][1], -2.0, 0.001);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }

  {
	MatrixResult A		= createMatrix(2, 3);
	MatrixResult B		= createMatrix(2, 2);
	MatrixResult result = getSumOrDiffMatrices(A, B, true);

	CU_ASSERT_NOT_EQUAL(result.error, SUCCESS);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }
}

void test_matrix_multiplication(void) {
  {
	MatrixResult A = createMatrix(2, 3);
	MatrixResult B = createMatrix(3, 2);

	for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 3; j++) {
		A.matrix->data[i][j] = i + j;  // A = [[0, 1, 2], [1, 2, 3]]
	  }
	}

	for (int i = 0; i < 3; i++) {
	  for (int j = 0; j < 2; j++) {
		B.matrix->data[i][j] = i * j;  // B = [[0, 0], [0, 1], [0, 2]]
	  }
	}

	MatrixResult result =
		multiplyMatrices(A, B);	 // result = [[0, 5], [0, 8]]

	CU_ASSERT_EQUAL(result.error, SUCCESS);
	CU_ASSERT_EQUAL(result.matrix->rowC, 2);
	CU_ASSERT_EQUAL(result.matrix->colC, 2);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[0][0], 0.0, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(result.matrix->data[1][1], 8.0, 0.001);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }

  {
	MatrixResult A		= createMatrix(2, 2);
	MatrixResult B		= createMatrix(3, 3);
	MatrixResult result = multiplyMatrices(A, B);

	CU_ASSERT_NOT_EQUAL(result.error, SUCCESS);

	freeMatrixResult(&A);
	freeMatrixResult(&B);
	freeMatrixResult(&result);
  }
}

void test_matrix_transpose(void) {
  {
	MatrixResult m = createMatrix(2, 3);

	for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 3; j++) {
		m.matrix->data[i][j] = i * 3 + j;  // m = [[0, 1, 2], [3, 4, 5]]
	  }
	}

	MatrixResult transposed = transposeMatrix(m);

	CU_ASSERT_EQUAL(transposed.error, SUCCESS);
	CU_ASSERT_EQUAL(transposed.matrix->rowC, 3);
	CU_ASSERT_EQUAL(transposed.matrix->colC, 2);
	CU_ASSERT_DOUBLE_EQUAL(transposed.matrix->data[0][0], 0.0, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(transposed.matrix->data[1][1], 4.0, 0.001);

	freeMatrixResult(&m);
	freeMatrixResult(&transposed);
  }
}

void test_determinant(void) {
  {
	MatrixResult m		 = createMatrix(2, 2);
	m.matrix->data[0][0] = 1.0;
	m.matrix->data[0][1] = 2.0;
	m.matrix->data[1][0] = 3.0;
	m.matrix->data[1][1] = 4.0;

	DeterminantResult det = findDeterminant(m);
	CU_ASSERT_EQUAL(det.error, SUCCESS);
	CU_ASSERT_DOUBLE_EQUAL(det.determinant, -2.0, 0.001);

	freeMatrixResult(&m);
  }

  {
	MatrixResult	  nonSquare = createMatrix(2, 3);
	DeterminantResult det		= findDeterminant(nonSquare);
	CU_ASSERT_NOT_EQUAL(det.error, SUCCESS);

	freeMatrixResult(&nonSquare);
  }
}

void test_null_safety(void) {
  MatrixResult nullResult = {NULL, NULL_PTR_ERR};

  {
	MatrixResult result = multiplyMatrices(nullResult, nullResult);
	CU_ASSERT_EQUAL(result.error, NULL_PTR_ERR);
	freeMatrixResult(&result);
  }

  {
	MatrixResult result = transposeMatrix(nullResult);
	CU_ASSERT_EQUAL(result.error, NULL_PTR_ERR);
	freeMatrixResult(&result);
  }

  {
	DeterminantResult det = findDeterminant(nullResult);
	CU_ASSERT_EQUAL(det.error, NULL_PTR_ERR);
  }

  {
	MatrixResult valid	= createMatrix(1, 1);
	MatrixResult result = multiplyMatrices(valid, nullResult);
	CU_ASSERT_EQUAL(result.error, NULL_PTR_ERR);
	freeMatrixResult(&valid);
	freeMatrixResult(&result);
  }
}

void test_file_operations(void) {
  const char* filename = "test_matrix.txt";

  FILE* f = fopen(filename, "w");
  fprintf(f, "2 2\n1.0 2.0\n3.0 4.0");
  fclose(f);

  MatrixResult loaded = loadMatrixFromFile(filename);
  CU_ASSERT_PTR_NOT_NULL(loaded.matrix);
  CU_ASSERT_PTR_NOT_NULL(loaded.matrix->data);

  CU_ASSERT_EQUAL(loaded.matrix->rowC, 2);
  CU_ASSERT_EQUAL(loaded.matrix->colC, 2);

  CU_ASSERT_DOUBLE_EQUAL(loaded.matrix->data[0][0], 1.0, 0.001);
  CU_ASSERT_DOUBLE_EQUAL(loaded.matrix->data[1][1], 4.0, 0.001);

  freeMatrixResult(&loaded);
  remove(filename);
}

void test_file_errors(void) {
  {
	MatrixResult loaded = loadMatrixFromFile("nonexistent.txt");
	CU_ASSERT_EQUAL(loaded.error, FILE_READ_ERR);
	CU_ASSERT_PTR_NULL(loaded.matrix);
  }
  {
	FILE* f = fopen("bad_matrix.txt", "w");
	fprintf(f, "2 a\n1 2\n3 4");
	fclose(f);

	MatrixResult loaded = loadMatrixFromFile("bad_matrix.txt");
	CU_ASSERT_PTR_NULL(loaded.matrix);
	remove("bad_matrix.txt");
  }
}

void register_matrix_tests(void) {
  CU_pSuite suite = CU_add_suite("Matrix Tests", NULL, NULL);
  CU_add_test(suite, "Matrix Creation", test_matrix_creation);
  CU_add_test(suite, "Matrix Addition", test_matrix_addition);
  CU_add_test(suite, "Matrix Subtraction", test_matrix_subtraction);
  CU_add_test(suite, "Matrix Multiplication", test_matrix_multiplication);
  CU_add_test(suite, "Matrix Transpose", test_matrix_transpose);
  CU_add_test(suite, "Matrix Determinant", test_determinant);
  CU_add_test(suite, "NULL Safety", test_null_safety);
  CU_add_test(suite, "File Operations", test_file_operations);
  CU_add_test(suite, "File Errors", test_file_errors);
}
