#include <cassert>
#include <cstdlib>
#include <forward_list>
#include <iostream>

using std::forward_list, std::hash;

const size_t DEFAULT_BUCKETS = 1000;

template<typename K, typename V>
struct Item {
    K key;
    V val;
};

template<typename K, typename V>
using ItemList = forward_list<Item<K, V>>;

template<typename K, typename V>
class HashMap {
    ItemList<K, V>* buckets;
    size_t num_buckets;
    size_t map_size;
    hash<K> hasher;

public:
    HashMap(): num_buckets{DEFAULT_BUCKETS}, map_size{0} {
        buckets = (ItemList<K, V>*) malloc(sizeof(ItemList<K, V>) * DEFAULT_BUCKETS);
        for (size_t b = 0; b < DEFAULT_BUCKETS; b ++) {
            new (buckets + b) ItemList<K, V>;
        }
    }

    HashMap(size_t size): num_buckets{size}, map_size{0} {
        if (size == 0) {
            throw std::exception("bucket count must be positive");
        }
        buckets = (ItemList<K, V>*) malloc(sizeof(ItemList<K, V>) * size);
        for (size_t b = 0; b < size; b ++) {
            new (buckets + b) ItemList<K, V>;
        }
    }

    size_t len() const {
        return map_size;
    }

    bool contains(const K& key) const {
        size_t bucket = hasher(key) % num_buckets;
        return find_item_const(buckets[bucket], key) != buckets[bucket].cend();
    }

    V get(const K& key) const {
        size_t bucket = hasher(key) % num_buckets;
        auto item = find_item_const(buckets[bucket], key);
        if (item == buckets[bucket].cend()) {
            throw std::exception("key not found");
        }
        return item->val;
    }

    void insert(K key, V val) {
        size_t bucket = hasher(key) % num_buckets;
        auto item = find_item(buckets[bucket], key);
        if (item == buckets[bucket].end()) {
            buckets[bucket].push_front(Item<K, V>{key, val});
        } else {
            item->val = val;
        }
    }

private:
    typename ItemList<K, V>::const_iterator find_item_const(const ItemList<K, V>& bucket, const K& key) const {
        return std::find_if(
            bucket.cbegin(),
            bucket.cend(),
            [&key](const Item<K, V>& item) {
                return item.key == key;
            }
        );
    }

    typename ItemList<K, V>::iterator find_item(ItemList<K, V>& bucket, const K& key) {
        return std::find_if(
            bucket.begin(),
            bucket.end(),
            [&key](const Item<K, V>& item) {
                return item.key == key;
            }
        );
    }

    friend void test_hash_map();
};

void test_hash_map() {
    {
        HashMap<int, int> map;
        assert(map.len() == 0);
        assert(map.buckets != nullptr);
        assert(map.num_buckets == DEFAULT_BUCKETS);
    }
    {
        HashMap<int, int> map(100);
        assert(map.len() == 0);
        assert(map.buckets != nullptr);
        assert(map.num_buckets == 100);
    }
}

int main() {
    test_hash_map();
    std::cout << "All tests passed!\n";
}