#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(){
    // 变量推导
    auto a = 10;

    // 匿名函数推导，相当于function<int(int a, int b)>
    auto f = [](int a, int b) -> int {
        return a + b;
    };

    // 迭代器推导,相当于list<int>::iterator it
    list<int> l = {1,2,3,4,5};
    auto it = find(l.begin(),l.end(),10);

    vector<int> vec;
    // Range-based for loop 基于范围的for循环
    for (auto elem:vec) // pass  by value
        cout << elem << endl;
    for (auto& elem:vec) // pass by reference
        elem *= 2;
    return 0;
}
