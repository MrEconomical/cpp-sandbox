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
class HashMap {
    forward_list<Item<K, V>>* buckets;
    size_t num_buckets;
    size_t map_size;
    hash<K> hasher;

public:
    HashMap(): num_buckets{DEFAULT_BUCKETS}, map_size{0} {
        buckets = (forward_list<Item<K, V>>*) malloc(sizeof(forward_list<Item<K, V>>) * DEFAULT_BUCKETS);
        for (size_t b = 0; b < DEFAULT_BUCKETS; b ++) {
            new (buckets + b) forward_list<Item<K, V>>;
        }
    }

    HashMap(size_t size): num_buckets{size}, map_size{0} {
        buckets = (forward_list<Item<K, V>>*) malloc(sizeof(forward_list<Item<K, V>>) * size);
        for (size_t b = 0; b < size; b ++) {
            new (buckets + b) forward_list<Item<K, V>>;
        }
    }

    size_t len() const {
        return map_size;
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