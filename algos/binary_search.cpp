#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

size_t lower_bound(const vector<int>& nums, int val) {
    size_t start = 0;
    size_t end = nums.size();
    while (start < end) {
        size_t mid = start + (end - start) / 2;
        if (nums[mid] < val) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return start;
}

size_t upper_bound(const vector<int>& nums, int val) {
    size_t start = 0;
    size_t end = nums.size();
    while (start < end) {
        size_t mid = start + (end - start) / 2;
        if (nums[mid] <= val) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return start;
}

int main() {
    vector<int> empty;
    assert(lower_bound(empty, 10) == 0);
    assert(upper_bound(empty, 10) == 0);

    vector<int> single{6};
    assert(lower_bound(single, 6) == 0);
    assert(upper_bound(single, 6) == 1);

    vector<int> even_len{2, 2, 2, 2};
    assert(lower_bound(even_len, 2) == 0);
    assert(upper_bound(even_len, 2) == 4);

    vector<int> odd_len{3, 3, 3, 3, 3};
    assert(lower_bound(odd_len, 3) == 0);
    assert(upper_bound(odd_len, 3) == 5);

    vector<int> unique{-2, 5, 6, 8, 12, 15, 17};
    assert(lower_bound(unique, 5) == 1);
    assert(upper_bound(unique, 5) == 2);
    assert(lower_bound(unique, 12) == 4);
    assert(upper_bound(unique, 12) == 5);

    vector<int> bounds{1, 6, 6, 7, 9};
    assert(lower_bound(bounds, 1) == 0);
    assert(upper_bound(bounds, 1) == 1);
    assert(lower_bound(bounds, 9) == 4);
    assert(upper_bound(bounds, 9) == 5);

    vector<int> duplicate{4, 4, 8, 10, 10, 10, 15, 15, 15, 15};
    assert(lower_bound(duplicate, 4) == 0);
    assert(upper_bound(duplicate, 4) == 2);
    assert(lower_bound(duplicate, 10) == 3);
    assert(upper_bound(duplicate, 10) == 6);
    assert(lower_bound(duplicate, 15) == 6);
    assert(upper_bound(duplicate, 15) == 10);

    vector<int> missing{-3, -1, 0, 4, 4, 4, 5, 10, 10, 11};
    assert(lower_bound(missing, 6) == 7);
    assert(upper_bound(missing, 6) == 7);
    assert(lower_bound(missing, 9) == 7);
    assert(upper_bound(missing, 9) == 7);

    vector<int> extreme{-7, -7, -2, 4, 5, 5, 8, 12, 14};
    assert(lower_bound(extreme, -20) == 0);
    assert(upper_bound(extreme, -20) == 0);
    assert(lower_bound(extreme, 20) == 9);
    assert(upper_bound(extreme, 20) == 9);

    std::cout << "All tests passed!\n";
}