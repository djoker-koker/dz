#include "catch_amalgamated.hpp"
#include <cstdio>
#include <cstring>

extern char* process_string(const char* input);

TEST_CASE("Z3: обработка строки (файловый ввод/вывод)") {
    SECTION("запись в файл и чтение") {
        // Создаем тестовый файл
        FILE* f = fopen("file1.txt", "w");
        REQUIRE(f != nullptr);
        fprintf(f, "hello.world");
        fclose(f);

        // Запускаем z3 (в реальности нужно запустить программу)
        // Для теста просто проверяем функцию process_string
        char* res = process_string("hello.world");
        REQUIRE(std::strcmp(res, "hello...world") == 0);
        free(res);

        // Проверяем, что файл file2.txt создан (в реальном тесте нужно читать его)
        FILE* f2 = fopen("file2.txt", "r");
        REQUIRE(f2 != nullptr);
        fclose(f2);
    }

    SECTION("обработка пустой строки из файла") {
        FILE* f = fopen("file1.txt", "w");
        REQUIRE(f != nullptr);
        fprintf(f, "");
        fclose(f);

        char* res = process_string("");
        REQUIRE(std::strcmp(res, "") == 0);
        free(res);
    }

    SECTION("обработка строки без точек") {
        FILE* f = fopen("file1.txt", "w");
        REQUIRE(f != nullptr);
        fprintf(f, "abcdef");
        fclose(f);

        char* res = process_string("abcdef");
        REQUIRE(std::strcmp(res, "abcdef") == 0);
        free(res);
    }
}
