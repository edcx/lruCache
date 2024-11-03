
# LruCache - A C++ LRU Cache Implementation

## Overview

`LruCache` is a lightweight, generic C++ library that implements an in-memory cache with a Least Recently Used (LRU) eviction policy. It is designed for high-performance applications where memory efficiency is critical, and recent data is frequently reused. 

## Features

- **Least Recently Used Eviction**: Automatically evicts the least recently accessed item when the cache reaches capacity.
- **Generic API**: Supports any key-value data types.
- **Dynamic Resizing**: Allows adjusting the cache capacity at runtime.
- **Tested**: Includes a suite of unit tests for all main features.

## Getting Started

### Prerequisites

- **C++ Compiler**: Requires a compiler that supports C++17 or later.
- **CMake**: Version 3.14 or higher for building the project.
- **Catch2**: The unit tests use the Catch2 framework, which will be automatically downloaded using CMake.

### Building the Project

Create a build directory, configure, and build the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

The `LruCache` class can be used as a standalone component. Here’s a quick example demonstrating how to use it:

```cpp
#include "LruCache.h"
#include <iostream>

int main() {
    edcx::LruCache<int, std::string> cache(3); // Cache with capacity 3

    // Adding items to the cache
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    // Accessing items
    std::cout << "Value for key 1: " << cache.get(1).value_or("Not found") << std::endl;

    // Adding more items will trigger eviction of the least recently used item
    cache.put(4, "four");

    std::cout << "Value for key 2 (should be evicted): " << cache.get(2).value_or("Not found") << std::endl;

    return 0;
}
```

## API Reference

### Class: `LruCache<Key, Value>`

#### Constructor

- **`LruCache(size_t capacity)`**: Initializes the cache with the specified `capacity`.

#### Methods

- **`std::optional<Value> get(const Key& key)`**: Retrieves the value associated with `key` if it exists, updating the recency. Returns `std::nullopt` if the key is not in the cache.
  
- **`bool put(const Key& key, const Value& value)`**: Inserts or updates the key-value pair. Returns `true` if an eviction occurred, `false` otherwise.

- **`void remove(const Key& key)`**: Removes the specified key and its associated value from the cache, if present.

- **`void clear()`**: Clears all entries in the cache.

- **`void resize(size_t newCapacity)`**: Resizes the cache to the specified capacity, evicting items if the new capacity is smaller.

- **`bool contains(const Key& key) const`**: Checks if a key is present in the cache without updating recency.

- **`size_t size() const`**: Returns the current number of items in the cache.

- **`size_t capacity() const`**: Returns the maximum number of items the cache can hold.

## Testing

The project includes unit tests written using the Catch2 testing framework. To run the tests:

1. Ensure that you have built the project with CMake, as this will also build the test suite.
2. Run the tests using CTest:

   ```bash
   ctest
   ```

Alternatively, run the test executable directly:

```bash
./test/LruCacheTests
```

## Contributing

Contributions are welcome! Please open an issue to discuss any changes or improvements you’d like to make, or submit a pull request with your updates.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
