#include <cstdlib>
#include <iostream>

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

void binSearchTree(){
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
