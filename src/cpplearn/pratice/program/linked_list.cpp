#include <cstddef>
#include <iostream>
#include <list>

using namespace std;
// 定义节点
#include <cstdlib>
typedef struct Node {
  int data;
  struct Node* next;
} d_node;

// 打包构造函数
d_node* create_node(int data){
    d_node* new_node = (d_node*) malloc(sizeof(d_node));
    if (new_node == NULL) {
        cout << "Memory allocation failed" << endl;
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 定义前插函数,我的实现,是错的
// d_node** m_push_front(d_node* cur, int data){
//     d_node* new_node = create_node(data);
//     new_node->next = cur;
//     return &new_node;
// }
// 前插函数，示例实现
void ex_push_front(d_node** headptr, int data){
    d_node* new_node = create_node(data);
    new_node->next = *headptr;
    *headptr = new_node;
}

// 定义后插函数,示例实现
void push_back(d_node** headptr, int data){
    d_node* new_node = create_node(data);
    if (*headptr == NULL) {
        *headptr = new_node;
        return;
    }
    // 遍历列表
    d_node* cur = *headptr;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = new_node;
}

void print_list(d_node** headptr){
    d_node* cur = *headptr;
    while (cur != NULL) {
        cout << cur->data << "->";
        cur = cur->next;
    }
    cout << "NULL" << endl;
}

// 释放空间
void free_list(d_node** headptr){
    d_node* cur = *headptr;
    d_node* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
        // free(prev);
    }
    // 避免悬空指针
    *headptr = NULL;
}


void linkedList(){
    // C17
    d_node* head = NULL;
    push_back(&head, 1);
    push_back(&head, 2);
    push_back(&head, 3);
    push_back(&head, 4);
    ex_push_front(&head, 5);
    print_list(&head);
    free_list(&head);

    // c++20
    std::list<int> c20_list;
    c20_list.push_back(1);
    c20_list.push_back(2);
    c20_list.push_back(3);
    c20_list.push_back(4);
    c20_list.push_front(5);
    for (auto it = c20_list.begin(); it != c20_list.end(); ++it) {
        cout << *it << "->";
    }
    cout << "NULL" << endl;
}
