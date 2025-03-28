/* C++11 引入了 lambda 表达式，使得在代码中定义匿名函数变得更加方便和简洁。
lambda 表达式可以捕获周围作用域中的变量，并且可以像普通函数一样调用。
下面是 lambda 表达式的基本语法和一些示例。 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v = {1,2,3,4,5};
    // 使用 lambda 表达式打印 v 中的元素
    for_each(v.begin(),v.end(),[](int n){
        cout << n << endl;
    });

    int x = 10;
    int y = 20;

    // 按值捕获 x 和 y
    auto lambda1 = [x, y]() {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    };
    lambda1();

    // 按引用捕获 x 和 y
    auto lambda2 = [&x, &y]() {
        x += 10;
        y += 10;
        std::cout << "x: " << x << ", y: " << y << std::endl;
    };
    lambda2();
    return 0;
}
