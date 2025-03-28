## 现代cpp特性
### Variadic Templates可变参数模板
数量不定的模板参数
### nullptr and nullptr_t
[示例代码](./mordencpp/nullptr.cpp)
### auto
[示例代码](./mordencpp/auto.cpp)
### lambda
[示例代码](./mordencpp/lambda.cpp)
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
[示例代码](./mordencpp/auto.cpp)
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
### Rvalue references 右值引用
Rvalue references（右值引用）是 C++11 引入的一种新特性，它允许我们区分左值（lvalue）和右值（rvalue），并且可以更高效地处理临时对象。右值引用的主要用途是实现移动语义（move semantics）和完美转发（perfect forwarding），从而提高程序的性能。
#### 左值（Lvalue）和右值（Rvalue）

- **左值（Lvalue）**：表示一个在内存中有确定存储位置的对象，可以取地址。例如，变量、数组元素、对象的成员等。
- **右值（Rvalue）**：表示一个临时对象或字面量，通常不能取地址。例如，字面量、临时对象、表达式的结果等。

#### 右值引用（Rvalue References）

右值引用使用双引用符号 `&&` 来声明。它可以绑定到右值，但不能绑定到左值。

[示例代码](./mordencpp/rvalue.cpp)
#### 移动语义（Move Semantics）
移动语义允许我们通过移动资源（如内存、文件句柄等）而不是复制资源来提高程序的性能。移动构造函数和移动赋值运算符是实现移动语义的关键。
[示例代码](./mordencpp/move_sem.cpp)
涉及到`拷贝构造函数`，`移动构造函数`，`拷贝赋值运算符`，`移动赋值运算符`

#### 完美转发
解决了在编写泛型代码时，如何正确地传递和处理参数的问题，特别是在处理右值引用和移动语义时
完美转发允许我们将函数参数完美地转发给另一个函数，而**不改变参数的左值或右值属性**。`std::forward` 是实现完美转发的关键。

[示例代码](./mordencpp/forward.cpp)

### move aware class 移动感知类
是指那些支持移动语义的类。这些类通过实现移动构造函数和移动赋值运算符来支持移动操作，从而能够高效地处理资源的转移。
在传统的复制语义中，复制一个对象通常涉及分配新内存并复制数据，这可能是一个昂贵的操作。移动语义通过移动资源而不是复制资源，避免了这些昂贵的操作，提高了程序的性能。
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
>     MyClass obj3 = std::move(obj1); // 移动构造，将 obj1 的资源移动到 obj3
>     obj2 = obj3; // 拷贝赋值
>     obj3 = std::move(obj2); // 移动赋值
>
>     return 0;
> }
> ```
* =delete可以使用在任何函数(构造函数，普通函数，析构函数)身上,而=default不可以使用在普通函数上
### type alias 类型别名
两种方式：C++ 提供了两种创建类型别名的方法：`typedef` 和 `using`，两者的功能是一样的，只是语法不同。
示例一
```cpp
// 第一种使用
// type alias
// 等价于typedef void(*func)(int, int);
using fun=void (*)(int, int);
```
示例二
```cpp
template<typename T>
struct MyAlloc {
    using value_type = T;
    // 这行代码使用 `using` 关键字为模板参数 `T` 创建了一个类型别名 `value_type`。这意味着在 `MyAlloc` 结构体中，`value_type` 是 `T` 的别名。换句话说，`value_type` 和 `T` 是同一种类型
};
```
### Alias Typedefs别名模板
C++11 引入了别名模板（Alias Templates）功能，允许为模板定义别名。别名模板可以用于简化模板的使用，提高代码的可读性。
```cpp
#include <vector>

using namespace std;

// 不可以对alias template做偏特化或全特化
template<typename T>
using Vec=vector<T, allocator<T>>;  // alias template using新用法
//# define Vec<T> template<typename T> vector<T, allocator<T>> // 使用宏不行
// typedef vector<int, allocator<int>> Vec;   // typedef也无法做到,没法指定模板参数
int main() {
    Vec<int> col;
// 如果使用宏上述会被替换为template<typename int> vector<int, allocator<int>>  error 不是我们想要的
    return 0;
}
```
### 模板模板参数Template Template Parameters
```cpp
//
// Created by light on 19-11-3.
//
#include <iostream>
#include <list>

using namespace std;
// template template parameter 模板模板参数，将模板作为模板参数
template<typename T, template<typename U> class Container>
class XCls {
private:
    Container<T> c;
};

// alias template
template<typename T>
using Lst = list<T>;

int main() {
//    XCls<string, list> mylist1;   // error
    XCls<string, Lst> mylist2;
    return 0;
}
```
### noexcept
`noexcept` 是 C++11 引入的一个关键字，用于指定函数是否不会抛出异常。它可以用于函数声明、函数定义和 lambda 表达式中。
```cpp
void func() noexcept;
void func() noexcept(true);  // 等价于 noexcept
void func() noexcept(false); // 表示函数可能抛出异常
```
```cpp
auto lambda = []() noexcept {
    // lambda body
};
```
`noexcept` 还可以作为一个运算符，用于检查表达式是否会抛出异常。它返回一个布尔值。
```cpp
int a = 10;
int b = 0;
bool is_noexcept = noexcept(a / b); // 返回 false
```
`noexcept` 关键字还可以接受一个布尔表达式，用于条件性地指定函数是否不会抛出异常。
```cpp
template <typename T>
void func(T t) noexcept(noexcept(t())) {
    t();
}
```
`func` 函数模板接受一个布尔表达式 `noexcept(t())`，表示如果 `t()` 不会抛出异常，则 `func` 也不会抛出异常。
### override and final
用于增强虚函数的行为和接口的明确性。它们帮助开发者更好地管理继承和多态，防止意外的错误
#### override
`override` 关键字用于显式地指定一个虚函数是重写基类中的虚函数。它可以帮助编译器检查函数签名是否正确匹配基类中的虚函数，从而防止意外的错误。
```cpp
class Base {
public:
    virtual void foo() const {
        std::cout << "Base::foo" << std::endl;
    }

    virtual void bar(int) {
        std::cout << "Base::bar" << std::endl;
    }
};

class Derived : public Base {
public:
    // 正确重写基类的虚函数
    void foo() const override {
        std::cout << "Derived::foo" << std::endl;
    }

    // 错误：函数签名不匹配基类的虚函数
    // void bar(double) override {
    //     std::cout << "Derived::bar" << std::endl;
    // }

    // 正确重写基类的虚函数
    void bar(int) override {
        std::cout << "Derived::bar" << std::endl;
    }
};
```
#### `final`
`final` 关键字用于防止类或虚函数被进一步继承或重写。它可以用于类声明或虚函数声明。
用于虚函数
```cpp
// Base类
virtual void bar() const final {
    std::cout << "Base::bar" << std::endl;
}
// Device类
// 错误：不能重写被 final 修饰的虚函数
// void bar() const override {
//     std::cout << "Derived::bar" << std::endl;
// }
```
用于类声明
```cpp
class Base final {
    // 类声明被 final 修饰，不能被继承
};
// 错误：不能继承被 final 修饰的类
// class Derived : public Base {
// };
```
### decltype
[参考](./basethings.md)的decltype章节

### 容器-结构与分类
[示例代码/src/cpplearn/stl]()
**序列式容器**包括：
> array（C++2.0 新引入）、vector、deque、list、forward_list（C++2.0 新引入）

**关联式容器**包括：
> set/multiset、map/multimap

无序容器（C++2.0 新引入，更换原先 hash_xxx 为 unordered_xxx）包括:
> unordered_map/unordered_multimap、unordered_set/unordered_multiset
### hash函数
[示例代码](./mordencpp/hash.cpp)
### tuple元组
[示例代码](./mordencpp/tuple.cpp)
在 C++ 中，`std::tuple` 是一个标准库提供的模板类，用于存储多个不同类型的值。它类似于结构体，但更加通用和灵活，因为它可以存储任意数量和类型的元素。`std::tuple` 是在 C++11 标准中引入的，位于 `<tuple>` 头文件中。
