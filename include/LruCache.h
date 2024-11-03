//
//  LruCache.h
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

        /**
         * @brief Returns the key's value from the cache if it exists.
         * Updates the recentlyness of the key.
         */
        std::optional<Value> get(const Key &key)
        {
            return std::nullopt;
        }

        /**
         * @brief Puts the given <key, value> into the cache. Updates the
         * value if the key exists. Updates the recentlyness of the key.
         *
         * @return true if eviction occured. false otherwise.
         */
        bool put(const Key &key, const Value &value)
        {
            throw;
        }

        /**
         * @brief Checks if a key exists in the cache.
         * Does not updates recentlyness of the item
         */
        bool contains(const Key &key)
        {
            throw;
        }

        /**
         * @brief Returns the value of the key without
         * updating recentlyness of the item.
         */
        std::optional<Value> peek(const Key &key)
        {
            throw;
        }

        /**
         * @brief Removes the key from the cache
         */
        void remove(const Key &key)
        {
            throw;
        }

        /**
         * @brief Removes all the entries from the cache.
         */
        void clear()
        {
            throw;
        }

        /**
         * @brief Returns the number of entries in the cache.
         */
        size_t size() const { return 0; }

        /**
         * @brief Returns the capacity of the cache.
         */
        size_t capacity() const { return mCapacity; }

        /**
         * @brief Resizes the capacity of the cache. Eviction might occur
         * if the new capacity is less than the number of entries in the
         * cache.
         */
        void resize(size_t capacity)
        {
            throw;
        }

    private:
        size_t mCapacity;
    };
} // namespace edcx
