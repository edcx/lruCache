#include <catch2/catch_test_macros.hpp>
#include "LruCache.h"

using namespace edcx;

TEST_CASE("Basic LRU Cache Operations")
{
    LruCache<int, int> cache(3);

    SECTION("Put and Get")
    {
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(3, 300);

        REQUIRE(cache.get(1) == 100);          // Cache hit
        REQUIRE(cache.get(4) == std::nullopt); // Cache miss
    }

    SECTION("Overwrite existing key")
    {
        cache.put(1, 100);
        cache.put(1, 150); // Overwrite
        REQUIRE(cache.get(1) == 150);
    }
}

TEST_CASE("Eviction Policy")
{
    LruCache<int, int> cache(2);

    SECTION("Evict least recently used item")
    {
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(3, 300); // Should evict key 1

        REQUIRE(cache.get(1) == std::nullopt); // Key 1 was evicted
        REQUIRE(cache.get(2) == 200);          // Key 2 should still be in cache
        REQUIRE(cache.get(3) == 300);          // Key 3 should still be in cache
    }
}

TEST_CASE("Resize Method")
{
    LruCache<int, int> cache(3);

    SECTION("Increase capacity")
    {
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(3, 300);

        cache.resize(5); // Increase capacity to 5
        cache.put(4, 400);
        cache.put(5, 500);

        // Ensure all items are still in the cache
        REQUIRE(cache.get(1) == 100);
        REQUIRE(cache.get(2) == 200);
        REQUIRE(cache.get(3) == 300);
        REQUIRE(cache.get(4) == 400);
        REQUIRE(cache.get(5) == 500);
    }

    SECTION("Decrease capacity")
    {
        cache.put(1, 100);
        cache.put(2, 200);
        cache.put(3, 300);

        cache.resize(2); // Decrease capacity to 2, should evict key 1 (least recently used)

        REQUIRE(cache.get(1) == std::nullopt); // Key 1 should be evicted
        REQUIRE(cache.get(2) == 200);          // Key 2 should still be in cache
        REQUIRE(cache.get(3) == 300);          // Key 3 should still be in cache
    }
}

TEST_CASE("Clear and Size Checking")
{
    LruCache<int, int> cache(3);

    SECTION("Clear cache")
    {
        cache.put(1, 100);
        cache.put(2, 200);
        cache.clear();

        REQUIRE(cache.size() == 0);
        REQUIRE(cache.get(1) == std::nullopt);
        REQUIRE(cache.get(2) == std::nullopt);
    }

    SECTION("Capacity and Size")
    {
        cache.put(1, 100);
        REQUIRE(cache.size() == 1);
        REQUIRE(cache.capacity() == 3);

        cache.put(2, 200);
        cache.put(3, 300);
        REQUIRE(cache.size() == 3); // Cache should be full now

        cache.put(4, 400);          // Should evict the least recently used item
        REQUIRE(cache.size() == 3); // Size should still be 3 after eviction
    }
}

TEST_CASE("Contains Method")
{
    LruCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    SECTION("Returns correct result")
    {
        REQUIRE(cache.contains(1) == true);
        REQUIRE(cache.contains(3) == false);
    }

    SECTION("Does not modify recently used-ness")
    {
        REQUIRE(cache.contains(1) == true);

        cache.put(3, 300); // Should evict key 1
        REQUIRE(cache.contains(1) == false);
    }
}

TEST_CASE("Peek method does not modify recently used-ness")
{
    LruCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(2, 200);

    REQUIRE(cache.peek(1) == 100);         // Cache hit
    cache.put(3, 300);                     // Should evict key 1
    REQUIRE(cache.get(1) == std::nullopt); // Cache miss
}

TEST_CASE("Remove method")
{
    LruCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);

    SECTION("Remove an existing key")
    {
        cache.remove(1);                       // 1 is removed
        REQUIRE(cache.get(1) == std::nullopt); // Cache miss
    }
    SECTION("Remove a non-existing key")
    {
        cache.remove(5); // does not remove anything
        REQUIRE(cache.size() == 3);
    }
}