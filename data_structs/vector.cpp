#include <cassert>
#include <cstdlib>
#include <iostream>

template<typename T>
class Vector {
    T* data;
    size_t capacity;
    size_t length;

public:
    Vector(): data{nullptr}, capacity{0}, length{0} {}

    Vector(size_t size): capacity{size}, length{0} {
        data = (T*) malloc(sizeof(T) * size);
    }

    size_t len() const {
        return length;
    }

    T get(size_t index) const {
        if (index >= length) {
            throw std::exception("index out of bounds");
        }
        return data[index];
    }

    void push(T val) {
        if (capacity == 0) {
            data = (T*) malloc(sizeof(T));
            capacity = 1;
        } else if (length == capacity) {
            data = (T*) realloc((void*) data, sizeof(T) * capacity * 2);
            capacity *= 2;
        }
        data[length] = val;
        length ++;
    }

    void remove(size_t index) {
        if (index >= length) {
            throw std::exception("index out of bounds");
        }
        for (size_t v = index + 1; v < length; v ++) {
            data[v - 1] = data[v];
        }
        length --;
    }

    ~Vector() {
        if (capacity > 0) {
            free((void*) data);
        }
    }

    friend void test_vector();
};

void test_vector() {
    {
        Vector<int> vec;
        assert(vec.len() == 0);
        assert(vec.data == nullptr && vec.capacity == 0);

        vec.push(1);
        assert(vec.len() == 1);
        assert(vec.get(0) == 1);
        assert(vec.data != nullptr && vec.capacity == 1);

        vec.push(2);
        vec.push(3);
        assert(vec.len() == 3);
        assert(vec.get(0) == 1 && vec.get(1) == 2 && vec.get(2) == 3);
        assert(vec.data != nullptr && vec.capacity == 4);

        vec.push(4);
        vec.push(5);
        assert(vec.len() == 5);
        assert(vec.get(0) == 1 && vec.get(1) == 2 && vec.get(2) == 3 && vec.get(3) == 4 && vec.get(4) == 5);
        assert(vec.data != nullptr && vec.capacity == 8);

        vec.remove(3);
        vec.remove(0);
        assert(vec.len() == 3);
        assert(vec.get(0) == 2 && vec.get(1) == 3 && vec.get(2) == 5);
        assert(vec.data != nullptr && vec.capacity == 8);

        vec.remove(1);
        vec.remove(0);
        vec.remove(0);
        assert(vec.len() == 0);
        assert(vec.data != nullptr && vec.capacity == 8);
    }
    {
        Vector<int> vec(6);
        assert(vec.len() == 0);
        assert(vec.data != nullptr && vec.capacity == 6);

        vec.push(1);
        vec.push(2);
        assert(vec.len() == 2);
        assert(vec.get(0) == 1 && vec.get(1) == 2);
        assert(vec.data != nullptr && vec.capacity == 6);

        vec.remove(1);
        assert(vec.len() == 1);
        assert(vec.get(0) == 1);
        assert(vec.data != nullptr && vec.capacity == 6);

        vec.remove(0);
        assert(vec.len() == 0);
        assert(vec.data != nullptr && vec.capacity == 6);
    }
}

int main() {
    test_vector();
    std::cout << "All tests passed!\n";
}