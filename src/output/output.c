#include "output.h"

MatrixErrorCode outputToStdOut(const MatrixResult A) {
	MatrixErrorCode res = (A.matrix == NULL || A.matrix->data == NULL)
							  ? NULL_PTR_ERR
							  : SUCCESS;
	if (res == SUCCESS) {
		char* buffer = convertMatrixToBuffer(A);
		if (buffer)
			puts(buffer);
		else
			res = FAILED_CONVERT_TO_BUFFER;
	}

	return res;
}

MatrixErrorCode outputToFile(const MatrixResult A, const char* filename) {
	MatrixErrorCode res = (A.matrix == NULL || A.matrix->data == NULL)
							  ? NULL_PTR_ERR
							  : SUCCESS;
	if (res == SUCCESS) {
		char* buffer = convertMatrixToBuffer(A);
		if (buffer) {
			FILE* file = NULL;
			file	   = fopen(filename, "w");
			if (file == NULL)
				res = FILE_WRITE_ERR;
			else
				fprintf(file, "%s", buffer);
		} else
			res = FAILED_CONVERT_TO_BUFFER;
	}

	return res;
}
