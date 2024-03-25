#include <cassert>
#include <iostream>

template<typename T>
struct ListNode {
    T val;
    ListNode<T>* next;
};

template<typename T>
class LinkedList {
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t length;

public:
    LinkedList(): head{nullptr}, tail{nullptr}, length{0} {}

    size_t len() const {
        return length;
    }

    T get(size_t index) const {
        if (index >= length) {
            throw std::exception("index out of bounds");
        }
        ListNode<T>* current = head;
        for (size_t n = 0; n < index; n ++) {
            current = current->next;
        }
        return current->val;
    }

    void push_front(T val) {
        head = new ListNode<T>{val, head};
        if (!tail) {
            tail = head;
        }
        length ++;
    }

    void push_back(T val) {
        if (!head) {
            head = new ListNode<T>{val, nullptr};
            tail = head;
        } else {
            tail->next = new ListNode<T>{val, nullptr};
            tail = tail->next;
        }
        length ++;
    }

    void remove(size_t index) {
        if (index >= length) {
            throw std::exception("index out of bounds");
        }

        if (index == 0) {
            // Remove head node
            ListNode<T>* next = head->next;
            delete head;
            head = next;
            if (length == 1) {
                tail = nullptr;
            }
        } else {
            // Traverse list to node before removal index
            ListNode<T>* prev = head;
            for (size_t n = 0; n < index - 1; n ++) {
                prev = prev->next;
            }

            if (index < length - 1) {
                // Remove middle node
                ListNode<T>* next = prev->next->next;
                delete prev->next;
                prev->next = next;
            } else {
                // Remove tail node
                delete prev->next;
                prev->next = nullptr;
                tail = prev;
            }
        }

        length --;
    }

    friend void test_linked_list();
};

void test_linked_list() {
    LinkedList<int> list;
    assert(list.len() == 0);
    assert(list.head == nullptr && list.tail == nullptr);

    list.push_front(2);
    list.push_front(1);
    assert(list.len() == 2);
    assert(list.get(0) == 1 && list.get(1) == 2);
    assert(list.head != nullptr && list.tail != nullptr && list.tail->next == nullptr);

    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    assert(list.len() == 5);
    assert(list.get(0) == 1 && list.get(1) == 2);
    assert(list.get(2) == 3 && list.get(3) == 4 && list.get(4) == 5);
    assert(list.head != nullptr && list.tail != nullptr && list.tail->next == nullptr);

    list.remove(3);
    assert(list.len() == 4);
    assert(list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 3 && list.get(3) == 5);
    assert(list.head != nullptr && list.tail != nullptr && list.tail->next == nullptr);

    list.remove(0);
    assert(list.len() == 3);
    assert(list.get(0) == 2 && list.get(1) == 3 && list.get(2) == 5);
    assert(list.head != nullptr && list.tail != nullptr && list.tail->next == nullptr);

    list.remove(2);
    assert(list.len() == 2);
    assert(list.get(0) == 2 && list.get(1) == 3);
    assert(list.head != nullptr && list.tail != nullptr && list.tail->next == nullptr);

    list.remove(0);
    list.remove(0);
    assert(list.len() == 0);
    assert(list.head == nullptr && list.tail == nullptr);
}

int main() {
    test_linked_list();
    std::cout << "All tests passed!\n";
}