/**
 * @file errors.h
 * @brief Предоставляет функции для обработки ошибок
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

/**
 * @enum MatrixErrorCode
 * @brief Коды ошибок для операций с матрицами
 */
typedef enum {
  SUCCESS = 0,				 ///< Операция выполнена успешно
  NULL_PTR_ERR,				 ///< Передан нулевой указатель
  STRUCT_MEM_ALLOC_ERR,		 ///< Ошибка выделения памяти для структуры
  DATA_MEM_ALLOC_ERR,		 ///< Ошибка выделения памяти для данных
  INVALID_SIZE_ERR,			 ///< Некорректный размер матрицы
  DIMENSIONS_MISMATCH_ERR,	 ///< Несовпадение размеров матриц
  IS_NOT_SQUARE_ERR,		 ///< Матрица не квадратная
  CANNOT_EXCLUDE_ROW_COL,	 ///< Невозможно исключить строку/столбец
  CANNOT_MULTIPLY_MATRICES,	 ///< Невозможно умножить матрицы
  FILE_WRITE_ERR,			 ///< Ошибка записи в файл
  FILE_READ_ERR,			 ///< Ошибка чтения файла
  EMPTY_FILE_ERR,			 ///< Файл пуст
  INVALID_INPUT_DATA_ERR,	 ///< Некорректные входные данные
  NOT_ENOUGH_VALUES_ERR,	 ///< Недостаточно значений в файле
  TOO_MANY_VALUES_ERR,		 ///< Слишком много значений в файле
  LINE_TOO_LONG_ERR,		 ///< Слишком длинная строка в файле
  FAILED_CONVERT_TO_BUFFER,	 ///< Ошибка конвертации матрицы в буферную
							 ///< строку
  ERROR_COUNT				 ///< Количество типов ошибок (служебное)
} MatrixErrorCode;

#include "../matrix/matrix.h"
#include "messages.h"

/**
 * @brief Меняет текущий язык для вывода ошибок
 * @param newLang Код языка (Language)
 */
void setLanguage(Language newLang);

/**
 * @brief Возвращает текстовое описание ошибки
 * @param errCode Код ошибки MatrixErrorCode
 * @return Строка с описанием ошибки
 */
const char* getErrorMessage(const MatrixErrorCode errCode);

/**
 * @brief Проверяет корректность размеров матрицы
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode checkMatrixSize(const size_t rows, const size_t cols);

/**
 * @brief Проверяет совпадение размеров матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode matrixSizesIsEqual(const Matrix* A, const Matrix* B);

/**
 * @brief Проверяет возможность исключения строки/столбца
 * @param count Общее количество строк/столбцов
 * @param currentIndex Индекс для исключения
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode canExclude(const size_t count, const size_t currentIndex);

/**
 * @brief Проверяет возможность умножения матриц
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode canMultiplyMatrices(const Matrix* A, const Matrix* B);

/**
 * @brief Проверяет количество переменных для заполнения матрицы
 * @param A Матрица
 * @param count Количество переменных
 * @return Код ошибки MatrixErrorCode
 */
MatrixErrorCode checkVariableCount(const Matrix* A, const size_t count);

#endif