#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"

MatrixErrorCode outputToStdOut(const MatrixResult A);

MatrixErrorCode outputToFile(const MatrixResult A, const char* filename);

#endif