#include "../include/config.h"
#include "matrix/matrix.h"

int main() {
  MatrixResult A = loadMatrixFromFile(INPUT_FILE_DIR "matrix_a.txt");
  MatrixResult B = loadMatrixFromFile(INPUT_FILE_DIR "matrix_b.txt");
  MatrixResult C = loadMatrixFromFile(INPUT_FILE_DIR "matrix_c.txt");
  MatrixResult D = loadMatrixFromFile(INPUT_FILE_DIR "matrix_d.txt");

  MatrixResult result	   = getSumOrDiffMatrices(A, B, 0);
  MatrixResult transposedC = transposeMatrix(C);
  result				   = multiplyMatrices(result, transposedC);
  result				   = getSumOrDiffMatrices(result, D, 1);

  MatrixErrorCode fileErr =
	  outputToFile(result, OUTPUT_FILE_DIR "result.txt");

  MatrixErrorCode resultError =
	  (fileErr == SUCCESS) ? result.error : fileErr;

  freeMatrixResult(&A);
  freeMatrixResult(&B);
  freeMatrixResult(&C);
  freeMatrixResult(&D);
  freeMatrixResult(&result);
  freeMatrixResult(&transposedC);

  return (resultError == SUCCESS) ? 0 : 1;
}
