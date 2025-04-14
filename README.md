# Лабораторная работа №II.2. Разработка библиотеки для операций над матрицами

## Оглавление

- [Вступление](#описание-проекта)
	- [Цель проекта](#цель-работы)
	- [Задачи проекта](#основные-задачи)
	- [Структура проекта](#структура-проекта)
- [Реализация](#реализация)
	- [Особенности реализации](#особенности-реализации)
- [Список доступных функций](#функции-реализованные-в-библиотеке)
- [Сборка и запуск](#сборка-и-запуск-проекта)
- [Тестирование](#тестирование)
- [Вывод](#вывод)


## Описание проекта

Данный проект представляет собой библиотеку для работы с матрицами, реализующую базовые и расширенные операции: создание, освобождение, транспонирование, нахождение минора и определителя, арифметические операции и вывод. Библиотека построена с использованием структур `Matrix`, `MatrixResult` и `DeterminantResult` для удобного хранения и обработки данных и ошибок.

### Цель работы:

Освоить методы реализации операций над матрицами в языке C, включая динамическое выделение памяти, работу с файлами, обработку ошибок и реализацию функциональных интерфейсов.


### Основные задачи:
1. Реализация базовых операций над матрицами, включая создание, освобождение, копирование и вывод.
2. Поддержка арифметических операций: сумма, разность, умножение.
3. Поддержка линейной алгебры: транспонирование, определитель, минор.
4. Внедрение системы обработки ошибок с использованием перечисления `MatrixErrorCode`.
5. Подключение модулей вывода в консоль и файл.
6. Автоматизированная сборка проекта и тестирование.


### Структура проекта
```
/matrix_lib_c
│── src/
│   │── matrix/
│   │   │── matrix.c
│   │   │── matrix.h
│   │── errors/
│   │   │── errors.c
│   │   │── errors.h
│   │── output/
│   │   │── output.c
│   │   │── output.h
│   │── main.c
│── tests/
│   │── tests.c
│── include/
│	│── config.h
│── data/
│	│── input/
│	│── output/
│── Makefile
│── README.md
```

**Описание файлов и дирректорий:**
- **matrix.h/matrix.c** — основная реализация структур и функций работы с матрицами.
- **errors.h/errors.c** — модуль обработки ошибок, содержащий коды и проверки.
- **output.h/output.c** — функции вывода матрицы в консоль и файл.
- **main.c** — демонстрационная программа.
- **tests.c** — модуль тестирования библиотеки.
- **data/ouput** - содержит выходные данные (если пользователь выполнял запись в файл)
- **data/input** - содержит входные данные формата
```math
rows \; cols \\
n_{1,1} \; n_{1,2} \; ... \; n_{1,j} \\
n_{2,1} \; n_{2,2} \; ... \; n_{2,j} \\
... \\
n_{i,1} \; n_{i,2} \; ... \; n_{i,j}
```
- **Makefile** — сборка и тестирование проекта.
- **README.md** — описание проекта.

## Реализация

### Особенности реализации:

- Использование структуры `Matrix`, содержащей количество строк, столбцов и двумерный массив данных.
- Обработка ошибок через структуру `MatrixResult`, содержащую указатель на матрицу и код ошибки.
- Все функции возвращают результат в виде `MatrixResult` или `DeterminantResult`, что позволяет централизованно обрабатывать ошибки.
- Используются типы `MATRIX_TYPE` и `DETERMINANT_TYPE` из `config.h` для гибкой настройки типов данных.


## Функции, реализованные в библиотеке

### Функции для операций над матрицами
Функция | Описание
--- | ---
`createMatrix(rows, cols)` | Создает новую матрицу.
`freeMatrix()` | Освобождает память матрицы.
`freeMatrixResult()` | Освобождает память и очищает `MatrixResult`.
`fillMatrix()` | Заполняет матрицу данными из массива.
`loadMatrixFromFile()` | Загружает матрицу из файла.
`createMinor()` | Создает минор матрицы.
`getSumOrDiffMatrices()` | Вычисляет сумму или разность матриц.
`getMatrixCopy()` | Копирует матрицу.
`transposeMatrix()` | Транспонирует матрицу.
`findDeterminant()` | Вычисляет определитель.
`multiplyMatrices()` | Умножает матрицы.
`convertMatrixToBuffer()` | Преобразует матрицу в строку для вывода.

### Функции для вывода матриц
Функция | Описание
--- | ---
`outputToStdOut()` | Выводит матрицу в консоль.
`outputToFile()` | Выводит матрицу в файл.

### Функции проверки данных и обработки ошибок
Функция | Описание
--- | ---
`getErrorMessage()` | Возвращает строковое сообщение по коду ошибки.
`checkMatrixSize()` | Проверяет корректность размеров.
`matrixSizesIsEqual()` | Сравнивает размеры двух матриц.
`canExclude()` | Проверяет возможность исключения строки/столбца.
`canMultiplyMatrices()` | Проверяет совместимость для умножения.
`checkVariableCount()` | Проверяет количество переменных.


## Сборка и запуск проекта

**Сборка проекта:**
```sh
make
```

**Удаление промежуточных файлов:**
```sh
make clean
```

**Полная очистка:**
```sh
make cleanf
```

**Пересборка проекта:**
```sh
make rebuild
```

**Проверка форматирования:**
```sh
make check-format
```

**Применение форматирование:**
```sh
make format
```

**Запуск программы:**
```sh
./bin/MatrixLib
```

<!-- ## Тестирование -->

## Вывод
В результате работы была разработана библиотека для работы с матрицами, включающая создание, арифметические и алгебраические операции, вывод и обработку ошибок. Библиотека легко расширяема и сопровождается удобным интерфейсом и системой обработки ошибок.
