В различных клетках шахматной доски размером в $M$ строк и $N$ столбцов находятся два коня: белый и чёрный. 
Они поочерёдно делают ходы согласно шахматным правилам так, что первый и все нечётные ходы делает белый конь, а второй и все чётные — чёрный. 
При этом в любой момент времени кони могут находиться в одной клетке (взятий при этом не происходит) или ходить в клетку, где уже стоит другой конь.
Определите минимальный номер хода, после выполнения которого кони окажутся в одной клетке. Определите также координаты клетки (номер строки и столбца), в которой произойдёт встреча.
Напомним, что, согласно шахматным правилам, конь за один ход передвигается на две клетки по горизонтали или вертикали и на одну клетку в перпендикулярном направлении. Выходить за пределы доски при этом нельзя.

Input
В первой строке записаны целые числа $M$ и $N$ ($1 \leqslant M, N \leqslant 1000, M \cdot N > 1$).
Во второй и третьей строках заданы номера строки и столбца, в которых изначально находится соответственно белый и чёрный конь. 
Нумерация строк и столбцов начинается с единицы.

Output
Выведите три числа — количество ходов и координаты клетки (номер строки и номер столбца), в которой произойдёт встреча. 
Если задача допускает несколько решений, выведите любое из них. Если решения не существует, выведите три ноля.

Examples
standard input:	8 8  3 2  5 7 standard output: 3 3 6
standard input:	2 3  1 1  2 1 standard output: 0 0 0

https://acm.bsu.by/contests/249/problems/4849/

Installation:

### Step-by-Step Installation of Google Test

1. **Install Required Packages**

   Ensure you have the necessary tools installed:

   ```bash
   sudo dnf install git cmake gcc-c++
   ```

2. **Clone the Google Test Repository**

   Open a terminal and clone the Google Test repository:

   ```bash
   git clone https://github.com/google/googletest.git
   cd googletest
   ```

3. **Build Google Test**

   Create a build directory and navigate into it:

   ```bash
   mkdir build
   cd build
   ```

4. **Run CMake**

   Configure the build with CMake:

   ```bash
   cmake ..
   ```

5. **Compile the Library**

   Compile the library:

   ```bash
   make
   ```

6. **Install the Libraries**

   Copy the compiled libraries to the appropriate directories:

   ```bash
   sudo cp libgtest.a /usr/lib/
   sudo cp libgtest_main.a /usr/lib/
   ```

7. **Copy the Header Files**

   The header files for Google Test are located in the `googletest/include` directory. You can copy them as follows:

   ```bash
   sudo cp -r ../googletest/include/gtest /usr/include/
   ```

### Verify Installation

To verify that Google Test is correctly installed, you can check the `/usr/include/gtest` directory:

```bash
ls /usr/include/gtest
```

You should see files like `gtest.h`, `gtest_main.h`, etc.

### Linking GTest in Your Project

Ensure your `CMakeLists.txt` is set up to find and link GTest:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Find GTest package
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})

# Add your executable
add_executable(MyTests test_main.cpp)

# Link GTest libraries
target_link_libraries(MyTests ${GTEST_LIBRARIES} pthread)
```

### Build Your Project

1. **Create a build directory**:

   ```bash
   mkdir build
   cd build
   ```

2. **Run CMake**:

   ```bash
   cmake ..
   ```

3. **Build the project**:

   ```bash
   make
   ```

### Summary

By following these steps, you should be able to successfully build and install Google Test on your system. If you encounter any further issues, feel free to ask!

Для создания тестов в C++ с использованием CMake и Visual Studio Code, вы можете следовать этим шагам:

### Шаг 1: Установите необходимые инструменты

1. **CMake**: Убедитесь, что у вас установлен CMake.
2. **Google Test**: Это популярная библиотека для тестирования в C++. Вы можете использовать её для написания тестов.
3. **Visual Studio Code**: Убедитесь, что у вас установлены расширения C/C++ и CMake Tools.

### Шаг 2: Настройка проекта

1. Создайте структуру проекта. Например:

   ```
   MyProject/
   ├── CMakeLists.txt
   ├── src/
   │   └── main.cpp
   └── tests/
       ├── CMakeLists.txt
       └── test_main.cpp
   ```

2. В корневом `CMakeLists.txt` добавьте следующие строки:

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   # Добавляем папку с исходниками
   add_subdirectory(src)
   add_subdirectory(tests)
   ```

3. В `src/CMakeLists.txt` добавьте:

   ```cmake
   add_library(MyLibrary main.cpp)
   ```

4. В `tests/CMakeLists.txt` добавьте:

   ```cmake
   enable_testing()

   find_package(GTest REQUIRED)
   include_directories(${GTEST_INCLUDE_DIRS})

   add_executable(MyTests test_main.cpp)
   target_link_libraries(MyTests MyLibrary ${GTEST_LIBRARIES} pthread)

   add_test(NAME MyTests COMMAND MyTests)
   ```

### Шаг 3: Напишите тесты

В файле `tests/test_main.cpp` напишите ваши тесты:

```cpp
#include <gtest/gtest.h>

// Пример функции для тестирования
int Add(int a, int b) {
    return a + b;
}

TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(Add(1, 2), 3);
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(Add(-1, -1), -2);
}
```

### Шаг 4: Сборка и запуск тестов

1. Откройте терминал в Visual Studio Code.
2. Перейдите в корневую папку проекта и создайте сборочную директорию:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. После успешной сборки запустите тесты:

   ```bash
   ctest
   ```

### Шаг 5: Просмотр результатов тестов

Вы увидите результаты тестов в терминале. Если все прошло успешно, вы получите сообщение о том, что все тесты пройдены.

Теперь вы готовы к разработке и тестированию вашего C++ проекта с использованием CMake и Visual Studio Code!