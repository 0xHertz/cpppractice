#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;

void process(int& x){
    cout << "Lvalue reference: " << x << endl;
}
void process(int&& x){
    cout << "Rvalue reference: " << x << endl;
}

template <typename T>
void forwarder(T&& arg){
    /* forwarder 函数模板使用 std::forward 将参数 arg 完美地转发给 process 函数。 */
    process(std::forward<T>(arg));
}

int main(){
    int a = 10;
    forwarder(a);       // 调用左值引用版本
    forwarder(20);      // 调用右值引用版本
    forwarder(std::move(a)); // 调用右值引用版本

    return 0;
}
