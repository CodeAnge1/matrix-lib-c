/**
 * @file tests_runner.c
 * @brief Модуль запуска всех тестов
 */

#include <CUnit/Basic.h>
#include <stdio.h>

// Объявления тестовых функций
void register_matrix_tests(void);
void register_main_tests(void);

// Основная функция
int main(void) {
  // Инициализация реестра тестов
  if (CU_initialize_registry() != CUE_SUCCESS) {
	return CU_get_error();	// Возвращаем ошибку, если не удалось
							// инициализировать реестр
  }

  // Регистрация всех тестов
  register_matrix_tests();	// Регистрация тестов для matrix
  register_main_tests();	// Регистрация тестов для main

  // Установка режима вывода
  CU_basic_set_mode(CU_BRM_VERBOSE);  // Подробный режим вывода

  // Запуск тестов
  CU_basic_run_tests();

  // Очистка реестра после выполнения тестов
  CU_cleanup_registry();

  return CU_get_error();  // Возвращаем ошибку, если тесты завершились с
						  // ошибкой
}
