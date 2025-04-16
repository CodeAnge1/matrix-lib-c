/**
 * @file tests_main.c
 * @brief Тесты для основного модуля приложения
 */

#include <CUnit/CUnit.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/config.h"
#include "../src/matrix/matrix.h"
#include "../src/output/output.h"

#define APP_NAME "./bin/MatrixLib"

/**
 * @brief Вспомогательная функция для создания текстового файла матрицы
 * @param filename Имя файла
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param data Указатель на массив значений
 */
void createTestMatrixFile(const char* filename, int rows, int cols,
						  double* data) {
  mkdir(DATA_DIR, 0755);
  mkdir(INPUT_FILE_DIR, 0755);
  mkdir(OUTPUT_FILE_DIR, 0755);
  FILE* f = fopen(filename, "w");
  if (f) {
	fprintf(f, "%d %d\n", rows, cols);
	for (int i = 0; i < rows; i++) {
	  for (int j = 0; j < cols; j++) {
		fprintf(f, MATRIX_T_SPEC " ", data[i * cols + j]);
	  }
	  fprintf(f, "\n");
	}
	fclose(f);
  }
}

/**
 * @brief Тест успешного выполнения программы и корректности вычислений
 */
void test_main_success(void) {
  double a_data[4] = {1.0, 2.0, 3.0, 4.0};	// 2x2
  double b_data[4] = {5.0, 6.0, 7.0, 8.0};	// 2x2
  double c_data[4] = {0.5, 0.5, 0.5, 0.5};	// 2x2
  double d_data[4] = {0.1, 0.1, 0.1, 0.1};	// 2x2

  createTestMatrixFile(INPUT_FILE_DIR "matrix_a.txt", 2, 2, a_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_b.txt", 2, 2, b_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_c.txt", 2, 2, c_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_d.txt", 2, 2, d_data);

  int result = system(APP_NAME);
  CU_ASSERT_EQUAL(result, 0);

  FILE* f = fopen(OUTPUT_FILE_DIR "result.txt", "r");
  CU_ASSERT_PTR_NOT_NULL(f);

  if (f) {
	double val1, val2, val3, val4;
	fscanf(f, "%lf %lf", &val1, &val2);
	fscanf(f, "%lf %lf", &val3, &val4);

	// Проверка выражения: (A+B)×C^T−D
	CU_ASSERT_DOUBLE_EQUAL(val1, 6.9, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(val2, 6.9, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(val3, 10.9, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(val4, 10.9, 0.001);

	fclose(f);
  }

  remove(INPUT_FILE_DIR "matrix_a.txt");
  remove(INPUT_FILE_DIR "matrix_b.txt");
  remove(INPUT_FILE_DIR "matrix_c.txt");
  remove(INPUT_FILE_DIR "matrix_d.txt");
  remove(OUTPUT_FILE_DIR "result.txt");
}

/**
 * @brief Тест обработки ошибок при отсутствии входных файлов
 */
void test_main_file_errors(void) {
  double a_data[4] = {1, 2, 3, 4};
  createTestMatrixFile(INPUT_FILE_DIR "matrix_a.txt", 2, 2, a_data);

  int result = system(APP_NAME);
  CU_ASSERT_NOT_EQUAL(result, 0);

  remove(INPUT_FILE_DIR "matrix_a.txt");
}

/**
 * @brief Тест обработки ошибки при несовместимых размерах матриц
 */
void test_main_dimension_errors(void) {
  double a_data[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};   // 2x3
  double b_data[6] = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0};  // 3x2
  double c_data[4] = {0.5, 0.5, 0.5, 0.5};			   // 2x2
  double d_data[4] = {0.1, 0.1, 0.1, 0.1};			   // 2x2

  createTestMatrixFile(INPUT_FILE_DIR "matrix_a.txt", 2, 3, a_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_b.txt", 3, 2, b_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_c.txt", 2, 2, c_data);
  createTestMatrixFile(INPUT_FILE_DIR "matrix_d.txt", 2, 2, d_data);

  int result = system(APP_NAME);
  CU_ASSERT_NOT_EQUAL(result, 0);

  remove(INPUT_FILE_DIR "matrix_a.txt");
  remove(INPUT_FILE_DIR "matrix_b.txt");
  remove(INPUT_FILE_DIR "matrix_c.txt");
  remove(INPUT_FILE_DIR "matrix_d.txt");
}

/**
 * @brief Тест ошибки сохранения результата (например, если отсутствует
 * директория)
 */
void test_main_save_error(void) {
  rmdir(INPUT_FILE_DIR);
  int result = system(APP_NAME);
  CU_ASSERT_NOT_EQUAL(result, 0);
}

/**
 * @brief Регистрация всех тестов основного модуля
 */
void register_main_tests(void) {
  CU_pSuite suite = CU_add_suite("Main Module Tests", NULL, NULL);
  CU_add_test(suite, "Test Main Success", test_main_success);
  CU_add_test(suite, "Test File Errors", test_main_file_errors);
  CU_add_test(suite, "Test Dimension Errors", test_main_dimension_errors);
  CU_add_test(suite, "Test Save Error", test_main_save_error);
}