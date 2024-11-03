cmake_minimum_required(VERSION 3.22)

project(
    LruCache
    VERSION 0.1
    DESCRIPTION "Least recently used caching library"
    HOMEPAGE_URL "https://github.com/edcx/lru-cache"
)

enable_testing()

add_subdirectory(test)