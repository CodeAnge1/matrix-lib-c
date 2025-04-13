/**
 * @file
 */

#ifndef MATRIX_H
#define MATRIX_H
#define _GNU_SOURCE

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/config.h"

/**
 * @struct Matrix
 * @brief Структура матрицы
 */
typedef struct {
  size_t		rowC;  ///< Количество строк.
  size_t		colC;  ///< Количество столбцов.
  MATRIX_TYPE** data;  ///< Двумерный массив данных.
} Matrix;

#include "../errors/errors.h"

/**
 * @struct MatrixResult
 * @brief Структура, реализующая хранение ошибок выполнения и самой матрицы
 */
typedef struct {
  Matrix*		  matrix;  ///< Указатель на структуру Matrix
  MatrixErrorCode error;   ///< Сохраняемый код ошибки
} MatrixResult;

#include "../output/output.h"

/**
 * @struct DeterminantResult
 * @brief Структура, реализующая хранение ошибок выполнения и определителя
 * матрицы
 */
typedef struct {
  DETERMINANT_TYPE determinant;	 ///< Хранимое значение определителя
  MatrixErrorCode  error;		 ///< Сохраняемый код ошибки
} DeterminantResult;

/**
 * @brief Создает новую матрицу с заданными размерами
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult createMatrix(const size_t rows, const size_t cols);

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param matrix Указатель на указатель на матрицу (Matrix**)
 */
void freeMatrix(Matrix** matrix);

/**
 * @brief Освобождает ресурсы структуры MatrixResult
 * @param res Указатель на структуру MatrixResult
 * @note Безопасно обрабатывает NULL указатели
 */
void freeMatrixResult(MatrixResult* res);

/**
 * @brief Заполняет матрицу данными из массива
 * @param A Указатель на структуру MatrixResult
 * @param data Указатель на массив данных
 * @note Размер массива должен соответствовать размерам матрицы
 */
void fillMatrix(MatrixResult* A, const MATRIX_TYPE* data);

/**
 * @brief Загружает матрицу из файла
 * @param filename Имя файла для загрузки
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult loadMatrixFromFile(const char* filename);

/**
 * @brief Создает минор матрицы
 * @param A Исходная матрица
 * @param excludeRowIndex Индекс исключаемой строки
 * @param excludeColIndex Индекс исключаемого столбца
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult createMinor(const MatrixResult A,
						 const size_t		excludeRowIndex,
						 const size_t		excludeColIndex);

/**
 * @brief Вычисляет сумму или разность матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @param getDiff Флаг вычисления разности (true - разность, false - сумма)
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult getSumOrDiffMatrices(const MatrixResult A,
								  const MatrixResult B, bool getDiff);

/**
 * @brief Создает копию матрицы
 * @param source Исходная матрица для копирования
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult getMatrixCopy(const MatrixResult source);

/**
 * @brief Транспонирует матрицу
 * @param A Исходная матрица
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult transposeMatrix(const MatrixResult A);

/**
 * @brief Вычисляет определитель матрицы
 * @param A Исходная матрица
 * @return Структура DeterminantResult
 * @note Для неквадратных матриц возвращает ошибку
 */
DeterminantResult findDeterminant(const MatrixResult A);

/**
 * @brief Умножает матрицы
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return Структура MatrixResult
 * @note Если возвращаемая ошибка не "SUCCESS", то поле matrix будет NULL
 */
MatrixResult multiplyMatrices(const MatrixResult A, const MatrixResult B);

/**
 * @brief Конвертирует матрицу в строковое представление
 * @param A Исходная матрица
 * @return Указатель на строку с представлением матрицы
 * @note Служебная функция, используется только для вывода в модуле output/
 */
char* convertMatrixToBuffer(const MatrixResult A);

#endif	// MATRIX_H
