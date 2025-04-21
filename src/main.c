#include "../include/config.h"
#include "matrix/matrix.h"

int main() {
  MatrixResult A = loadMatrixFromFile(INPUT_FILE_DIR "A.txt");
  MatrixResult B = loadMatrixFromFile(INPUT_FILE_DIR "B.txt");
  MatrixResult C = loadMatrixFromFile(INPUT_FILE_DIR "C.txt");
  MatrixResult D = loadMatrixFromFile(INPUT_FILE_DIR "D.txt");

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
