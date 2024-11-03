#include <catch2/catch_test_macros.hpp>

#include "LruCache.h"

using namespace edcx;

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("A call to cache")
{
    LruCache<int, int> cache{6};

    auto cap = cache.capacity();
    REQUIRE(cap == 6);
}