#include <iostream>
#include <memory>
#include <queue>
#include <vector>

using std::deque, std::vector;

template<typename T, template<typename V, typename A> typename C>
struct Container {
    C<T, std::allocator<T>> data;

    Container() {}

    void push(T val) {
        data.push_back(val);
    }

    size_t len() {
        return data.size();
    }
};

int main() {
    Container<int, vector> vec;
    vec.push(5);
    vec.push(10);
    std::cout << "Vector: " << vec.len() << "\n";

    Container<int, deque> queue;
    queue.push(5);
    queue.push(10);
    queue.push(15);
    std::cout << "Deque: " << queue.len() << "\n";
}