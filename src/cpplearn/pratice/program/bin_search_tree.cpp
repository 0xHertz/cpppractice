#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>

using namespace std;
typedef struct BinTree{
    int data;
    struct BinTree* left;
    struct BinTree* right;
} b_tree;

namespace tree {
    b_tree* create_node(int data){
        try {
            b_tree* new_node = (b_tree*) malloc(sizeof(b_tree));
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            return new_node;
        } catch (const std::bad_alloc& e) {
            cout << e.what() << endl;
            exit(1);
        };
    }
}


// 示例插入
b_tree* insert_node(b_tree* root, int data){
    if (root == NULL) {
        return tree::create_node(data);
    }else if (data <= root->data) {
        root->left = insert_node(root->left, data);
    }else {
        root->right = insert_node(root->right, data);
    }
    return root;
}

// 插入，我写的
void m_insert_node(b_tree** root, int data){
    b_tree* cur = *root;
    b_tree* prev = NULL;
    // 找到插入位置
    while (cur != NULL) {
        prev = cur;
        if (data <= cur->data) {
            cur = cur->left;
        }else if (data > cur->data) {
            cur = cur->right;
        }
    }
    // 插入
    if (data <= prev->data) {
        prev->left =  tree::create_node(data);
    }else{
        prev->right =  tree::create_node(data);
    }
}

// 示例输出
void print_tree(b_tree* root){
    if (root != NULL) {
        print_tree(root->left);
        cout << root->data << " < ";
        print_tree(root->right);
    }
}

// 释放空间
void free_tree(b_tree* root){
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
    }
}

void bin_search_tree_c17(){
    b_tree* root = tree::create_node(50);
    cout << root << endl;
    insert_node(root, 30);
    insert_node(root, 20);
    insert_node(root, 40);
    insert_node(root, 60);
    // m_insert_node(&root, 35);
    insert_node(root, 10);

    print_tree(root);
    free_tree(root);
}

typedef struct Node {
    int data;
    std::unique_ptr<Node> left, right;
    // 构造函数
    Node(int value) : data(value) {}
    // 成员函数
    void print_data(){
        std::cout << "the value of this node is " << data << endl;
    }
} c20_node;
class BinaryDearchTree{
    public:
    BinaryDearchTree() = default;
    // 循环
    std::unique_ptr<c20_node> insert_node_loop(std::unique_ptr<c20_node> root, int value){
        if (!root) {
            return std::make_unique<c20_node>(value);
        }
        c20_node* cur = root.get();
        c20_node* prev = nullptr;
        // 查找插入位置
        while (cur) {
            // 暂存当前指针
            prev = cur;
            if (value < cur->data) {
                cur = cur->left.get();
            }else {
                cur = cur->right.get();
            }
        }
        // 插入
        if (value < prev->data) {
            prev->left = std::make_unique<c20_node>(value);
        }else {
            prev->right = std::make_unique<c20_node>(value);
        }
        return root;
    }
    // 递归
    std::unique_ptr<c20_node> insert_node_recursion(std::unique_ptr<c20_node> root, int value){
        if (!root) {
            return std::make_unique<c20_node>(value);
        }
        if (value < root->data) {
            root->left = insert_node_recursion(std::move(root->left), value);
        } else if (value > root->data) {
            root->right = insert_node_recursion(std::move(root->right), value);
        }
        return root;
    }
    // 递归遍历
    void inorder_traversal_recursion(c20_node* root){
        if (root) {
            inorder_traversal_recursion(root->left.get());
            std::cout << root->data << " ";
            inorder_traversal_recursion(root->right.get());
        }
    }
    // 循环遍历
    void inorder_traversal_loop(c20_node* root){
        c20_node* cur = root;
        c20_node* print_ptr = nullptr;
        std::stack<c20_node*> stack_node;
        while (cur->left) {
            stack_node.push(cur);
            cur = cur->left.get();
        }
        while (!stack_node.empty()) {
            print_ptr = stack_node.top();
            stack_node.pop();
            cout << print_ptr->data << "-> ";
            if (print_ptr->right) {
                stack_node.push(print_ptr->right.get());
            }
        }
    }
    std::unique_ptr<c20_node> root = nullptr;
};
void bin_search_tree_c20(){

}

void binSearchTree(){
    bin_search_tree_c17();
    bin_search_tree_c20();
}
