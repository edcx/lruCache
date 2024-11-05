//
//  LruCache.h
//
//  Copyright (c) 2024 Engin Deniz Cengiz. All rights reserved.
//  MIT License
//

#pragma once

#include <cassert>
#include <list>
#include <optional>
#include <unordered_map>

namespace edcx {
template<typename Key, typename Value>
class LruCache {
public:
    explicit LruCache(size_t capacity)
        : mCapacity(capacity)
    {
    }

    /**
     * @brief Returns the key's value from the cache if it exists.
     * Updates the recentlyness of the key.
     */
    std::optional<Value> get(const Key& key)
    {
        auto it = mCache.find(key);
        if (it == mCache.end()) {
            return std::nullopt; // Cache miss
        }
        // Move accessed key to the front of the usage order
        mUsageOrder.splice(mUsageOrder.begin(), mUsageOrder, it->second.second);
        return it->second.first;
    }

    /**
     * @brief Puts the given <key, value> into the cache. Updates the
     * value if the key exists. Updates the recentlyness of the key.
     *
     * @return true if eviction occured. false otherwise.
     */
    bool put(const Key& key, const Value& value)
    {
        auto it = mCache.find(key);
        if (it != mCache.end()) {
            // Update existing key and move to front
            mUsageOrder.splice(mUsageOrder.begin(), mUsageOrder, it->second.second);
            it->second.first = value;
            return false; // No eviction
        }

        if (mCache.size() == mCapacity) {
            assert(mCapacity != 0);
            // Cache is full, evict the least recently used item (back of list)
            auto lruKey = mUsageOrder.back();
            mUsageOrder.pop_back();
            mCache.erase(lruKey);
        }

        // Insert new item
        mUsageOrder.push_front(key);
        mCache[key] = { value, mUsageOrder.begin() };
        return true; // Eviction occurred if cache was full
    }

    /**
     * @brief Checks if a key exists in the cache.
     * Does not updates recentlyness of the item
     */
    bool contains(const Key& key)
    {
        return mCache.find(key) != mCache.end();
    }

    /**
     * @brief Returns the value of the key without
     * updating recentlyness of the item.
     */
    std::optional<Value> peek(const Key& key)
    {
        auto it = mCache.find(key);
        if (it == mCache.end()) {
            return std::nullopt; // Cache miss
        }
        return it->second.first;
    }

    /**
     * @brief Removes the key from the cache
     */
    void remove(const Key& key)
    {
        auto it = mCache.find(key);
        if (it != mCache.end()) {
            mUsageOrder.erase(it->second.second);
            mCache.erase(it);
        }
    }

    /**
     * @brief Removes all the entries from the cache.
     */
    void clear()
    {
        mCache.clear();
        mUsageOrder.clear();
    }

    /**
     * @brief Returns the number of entries in the cache.
     */
    size_t size() const { return mCache.size(); }

    /**
     * @brief Returns the capacity of the cache.
     */
    size_t capacity() const { return mCapacity; }

    /**
     * @brief Resizes the capacity of the cache. Eviction might occur
     * if the new capacity is less than the number of entries in the
     * cache.
     */
    void resize(size_t newCapacity)
    {
        if (newCapacity >= mCapacity) {
            // Increase capacity or keep it the same, no eviction needed
            mCapacity = newCapacity;
            return;
        }

        // Decrease capacity, evict items if necessary
        while (mCache.size() > newCapacity) {
            // Evict from the back (least recently used item)
            auto lruKey = mUsageOrder.back();
            mUsageOrder.pop_back();
            mCache.erase(lruKey);
        }

        mCapacity = newCapacity;
    }

private:
    size_t mCapacity;
    std::list<Key> mUsageOrder; // Stores keys in LRU order
    std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>> mCache;
};
} // namespace edcx
