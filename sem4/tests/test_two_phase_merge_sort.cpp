#include "../../catch_amalgamated.hpp"
#include "../sorting/include/two_phase_merge_sort.h"

TEST_CASE("Domashka")
{
    std::vector<int> arr = {17, 3, 0, 12, 6, 9, 19, 1};
    std::vector<int> expected = {0, 1, 3, 6, 9, 12, 17, 19};

    two_phase_merge_sort(arr);
    REQUIRE(arr == expected);
}

TEST_CASE("Pustoy massiv")
{
    std::vector<int> arr = {};
    std::vector<int> expected = {};

    two_phase_merge_sort(arr);
    REQUIRE(arr == expected);
}

TEST_CASE("Odin element")
{
    std::vector<int> arr = {5};
    std::vector<int> expected = {5};

    two_phase_merge_sort(arr);
    REQUIRE(arr == expected);
}

TEST_CASE("Otsortirovano")
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    two_phase_merge_sort(arr);
    REQUIRE(arr == expected);
}
