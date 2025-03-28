## 现代cpp特性
### Variadic Templates可变参数模板
数量不定的模板参数
### nullptr and nullptr_t
[示例代码](./moremoderncpp/nullptr.cpp)
### auto
[示例代码](./moremoderncpp/auto.cpp)
### lambda
[示例代码](./moremoderncpp/lambda.cpp)
```cpp
[capture](parameters) -> return_type {
    // function body
}
```
```cpp
// 不带返回值的 lambda 表达式
[capture](parameters) {
    // function body
}
```
- `capture`：捕获列表，用于捕获外部作用域中的变量。
- `parameters`：参数列表，类似于普通函数的参数列表。
- `return_type`：返回类型，可以省略，编译器会自动推导。
- `function body`：函数体，包含要执行的代码
#### 捕获列表
捕获列表用于指定 lambda 表达式可以访问哪些外部变量。捕获列表可以包含以下内容：
- `[ ]`：不捕获任何变量。
- `[=]`：按值捕获所有外部变量。
- `[&]`：按引用捕获所有外部变量。
- `[x]`：按值捕获变量 `x`。
- `[&x]`：按引用捕获变量 `x`。
- `[=, &x]`：按值捕获所有外部变量，但按引用捕获变量 `x`。
- `[&, x]`：按引用捕获所有外部变量，但按值捕获变量 `x`。
### Uniform Initialization统一初始化
C++11 引入了统一初始化（Uniform Initialization）语法，使得初始化对象的方式更加一致和简洁。统一初始化使用大括号 `{}` 来初始化对象，可以用于初始化内置类型、类对象、数组、容器等。统一初始化不仅简化了语法，还可以避免一些潜在的错误。
统一初始化的基本语法如下：
```cpp
Type variable_name { initializer_list };
```
```cpp
int a = 5;      // 传统初始化
int b(5);       // 传统初始化
int c{5};       // 统一初始化
int d = {5};    // 统一初始化
```
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int value[]{1, 2, 3};       // initializer_list<T> 会关联一个array<T,n> 里面元素被编译器逐一分解传给函数
    vector<int> v{2, 3, 5};
    return 0;
}
```
### initializer_list初始化列表
与统一初始化的联系：**统一初始化可以触发 `std::initializer_list` 构造函数**：
- 当使用统一初始化语法 `{}` 初始化一个对象时，如果该对象的类有一个接收`std::initializer_list` 的构造函数，编译器会优先选择这个构造函数。
#### 示例

```cpp
#include <initializer_list>
#include <iostream>

class MyClass {
public:
    // 初始化列表构造函数
    MyClass(std::initializer_list<int> list) {
        for (auto elem : list) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyClass obj{1, 2, 3, 4, 5}; // 使用 initializer_list 进行初始化
    return 0;
}
```
###  显式指定接受多个参数的构造函数
[参考basethings.md](./basethings.md)中的explicit关键字
### Range-based for loop 基于范围的for语句
[示例代码](./moremoderncpp/auto.cpp)
C++11 引入了范围基于范围的 for 循环（Range-based for loop），它提供了一种简洁的方式来遍历容器或数组中的元素。范围基于范围的 for 循环使得代码更加简洁和易读，特别适用于需要遍历整个容器或数组的场景。
```cpp
for (declaration : expression) {
    // loop body
}
```
- `declaration`：用于声明循环变量，可以是值类型、引用类型或常量引用类型。
- `expression`：表示要遍历的容器或数组。
```cpp
#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // 使用范围基于范围的 for 循环遍历数组
    for (int n : arr) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
### delete and default functions
用于控制类的特殊成员函数（如构造函数、析构函数、拷贝构造函数、移动构造函数、拷贝赋值运算符和移动赋值运算符）的生成和行为。它们提供了一种简洁的方式来显式地指定这些成员函数的默认行为或禁用它们。
> 默认构造函数：
> - 如果类没有定义任何构造函数，编译器会自动生成一个默认构造函数。
> - 如果类定义了其他构造函数，但没有定义默认构造函数，编译器不会生成默认构造函数。
> - 如果类定义了默认构造函数，编译器不会生成默认构造函数。
> ```cpp
> className() = default;
> ```
> 拷贝构造函数：
> ```cpp
> className(const className &obj) = delete;
> ```
> 移动构造函数：
> ```cpp
> className(className &&obj) = default;
> ```
> 拷贝赋值运算符：
> ```cpp
> className &operator=(const className &obj) = default;
> ```
> 移动赋值运算符：
> ```cpp
> className &operator=(className &&obj) = delete;
> ```
> 析构函数：
> ```cpp
> ~className() = default;
> ```
> 使用
> ```cpp
> int main() {
>     MyClass obj1;
>     MyClass obj2 = obj1; // 拷贝构造
>     MyClass obj3 = std::move(obj1); // 移动构造
>     obj2 = obj3; // 拷贝赋值
>     obj3 = std::move(obj2); // 移动赋值
>
>     return 0;
> }
> ```
* =delete可以使用在任何函数(构造函数，普通函数，析构函数)身上,而=default不可以使用在普通函数上
