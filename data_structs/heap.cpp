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

    T peek() {
        if (length == 0) {
            throw std::exception("heap is empty");
        }
        return data[0];
    }

    void push(T val) {}

    T pop() {}

    ~Heap() {
        if (capacity > 0) {
            free((void*) data);
        }
    }

private:
    void push_back(T val) {
        if (capacity == 0) {
            data = (T*) malloc(sizeof(T));
            capacity = 1;
        } else if (capacity == length) {
            data = (T*) realloc((void*) data, sizeof(T) * capacity * 2);
            capacity *= 2;
        }
        data[length] = val;
        length ++;
    }

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