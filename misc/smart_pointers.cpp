#include <iostream>
#include <memory>

using std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr;

struct Test {
    int data;

    Test(int val): data{val} {}
};

template<typename T>
struct Wrapper {
    shared_ptr<T> ptr;

    Wrapper(const shared_ptr<T>& val): ptr{val} {}
    Wrapper(shared_ptr<T>&& val): ptr{std::move(val)} {}

    size_t get_count() {
        return ptr.use_count();
    }

    void view() {
        std::cout << "Wrapper data: " << ptr->data << "\n";
    }
};

void borrow(Test& test) {
    test.data = 6;
    std::cout << "Borrowed data: " << test.data << "\n";
}

int main() {
    unique_ptr<Test> owned_test = make_unique<Test>(5);
    std::cout << "Owned data: " << owned_test->data << "\n";
    borrow(*owned_test);
    std::cout << "Owned data: " << owned_test->data << "\n";
    std::cout << "\n";

    shared_ptr<Test> shared_test = make_shared<Test>(5);
    std::cout << "Initial count: " << shared_test.use_count() << "\n";
    Wrapper<Test> wrapper_1(shared_test);
    std::cout << "After copy count: "
        << shared_test.use_count() << " "
        << wrapper_1.get_count() << "\n";
    {
        Wrapper<Test> wrapper_2(std::move(shared_test));
        std::cout << "After move count: "
            << shared_test.use_count() << " "
            << wrapper_1.get_count() << " "
            << wrapper_2.get_count() << "\n";
    }
    std::cout << "After drop count: "
        << shared_test.use_count() << " "
        << wrapper_1.get_count() << "\n";
}