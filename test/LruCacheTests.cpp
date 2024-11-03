#include <catch2/catch_test_macros.hpp>

#include "LruCache.h"

using namespace edcx;

TEST_CASE("A call to cache")
{
    LruCache<int, int> cache{6};

    auto cap = cache.capacity();

    REQUIRE(cap == 6);
}