#include <iostream>
using namespace std;
void process(int& x){
    cout << "Lvalue reference : " << x << endl;
}
void process(int&& x){
    cout << "Rvalue reference : " << x << endl;
}
int main(){
    int a = 10;
    process(a); // Lvalue reference
    process(20); // Rvalue reference
    /* 相当于20保留下来以供使用，否则每次调用后消失，每次调用时重新创建 */
    process(std::move(a)); // Rvalue reference，将 `a` 转换为右值。
}
