#include <cassert>
#include <iostream>

template<typename T, typename Compare = std::less<T>>
class Heap {
    T* data;
    size_t capacity;
    size_t length;
    Compare cmp;

public:
    Heap(): data{nullptr}, capacity{0}, length{0} {}

    size_t len() const {
        return length;
    }

    T peek() {
        if (length == 0) {
            throw std::exception("heap is empty");
        }
        return data[0];
    }

    void push(T val) {
        push_back(val);
        size_t current = length - 1;
        while (current > 0 && cmp(data[parent(current)], data[current])) {
            std::swap(data[parent(current)], data[current]);
            current = parent(current);
        }
    }

    T pop() {
        if (length == 0) {
            throw std::exception("heap is empty");
        }

        T top = data[0];
        data[0] = data[length - 1];
        length --;
        if (length > 1) {
            sift(0);
        }

        return top;
    }

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

    void sift(size_t index) {
        size_t max_index = index;
        if (left(index) < length && cmp(data[max_index], data[left(index)])) {
            max_index = left(index);
        }
        if (right(index) < length && cmp(data[max_index], data[right(index)])) {
            max_index = right(index);
        }
        if (max_index != index) {
            std::swap(data[index], data[max_index]);
            sift(max_index);
        }
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
        assert(heap.len() == 0);
        assert(heap.data == nullptr && heap.capacity == 0);

        heap.push(6);
        assert(heap.len() == 1);
        assert(heap.peek() == 6);
        assert(heap.data != nullptr && heap.capacity == 1);
        
        heap.push(2);
        heap.push(5);
        assert(heap.len() == 3);
        assert(heap.peek() == 6);
        assert(heap.data != nullptr && heap.capacity == 4);
        
        heap.push(9);
        heap.push(9);
        assert(heap.len() == 5);
        assert(heap.peek() == 9);
        assert(heap.data != nullptr && heap.capacity == 8);

        assert(heap.pop() == 9);
        assert(heap.len() == 4);
        assert(heap.peek() == 9);
        assert(heap.data != nullptr && heap.capacity == 8);

        assert(heap.pop() == 9);
        assert(heap.pop() == 6);
        assert(heap.len() == 2);
        assert(heap.peek() == 5);
        assert(heap.data != nullptr && heap.capacity == 8);

        assert(heap.pop() == 5);
        assert(heap.pop() == 2);
        assert(heap.len() == 0);
        assert(heap.data != nullptr && heap.capacity == 8);
    }
    {
        Heap<int, std::greater<int>> heap; // Min heap
        assert(heap.len() == 0);
        assert(heap.data == nullptr && heap.capacity == 0);

        heap.push(8);
        heap.push(3);
        heap.push(4);
        assert(heap.len() == 3);
        assert(heap.peek() == 3);
        assert(heap.data != nullptr && heap.capacity == 4);

        assert(heap.pop() == 3);
        assert(heap.len() == 2);
        assert(heap.peek() == 4);
        assert(heap.data != nullptr && heap.capacity == 4);
        
        assert(heap.pop() == 4);
        assert(heap.pop() == 8);
        assert(heap.len() == 0);
        assert(heap.data != nullptr && heap.capacity == 4);
    }
}

int main() {
    test_heap();
    std::cout << "All tests passed!\n";
}