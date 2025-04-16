#include "output.h"

#include <sys/stat.h>
#include <sys/types.h>

void createDir() {
  mkdir(DATA_DIR, 0755);
  mkdir(INPUT_FILE_DIR, 0755);
  mkdir(OUTPUT_FILE_DIR, 0755);
}

MatrixErrorCode outputToStdOut(const MatrixResult A) {
  createDir();
  MatrixErrorCode res = (A.matrix == NULL || A.matrix->data == NULL)
							? NULL_PTR_ERR
							: SUCCESS;
  if (res == SUCCESS) {
	char* buffer = convertMatrixToBuffer(A);
	if (buffer)
	  puts(buffer);
	else
	  res = FAILED_CONVERT_TO_BUFFER;
	free(buffer);
  }

  return res;
}

MatrixErrorCode outputToFile(const MatrixResult A, const char* filename) {
  createDir();
  MatrixErrorCode res = (A.matrix == NULL || A.matrix->data == NULL)
							? NULL_PTR_ERR
							: SUCCESS;
  if (res == SUCCESS) {
	char* buffer = convertMatrixToBuffer(A);
	if (buffer) {
	  FILE* file = NULL;
	  file		 = fopen(filename, "w");
	  if (file == NULL)
		res = FILE_WRITE_ERR;
	  else
		fprintf(file, "%s", buffer);
	} else
	  res = FAILED_CONVERT_TO_BUFFER;
	free(buffer);
  }

  return res;
}
