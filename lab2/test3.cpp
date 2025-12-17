#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include "catch.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

// ========== РЕАЛИЗАЦИЯ функции process_string ==========
// (такая же как в z1/z2/z3)
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int is_consonant(char c) {
    c = tolower(c);
    return isalpha(c) && !is_vowel(c);
}

char* process_string(const char* input) {
    if (!input) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    int len = (int)strlen(input);
    char* result = (char*)malloc((len * 3 + 1) * sizeof(char));
    if (!result) return nullptr;

    int res_index = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '.' && i > 0 && i < len - 1 &&
            is_vowel(input[i - 1]) && is_consonant(input[i + 1])) {
            result[res_index++] = '.';
            result[res_index++] = '.';
            result[res_index++] = '.';
        }
        else if (input[i] != '.') {
            result[res_index++] = input[i];
        }
    }
    result[res_index] = '\0';

    // Если результат пустой, перераспределяем память
    if (res_index == 0) {
        free(result);
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    return result;
}

// ========== Вспомогательные функции для файлов ==========
void create_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    if (f) {
        fprintf(f, "%s", content);
        fclose(f);
    }
}

char* read_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return nullptr;

    // Определяем размер файла
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Выделяем память
    char* content = (char*)malloc(size + 1);
    if (!content) {
        fclose(f);
        return nullptr;
    }

    // Читаем файл
    size_t bytes_read = fread(content, 1, size, f);
    content[bytes_read] = '\0';

    // Убираем символ новой строки если есть
    if (bytes_read > 0 && content[bytes_read - 1] == '\n') {
        content[bytes_read - 1] = '\0';
    }

    fclose(f);
    return content;
}

bool file_exists(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return true;
    }
    return false;
}

void delete_file(const char* filename) {
    remove(filename);
}

// ========== ИСПРАВЛЕННЫЕ ТЕСТЫ ==========
TEST_CASE("Z3: обработка строки (файловый ввод/вывод)") {

    SECTION("запись в файл и чтение - упрощенный тест") {
        // Создаем тестовый файл
        const char* test_filename = "test_file1.txt";
        const char* test_content = "hello.world";

        create_file(test_filename, test_content);

        // Проверяем, что файл создался и читается
        char* content = read_file(test_filename);
        REQUIRE(content != nullptr);
        REQUIRE(strcmp(content, "hello.world") == 0);

        // Обрабатываем строку как в z3
        char* res = process_string(content);
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "hello...world") == 0);

        // Записываем результат в другой файл (имитация z3)
        const char* output_filename = "test_file2.txt";
        create_file(output_filename, res);

        // Проверяем, что файл создан
        REQUIRE(file_exists(output_filename));

        // Читаем и проверяем содержимое
        char* output_content = read_file(output_filename);
        REQUIRE(output_content != nullptr);
        REQUIRE(strcmp(output_content, "hello...world") == 0);

        // Очистка
        free(content);
        free(res);
        free(output_content);
        delete_file(test_filename);
        delete_file(output_filename);
    }

    SECTION("обработка пустой строки из файла") {
        const char* test_filename = "test_empty.txt";

        // Создаем файл с пустой строкой
        create_file(test_filename, "");

        // Читаем файл
        char* content = read_file(test_filename);
        REQUIRE(content != nullptr);
        REQUIRE(strcmp(content, "") == 0);

        // Обрабатываем
        char* res = process_string(content);
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "") == 0);

        // Очистка
        free(content);
        free(res);
        delete_file(test_filename);
    }

    SECTION("обработка строки без точек") {
        const char* test_filename = "test_no_dots.txt";
        const char* test_content = "abcdef";

        create_file(test_filename, test_content);

        char* content = read_file(test_filename);
        REQUIRE(content != nullptr);
        REQUIRE(strcmp(content, "abcdef") == 0);

        char* res = process_string(content);
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "abcdef") == 0);

        free(content);
        free(res);
        delete_file(test_filename);
    }

    SECTION("полный цикл как в z3.cpp") {
        // 1. Создаем входной файл (как file1.txt в z3)
        const char* input_file = "z3_input.txt";
        const char* input_content = "a.b test. hello.world";
        create_file(input_file, input_content);

        // 2. Имитируем чтение из файла (как в z3)
        char* input = read_file(input_file);
        REQUIRE(input != nullptr);
        REQUIRE(strcmp(input, "a.b test. hello.world") == 0);

        // 3. Имитируем обработку (как в z3)
        char* result = process_string(input);
        REQUIRE(result != nullptr);
        REQUIRE(strcmp(result, "a...b test hello...world") == 0);

        // 4. Имитируем запись в файл (как file2.txt в z3)
        const char* output_file = "z3_output.txt";
        create_file(output_file, result);

        // 5. Проверяем, что файл создан и содержит правильный результат
        REQUIRE(file_exists(output_file));
        char* output = read_file(output_file);
        REQUIRE(output != nullptr);
        REQUIRE(strcmp(output, "a...b test hello...world") == 0);

        // 6. Очистка
        free(input);
        free(result);
        free(output);
        delete_file(input_file);
        delete_file(output_file);
    }

    SECTION("файл с точкой в начале строки") {
        const char* test_filename = "test_start_dot.txt";
        const char* test_content = ".start test";

        create_file(test_filename, test_content);

        char* content = read_file(test_filename);
        REQUIRE(content != nullptr);

        char* res = process_string(content);
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "start test") == 0);

        free(content);
        free(res);
        delete_file(test_filename);
    }

    SECTION("файл только с точками") {
        const char* test_filename = "test_only_dots.txt";
        const char* test_content = "...";

        create_file(test_filename, test_content);

        char* content = read_file(test_filename);
        REQUIRE(content != nullptr);

        char* res = process_string(content);
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "") == 0);

        free(content);
        free(res);
        delete_file(test_filename);
    }
}
