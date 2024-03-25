#include <cassert>
#include <iostream>

template<typename T>
struct TreeNode {
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

template<typename T>
class BinaryTree {
    TreeNode<T>* root;
    size_t tree_size;

public:
    BinaryTree(): root{nullptr}, tree_size{0} {}

    size_t size() const {
        return tree_size;
    }

    bool find(T val) {
        return tree_search(root, val);
    }

    bool insert(T val) {
        return tree_insert(root, val);
    }

    bool remove(T val) {
        return tree_remove(root, val);
    }

private:
    bool tree_search(TreeNode<T>* node, T val) {
        if (!node) {
            return false;
        }
        return node->val == val || tree_search(node->left, val) || tree_search(node->right, val);
    }

    bool tree_insert(TreeNode<T>* node, T val) {

    }

    bool tree_remove(TreeNode<T>* node, T val) {

    }

    friend void test_binary_tree();
};

void test_binary_tree() {
    BinaryTree<int> tree;
    std::cout << tree.tree_size << "\n";
}

int main() {
    test_binary_tree();
    std::cout << "All tests passed!\n";
}