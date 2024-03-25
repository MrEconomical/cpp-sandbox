#include <cassert>
#include <iostream>

template<typename T>
struct ListNode {
    T val;
    ListNode<T>* next;
    ListNode<T>* prev;
};

template<typename T>
class DoublyLinkedList {
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t length;

public:
    DoublyLinkedList(): head{nullptr}, tail{nullptr}, length{0} {}

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
        if (!head) {
            head = new ListNode<T>{val, nullptr, nullptr};
            tail = head;
        } else {
            ListNode<T>* node = new ListNode<T>{val, head, nullptr};
            head->prev = node;
            head = node;
        }
        length ++;
    }

    void push_back(T val) {
        if (!head) {
            head = new ListNode<T>{val, nullptr, nullptr};
            tail = head;
        } else {
            ListNode<T>* node = new ListNode<T>{val, nullptr, tail};
            tail->next = node;
            tail = node;
        }
        length ++;
    }

    void insert(T val, size_t index) {
        if (index > length) {
            throw std::exception("index out of bounds");
        }

        // Add node at start or end
        if (index == 0) {
            push_front(val);
            return;
        } else if (index == length) {
            push_back(val);
            return;
        }

        // Traverse list to node before insertion index
        ListNode<T>* prev = head;
        for (size_t n = 0; n < index - 1; n ++) {
            prev = prev->next;
        }

        // Add middle node
        ListNode<T>* next = prev->next;
        ListNode<T>* node = new ListNode<T>{val, next, prev};
        prev->next = node;
        next->prev = node;

        length ++;
    }

    void remove(size_t index) {
        if (index >= length) {
            throw std::exception("index out of bounds");
        }

        if (index == 0) {
            // Remove node at start
            ListNode<T>* next = head->next;
            delete head;
            head = next;
            if (length == 1) {
                tail = nullptr;
            } else {
                head->prev = nullptr;
            }
        } else if (index == length - 1) {
            // Remove node at end
            ListNode<T>* prev = tail->prev;
            prev->next = nullptr;
            delete tail;
            tail = prev;
        } else {
            // Traverse list to removal node
            ListNode<T>* current = head;
            for (size_t n = 0; n < index; n ++) {
                current = current->next;
            }

            // Remove middle node
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        length --;
    }

    template<typename U>
    friend void check_link_consistency(const DoublyLinkedList<U>& list);
    friend void test_doubly_linked_list();
};

template<typename T>
void check_link_consistency(const DoublyLinkedList<T>& list) {
    if (list.len() == 0) {
        assert(list.head == nullptr && list.tail == nullptr);
    } else if (list.len() == 1) {
        assert(list.head != nullptr && list.head == list.tail);
        assert(list.head->prev == nullptr && list.head->next == nullptr);
    } else {
        assert(list.head != nullptr && list.tail != nullptr && list.head != list.tail);
        assert(list.head->prev == nullptr && list.tail->next == nullptr);

        ListNode<T>* prev = list.head;
        ListNode<T>* current = list.head->next;
        while (current) {
            assert(current->prev == prev);
            prev = current;
            current = current->next;
        }
    }
}

void test_doubly_linked_list() {
    DoublyLinkedList<int> list;
    assert(list.len() == 0);
    check_link_consistency(list);

    list.push_front(2);
    list.push_back(4);
    assert(list.len() == 2);
    assert(list.get(0) == 2 && list.get(1) == 4);
    check_link_consistency(list);

    list.insert(1, 0);
    list.insert(5, 3);
    assert(list.len() == 4);
    assert(list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 4 && list.get(3) == 5);
    check_link_consistency(list);

    list.insert(3, 2);
    assert(list.len() == 5);
    assert(list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 3 && list.get(3) == 4 && list.get(4) == 5);
    check_link_consistency(list);

    list.remove(4);
    assert(list.len() == 4);
    assert(list.get(0) == 1 && list.get(1) == 2 && list.get(2) == 3 && list.get(3) == 4);
    check_link_consistency(list);

    list.remove(0);
    assert(list.len() == 3);
    assert(list.get(0) == 2 && list.get(1) == 3 && list.get(2) == 4);
    check_link_consistency(list);

    list.remove(1);
    assert(list.len() == 2);
    assert(list.get(0) == 2 && list.get(1) == 4);
    check_link_consistency(list);

    list.remove(0);
    list.remove(0);
    assert(list.len() == 0);
    check_link_consistency(list);
}

int main() {
    test_doubly_linked_list();
    std::cout << "All tests passed!\n";
}