#include "errors.h"

// TODO: Multi-language support
const char *getErrorMessage(const MatrixErrorCode errCode) {
    const char* message;

    if (errCode < 0 || errCode > MATRIX_ERROR_COUNT) {
        message = "Неверный код ошибки";
        return message;
    }

    switch (errCode) {
        case MATRIX_SUCCESS:
            message = "Операция завершилась успешно";
            break;
        case MATRIX_NULL_PTR_ERR:
            message = "Передан NULL указатель на матрицу";
            break;
        case MATRIX_STRUCT_MEM_ALLOC_ERR:
            message = "Не удалось выделить память для структуры";
            break;
        case MATRIX_DATA_MEM_ALLOC_ERR:
            message = "Не удалось выделить память для данных стуркуты";
            break;
        case MATRIX_INVALID_SIZE_ERR:
            message = "Некорректный размер матрицы";
            break;
        case MATRIX_DIMENSIONS_MISMATCH:
            message = "Размеры матриц не совпадают";
            break;
        case MATRIX_IS_NOT_SQUARE_ERR:
            message = "Матрица не является квадратной";
            break;
        case MATRIX_FILE_READ_ERR:
            message = "Не удалось считать матрицу из файла";
            break;
        default:
            message = "Получена неизвестная ошибка";
            break;
    }

    return message;
}

MatrixErrorCode checkMatrixSize(size_t rows, size_t cols) {
    MatrixErrorCode errCode = MATRIX_SUCCESS;

    if (rows == 0 || cols == 0) {
        errCode = MATRIX_INVALID_SIZE_ERR;
    }

    return errCode;
}
