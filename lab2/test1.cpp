#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include "catch.hpp"
#include <cstring>
#include <cstdlib>
#include <cctype>

// ========== РЕАЛИЗАЦИЯ ФУНКЦИЙ ==========
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int is_consonant(char c) {
    c = tolower(c);
    return isalpha(c) && !is_vowel(c);
}

char* process_string_malloc(const char* input) {
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
    return result;
}

// ========== ТЕСТЫ ==========
TEST_CASE("Z1: замена точки на ... если гласная перед и согласная после") {
    SECTION("a.b -> a...b") {
        char* res = process_string_malloc("a.b");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "a...b") == 0);
        free(res);
    }

    SECTION("hello.world -> hello...world") {
        char* res = process_string_malloc("hello.world");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "hello...world") == 0);
        free(res);
    }

    SECTION("i.j -> i...j") {
        char* res = process_string_malloc("i.j");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "i...j") == 0);
        free(res);
    }
}

TEST_CASE("Z1: точка удаляется если условие не выполняется") {
    SECTION("a.a -> aa") {
        char* res = process_string_malloc("a.a");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "aa") == 0);
        free(res);
    }

    SECTION("b.c -> bc") {
        char* res = process_string_malloc("b.c");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "bc") == 0);
        free(res);
    }

    SECTION("test. -> test") {
        char* res = process_string_malloc("test.");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "test") == 0);
        free(res);
    }
}

TEST_CASE("Z1: граничные случаи") {
    SECTION("пустая строка") {
        char* res = process_string_malloc("");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "") == 0);
        free(res);
    }

    SECTION("строка без точек") {
        char* res = process_string_malloc("abcdef");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "abcdef") == 0);
        free(res);
    }
}
