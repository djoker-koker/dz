#include "catch_amalgamated.hpp"
#include "z2.cpp"

TEST_CASE("Z2: точка заменяется на ... если гласная перед и согласная после") {
    SECTION("a.b -> a...b") {
        char* res = process_string_calloc("a.b");
        REQUIRE(std::strcmp(res, "a...b") == 0);
        free(res);
    }

    SECTION("hello.world -> hello...world") {
        char* res = process_string_calloc("hello.world");
        REQUIRE(std::strcmp(res, "hello...world") == 0);
        free(res);
    }
}

TEST_CASE("Z2: точка удаляется если условие не выполняется") {
    SECTION("a.a -> aa") {
        char* res = process_string_calloc("a.a");
        REQUIRE(std::strcmp(res, "aa") == 0);
        free(res);
    }

    SECTION("b.c -> bc") {
        char* res = process_string_calloc("b.c");
        REQUIRE(std::strcmp(res, "bc") == 0);
        free(res);
    }
}

TEST_CASE("Z2: несколько точек") {
    SECTION("a.b.c.d -> a...bc...d") {
        char* res = process_string_calloc("a.b.c.d");
        REQUIRE(std::strcmp(res, "a...bc...d") == 0);
        free(res);
    }
}

TEST_CASE("Z2: граничные случаи") {
    SECTION("пустая строка") {
        char* res = process_string_calloc("");
        REQUIRE(std::strcmp(res, "") == 0);
        free(res);
    }

    SECTION("строка без точек") {
        char* res = process_string_calloc("abcdef");
        REQUIRE(std::strcmp(res, "abcdef") == 0);
        free(res);
    }
}
