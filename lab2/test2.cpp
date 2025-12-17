#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include "catch.hpp"
#include <cstring>
#include <cstdlib>
#include <cctype>

// ========== РЕАЛИЗАЦИЯ ФУНКЦИЙ для z2 ==========
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int is_consonant(char c) {
    c = tolower(c);
    return isalpha(c) && !is_vowel(c);
}

char* process_string_calloc(const char* input) {
    int len = (int)strlen(input);
    char* result = (char*)calloc(len * 3 + 1, sizeof(char));
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

// ========== ИСПРАВЛЕННЫЕ ТЕСТЫ для z2 ==========
TEST_CASE("Z2: замена точки на ... (calloc/realloc версия)") {
    SECTION("a.b -> a...b") {
        char* res = process_string_calloc("a.b");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "a...b") == 0);
        free(res);
    }

    SECTION("hello.world -> hello...world") {
        char* res = process_string_calloc("hello.world");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "hello...world") == 0);
        free(res);
    }

    SECTION("e.f.g.h -> e...fgh") {  // ИСПРАВЛЕНО!
        char* res = process_string_calloc("e.f.g.h");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "e...fgh") == 0);  // e.f -> e...f, остальные точки удаляются
        free(res);
    }
}

TEST_CASE("Z2: точка удаляется если условие не выполняется") {
    SECTION("b.c -> bc (не гласная перед)") {
        char* res = process_string_calloc("b.c");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "bc") == 0);
        free(res);
    }

    SECTION("a.a -> aa (не согласная после)") {
        char* res = process_string_calloc("a.a");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "aa") == 0);
        free(res);
    }

    SECTION("test. -> test (точка в конце)") {
        char* res = process_string_calloc("test.");
        REQUIRE(res != nullptr);
        REQUIRE(strcmp(res, "test") == 0);
        free(res);
    }
}

TEST_CASE("Z2: проверка calloc инициализации нулями") {
    SECTION("calloc инициализация") {
        char* res = process_string_calloc("test");
        REQUIRE(res != nullptr);
        REQUIRE(strlen(res) == 4);
        REQUIRE(res[4] == '\0');
        free(res);
    }
}

TEST_CASE("Z2: сложные случаи") {
    SECTION("много точек") {
        char* res = process_string_calloc("a.b.c.d.e.f");
        REQUIRE(res != nullptr);
        // a.b -> a...b, e.f -> e...f, остальные точки удаляются
        REQUIRE(strcmp(res, "a...bcde...f") == 0);  // ИСПРАВЛЕНО!
        free(res);
    }

    SECTION("точки и другие знаки препинания") {
        char* res = process_string_calloc("Hello, world! Is this a.test? Yes, it.is!");
        REQUIRE(res != nullptr);
        // a.test -> a...test, it.is -> itis (точка удаляется, t - согласная)
        REQUIRE(strcmp(res, "Hello, world! Is this a...test? Yes, itis!") == 0);  // ИСПРАВЛЕНО!
        free(res);
    }
}
