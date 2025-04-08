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
		case DIMENSIONS_MISMATCH:
			message = "Размеры матриц не совпадают";
			break;
		case IS_NOT_SQUARE_ERR:
			message = "Матрица не является квадратной";
			break;
		case CANNOT_EXCLUDE_ROW_COL:
			message = "Не удалось удалить ряд или колонку из матрицы";
			break;
		case FILE_READ_ERR:
			message = "Не удалось считать матрицу из файла";
			break;
		default:
			message = "Получена неизвестная ошибка";
			break;
	}

	return message;
}

MatrixErrorCode checkMatrixSize(const size_t rows, const size_t cols) {
	MatrixErrorCode errCode = SUCCESS;

	if (rows == 0 || cols == 0) {
		errCode = INVALID_SIZE_ERR;
	}

	return errCode;
}

MatrixErrorCode compareMatrixSizes(const Matrix* A, const Matrix* B) {
	MatrixErrorCode result = SUCCESS;

	if (A->colC != B->colC || A->rowC != B->rowC) {
		result = DIMENSIONS_MISMATCH;
	}
	return result;
}

MatrixErrorCode canExclude(const size_t count, const size_t currentIndex) {
	return count > currentIndex ? SUCCESS : CANNOT_EXCLUDE_ROW_COL;
}
