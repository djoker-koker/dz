#include "catch_amalgamated.hpp"
#include "z1.cpp"

TEST_CASE("Z1: точка заменяется на ... если гласная перед и согласная после") {
    SECTION("a.b -> a...b") {
        char* res = process_string_malloc("a.b");
        REQUIRE(std::strcmp(res, "a...b") == 0);
        free(res);
    }

    SECTION("hello.world -> hello...world") {
        char* res = process_string_malloc("hello.world");
        REQUIRE(std::strcmp(res, "hello...world") == 0);
        free(res);
    }

    SECTION("i.j -> i...j") {
        char* res = process_string_malloc("i.j");
        REQUIRE(std::strcmp(res, "i...j") == 0);
        free(res);
    }
}

TEST_CASE("Z1: точка удаляется если условие не выполняется") {
    SECTION("a.a -> aa") {
        char* res = process_string_malloc("a.a");
        REQUIRE(std::strcmp(res, "aa") == 0);
        free(res);
    }

    SECTION("b.c -> bc") {
        char* res = process_string_malloc("b.c");
        REQUIRE(std::strcmp(res, "bc") == 0);
        free(res);
    }

    SECTION("test. -> test") {
        char* res = process_string_malloc("test.");
        REQUIRE(std::strcmp(res, "test") == 0);
        free(res);
    }

    SECTION(".start -> start") {
        char* res = process_string_malloc(".start");
        REQUIRE(std::strcmp(res, "start") == 0);
        free(res);
    }
}

TEST_CASE("Z1: несколько точек") {
    SECTION("a.b.c.d -> a...bc...d") {
        char* res = process_string_malloc("a.b.c.d");
        REQUIRE(std::strcmp(res, "a...bc...d") == 0);
        free(res);
    }

    SECTION("e.f.g.h -> e...fg...h") {
        char* res = process_string_malloc("e.f.g.h");
        REQUIRE(std::strcmp(res, "e...fg...h") == 0);
        free(res);
    }
}

TEST_CASE("Z1: граничные случаи") {
    SECTION("пустая строка") {
        char* res = process_string_malloc("");
        REQUIRE(std::strcmp(res, "") == 0);
        free(res);
    }

    SECTION("строка без точек") {
        char* res = process_string_malloc("abcdef");
        REQUIRE(std::strcmp(res, "abcdef") == 0);
        free(res);
    }

    SECTION("только точки") {
        char* res = process_string_malloc("...");
        REQUIRE(std::strcmp(res, "") == 0);
        free(res);
    }
}
