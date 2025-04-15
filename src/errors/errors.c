#include "errors.h"

static Language currentLang = DEFAULT_LANGUAGE;

static const ErrorMessage errorMessages[] = {
	{SUCCESS, "Operation completed successfully",
	 "Операция завершилась успешно"},
	{NULL_PTR_ERR, "NULL pointer to matrix passed",
	 "Передан NULL указатель на матрицу"},
	{STRUCT_MEM_ALLOC_ERR, "Failed to allocate memory for structure",
	 "Не удалось выделить память для структуры"},
	{DATA_MEM_ALLOC_ERR, "Failed to allocate memory for data",
	 "Не удалось выделить память для данных структуры"},
	{INVALID_SIZE_ERR, "Invalid matrix size",
	 "Некорректный размер матрицы"},
	{DIMENSIONS_MISMATCH_ERR, "Matrix dimensions don't match",
	 "Размеры матриц не совпадают"},
	{IS_NOT_SQUARE_ERR, "Matrix is not square",
	 "Матрица не является квадратной"},
	{CANNOT_EXCLUDE_ROW_COL, "Cannot exclude row/column from matrix",
	 "Не удалось удалить ряд или колонку из матрицы"},
	{CANNOT_MULTIPLY_MATRICES, "Cannot multiply matrices",
	 "Невозможно умножить матрицы"},
	{FILE_WRITE_ERR, "Failed to open file for writing",
	 "Не удалось открыть файл на запись"},
	{FILE_READ_ERR, "Failed to read matrix from file",
	 "Не удалось считать матрицу из файла"},
	{EMPTY_FILE_ERR, "Provided file is empty", "Переданный файл пуст"},
	{INVALID_INPUT_DATA_ERR, "Input data format is invalid",
	 "Входной формат данных некорректен"},
	{NOT_ENOUGH_VALUES_ERR, "Not enough values in provided file",
	 "В переданном файле недостаточно значений"},
	{TOO_MANY_VALUES_ERR, "Too many values in provided file",
	 "В переданном файле слишком много значений"},
	{LINE_TOO_LONG_ERR, "Buffer size is too small",
	 "Размер буфера слишком мал"},
	{FAILED_CONVERT_TO_BUFFER, "Failed to convert matrix to buffer string",
	 "Ошибка конвертации матрицы в буферную строку"},
	{ERROR_COUNT, "Unknown error", "Получена неизвестная ошибка"}};

void setLanguage(Language newLang) {
  currentLang = (LANG_EN <= newLang && newLang < LANG_COUNT)
					? newLang
					: DEFAULT_LANGUAGE;
}

const char* getErrorMessage(const MatrixErrorCode errCode) {
  const char* message;

  if (errCode < 0 || errCode > ERROR_COUNT)
	message = (currentLang == LANG_EN) ? "Incorrect error code"
									   : "Неверный код ошибки";

  if (errorMessages[errCode].errorCode == errCode)
	message = (currentLang == LANG_EN) ? errorMessages[errCode].msgEn
									   : errorMessages[errCode].msgRu;

  return message;
}

MatrixErrorCode checkMatrixSize(const size_t rows, const size_t cols) {
  return (rows == 0 || cols == 0) ? INVALID_SIZE_ERR : SUCCESS;
}

MatrixErrorCode matrixSizesIsEqual(const Matrix* A, const Matrix* B) {
  return (A->colC == B->colC && A->rowC == B->rowC)
			 ? SUCCESS
			 : DIMENSIONS_MISMATCH_ERR;
}

MatrixErrorCode canExclude(const size_t count, const size_t currentIndex) {
  return (count > currentIndex) ? SUCCESS : CANNOT_EXCLUDE_ROW_COL;
}

MatrixErrorCode canMultiplyMatrices(const Matrix* A, const Matrix* B) {
  return (A->colC == B->rowC) ? SUCCESS : DIMENSIONS_MISMATCH_ERR;
}

MatrixErrorCode checkVariableCount(const Matrix* A, const size_t count) {
  const size_t matrixSize = A->rowC * A->colC;

  return (matrixSize == count)	? SUCCESS
		 : (matrixSize > count) ? TOO_MANY_VALUES_ERR
								: NOT_ENOUGH_VALUES_ERR;
}
