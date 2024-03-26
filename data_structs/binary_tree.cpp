#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

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

    bool find(T val) const {
        return tree_search(root, val);
    }

    bool insert(T val) {
        if (!root) {
            root = new TreeNode<T>{val, nullptr, nullptr};
            tree_size ++;
            return true;
        }
        return tree_insert(root, val);
    }

    bool remove(T val) {
        if (!root) {
            return false;
        }
        return tree_remove(&root, val);
    }

private:
    bool tree_search(TreeNode<T>* node, T val) const {
        if (!node) {
            return false;
        }
        return node->val == val || tree_search(node->left, val) || tree_search(node->right, val);
    }

    bool tree_insert(TreeNode<T>* node, T val) {
        if (val > node->val) {
            if (!node->right) {
                node->right = new TreeNode<T>{val, nullptr, nullptr};
                tree_size ++;
                return true;
            }
            return tree_insert(node->right, val);
        } else if (val < node->val) {
            if (!node->left) {
                node->left = new TreeNode<T>{val, nullptr, nullptr};
                tree_size ++;
                return true;
            }
            return tree_insert(node->left, val);
        }
        return false;
    }

    bool tree_remove(TreeNode<T>*& node, T val) {
        // Check left and right subtrees for value
        if (val > node->val) {
            if (!node->right) {
                return false;
            }
            return tree_remove(node->right, val);
        } else if (val < node->val) {
            if (!node->left) {
                return false;
            }
            return tree_remove(node->left, val);
        }

        // Replace node with left subtree or right subtree
        if (!node->right) {
            TreeNode<T>* next = node->left;
            delete node;
            node = next;

            tree_size --;
            return true;
        } else if (!node->right->left) {
            TreeNode<T>* next = node->right;
            next->left = node->left;
            delete node;
            node = next;

            tree_size --;
            return true;
        }

        // Extract leftmost node in right subtree
        TreeNode<T>* parent = node->right;
        while (parent->left->left) {
            parent = parent->left;
        }
        TreeNode<T>* next = parent->left;
        parent->left = parent->left->right;

        // Replace node with extracted node
        next->left = node->left;
        next->right = node->right;
        delete node;
        node = next;

        tree_size --;
        return true;
    }

    friend void test_binary_tree();
};

template<typename T>
void check_tree_ordering(TreeNode<T>* node) {
    if (!node) {
        return;
    }
    if (node->left) {
        assert(node->left->val < node->val);
        check_tree_ordering(node->left);
    }
    if (node->right) {
        assert(node->right->val > node->val);
        check_tree_ordering(node->right);
    }
}

template<typename T>
void check_tree_includes(const BinaryTree<T>& tree, const vector<T>& vals) {
    for (T val : vals) {
        assert(tree.find(val));
    }
}

template<typename T>
void check_tree_excludes(const BinaryTree<T>& tree, const vector<T>& vals) {
    for (T val : vals) {
        assert(!tree.find(val));
    }
}

void test_binary_tree() {
    BinaryTree<int> tree;
    assert(tree.size() == 0);
    check_tree_excludes(tree, {6, 2, 9, 3, 7, 4, 10, 0, 15});
    assert(tree.root == nullptr);

    tree.insert(6);
    assert(tree.size() == 1);
    check_tree_includes(tree, {6});
    check_tree_excludes(tree, {2, 9, 3, 7, 4, 10, 0, 15});

    tree.insert(2);
    tree.insert(9);
    assert(tree.size() == 3);
    check_tree_includes(tree, {6, 2, 9});
    check_tree_excludes(tree, {3, 7, 4, 10, 0, 15});
    check_tree_ordering(tree.root);

    tree.insert(3);
    tree.insert(7);
    tree.insert(4);
    tree.insert(10);
    assert(tree.size() == 7);
    check_tree_includes(tree, {6, 2, 9, 3, 7, 4, 10});
    check_tree_excludes(tree, {0, 15});
    check_tree_ordering(tree.root);
}

int main() {
    test_binary_tree();
    std::cout << "All tests passed!\n";
}