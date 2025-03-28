#include <iostream>
#include<tuple>

using namespace std;

int main(){
    // 创建一个元组
    tuple<int, double, string> t1(1, 2.0, "hello");
    // 创建一个空元组
    tuple<int, double, string> t2;
    // 创建一个元组，元组的类型由编译器自动推导
    auto t3 = make_tuple(1, 2.0, "hello");

    // 获取元组的元素
    cout << get<0>(t1) << endl; // 1
    cout << get<1>(t1) << endl; // 2
    cout << get<2>(t1) << endl; // hello

    // 修改元组的元素
    get<0>(t1) = 10;
    get<1>(t1) = 20.0;
    get<2>(t1) = "world";

    // 比较两个元组
    cout << (t1 == t3) << endl; // 1

    // 元组的拆包
    int a;
    double b;
    string c;
    tie(a, b, c) = t1;
    cout << a << " " << b << " " << c << endl; // 10 20 world

    // 元组的拆包
    tie(a, ignore, c) = t1;
    cout << a << " " << c << endl; // 10 world

    // 元组的拆包
    tie(a, b, ignore) = t1;
    cout << a << " " << b << endl; // 10 20

    return 0;
}
