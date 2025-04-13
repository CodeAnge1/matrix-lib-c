#include "errors.h"

// TODO: Multi-language support
const char* getErrorMessage(const MatrixErrorCode errCode) {
  const char* message;

  if (errCode < 0 || errCode > ERROR_COUNT) {
	message = "Неверный код ошибки";
	return message;
  }

  switch (errCode) {
	case SUCCESS:
	  message = "Операция завершилась успешно";
	  break;
	case NULL_PTR_ERR:
	  message = "Передан NULL указатель на матрицу";
	  break;
	case STRUCT_MEM_ALLOC_ERR:
	  message = "Не удалось выделить память для структуры";
	  break;
	case DATA_MEM_ALLOC_ERR:
	  message = "Не удалось выделить память для данных стуркуты";
	  break;
	case INVALID_SIZE_ERR:
	  message = "Некорректный размер матрицы";
	  break;
	case DIMENSIONS_MISMATCH_ERR:
	  message = "Размеры матриц не совпадают";
	  break;
	case IS_NOT_SQUARE_ERR:
	  message = "Матрица не является квадратной";
	  break;
	case CANNOT_EXCLUDE_ROW_COL:
	  message = "Не удалось удалить ряд или колонку из матрицы";
	  break;
	case CANNOT_MULTIPLY_MATRICES:
	  message = "Невозможно умножить матрицы";
	  break;
	case FILE_WRITE_ERR:
	  message = "Не удалось открыть файл на запись";
	  break;
	case FILE_READ_ERR:
	  message = "Не удалось считать матрицу из файла";
	  break;
	case EMPTY_FILE_ERR:
	  message = "Переданный файл пуст";
	  break;
	case INVALID_INPUT_DATA_ERR:
	  message = "Входной формат данных некорректен";
	  break;
	case NOT_ENOUGH_VALUES_ERR:
	  message = "В переданном файле недостаточно значений";
	  break;
	case TOO_MANY_VALUES_ERR:
	  message = "В переданном файле слишком много значений";
	  break;
	case LINE_TOO_LONG_ERR:
	  message = "Размер буфера слишком мал";
	  break;
	case FAILED_CONVERT_TO_BUFFER:
	  message = "";
	  break;
	default:
	  message = "Получена неизвестная ошибка";
	  break;
  }

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
