/**
 * @file config.h
 * @brief Основные настройки проекта
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @def DATA_DIR
 * @brief Директория для хранения тестовых файлов с матрицами
 */
#define DATA_DIR "data/"

/**
 * @def INPUT_FILE_DIR
 * @brief Директория для входных файлов с матрицами
 */
#define INPUT_FILE_DIR DATA_DIR "input/"

/**
 * @def OUTPUT_FILE_DIR
 * @brief Директория для выходных файлов с результатами
 */
#define OUTPUT_FILE_DIR DATA_DIR "output/"

/**
 * @def BUFFER_SIZE
 * @brief Размер буфера для чтения/записи файлов (в байтах)
 * @warning Может работать некорректно при слишком маленьких значениях
 */
#define BUFFER_SIZE 1024

/**
 * @def MATRIX_T_SPEC
 * @brief Спецификатор формата для элементов матрицы
 * @note Необходимо менять только вместе с MATRIX_TYPE
 */
#define MATRIX_T_SPEC "%lf"

/**
 * @def DETERMINANT_T_SPEC
 * @brief Спецификатор формата для значений определителя
 * @note Необходимо менять только вместе с DETERMINANT_TYPE
 */
#define DETERMINANT_T_SPEC "%Lf"

/**
 * @typedef MATRIX_TYPE
 * @brief Основной тип данных для элементов матрицы
 * @note Изменение типа требует обновления MATRIX_T_SPEC
 * @see MATRIX_T_SPEC
 */
typedef double MATRIX_TYPE;

/**
 * @typedef DETERMINANT_TYPE
 * @brief Тип данных для вычисления определителя
 * @note Должен иметь большую точность чем MATRIX_TYPE
 * @note Изменение типа требует обновления DETERMINANT_T_SPEC
 * @see DETERMINANT_T_SPEC
 */
typedef long double DETERMINANT_TYPE;

#endif
