#include <cassert>
#include <iostream>

template<typename T, typename Compare = std::less<T>>
class Heap {
    T* data;
    size_t capacity;
    size_t length;
    Compare cmp;

public:
    Heap(): capacity{0}, length{0} {}

    size_t len() const {
        return length;
    }

    void push(T val) {}

    T pop() {}

private:
    size_t left(size_t index) {
        return 2 * index + 1;
    }

    size_t right(size_t index) {
        return 2 * index + 2;
    }

    size_t parent(size_t index) {
        return (index - 1) / 2;
    }

    friend void test_heap();
};

void test_heap() {
    {
        Heap<int> heap; // Max heap (default)
    }
    {
        Heap<int, std::greater<int>> heap; // Min heap
    }
}

int main() {
    test_heap();
    std::cout << "All tests passed!\n";
}