# include <iostream>
using namespace std;

void f(int i){
    cout << "f(int i)" << endl;
}

void f(void * p){
    cout << "f(void * p)" << endl;
}

int main(){
    /* C中NULL被定义为void *
     * C++中NULL被定义为0
    */
    f(0); // 输出 f(int i)
    if(NULL==0)  cout<<"NULL==0"<<endl;
    // f(NULL); // ambiguous,因为NULL==0所以存在二义性 指针也可以是个int的地址
    // 而 `0` 可以被解释为整数 `0` 或者空指针 `0`。
    // 因此，当你调用 `f(NULL)` 时，编译器无法确定你是想调用 `f(int i)` 还是 `f(void * p)`

    /* C++11中nullptr被定义为nullptr_t
     * nullptr_t是一种数据类型，可以隐式转换为任意指针类型
     * 但是不能隐式转换为整数类型
    */
    f(nullptr); // 输出 f(void * p)
    return 0;
}
