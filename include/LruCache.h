//
//  lruCache.h
//
//  Copyright (c) 2024 Engin Deniz Cengiz. All rights reserved.
//  MIT License
//

#pragma once

#include <optional>
#include <memory>

namespace edcx
{
    template <typename Key, typename Value>
    class LruCache
    {
    public:
        explicit LruCache(size_t capacity) : mCapacity(capacity) {}
        std::optional<Value> get(const Key &key) { return std::nullopt; }
        size_t size() const { return 0; }
        size_t capacity() const { return mCapacity; }

    private:
        size_t mCapacity;
    };
} // namespace edcx
