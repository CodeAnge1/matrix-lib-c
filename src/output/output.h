/**
 * @file output.h
 * @brief Предоставляет функции для вывода матриц
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"

/**
 * @brief Выводит матрицу в стандартный вывод
 * @param A Матрица для вывода
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode outputToStdOut(const MatrixResult A);

/**
 * @brief Выводит матрицу в файл
 * @param A Матрица для вывода
 * @param filename Имя файла
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode outputToFile(const MatrixResult A, const char* filename);

#endif