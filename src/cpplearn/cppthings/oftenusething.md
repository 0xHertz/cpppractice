## 惯用法
### 类初始化
* const成员的初始化只能在构造函数初始化列表中进行
* 引用成员的初始化也只能在构造函数初始化列表中进行
* 对象成员（对象成员所对应的类没有默认（无参）构造函数）的初始化，也只能在构造函数初始化列表中进行
#### const数据成员&引用成员
必须用初始化列表初始化，而不能通过赋值初始化
> ```cpp
> class Animal {
> public:
>     // 构造函数，这是不行的
>     Animal(int age,std::string name) {
>         std::cout << "Animal(int age) is called" << std::endl;
>     }
>     // 初始化列表，这是可以的
>     Animal(int age,std::string name):age_(age),name_(name) {
>         std::cout << "Animal(int age) is called" << std::endl;
>     }
> private:
>     int &age_;
>     const std::string name_; // const成员变量
> };
> ```
#### 对象成员（类的嵌套）
第一种： 使用初始化列表。
> ```cpp
> class Animal {
> public:
>     // 无参构造函数
>     Animal() {
>         std::cout << "Animal() is called" << std::endl;
>     }
>     // 构造函数初始化const引用成员
>     Animal(const Animal &) {
>         std::cout << "Animal (const Animal &) is called" << std::endl;
>     }
>     // 运算符重载
>     Animal &operator=(const Animal &) {
>         std::cout << "Animal & operator=(const Animal &) is called" << std::endl;
>         return *this;
>     }
>     // 析构函数
>     ~Animal() {
>         std::cout << "~Animal() is called" << std::endl;
>     }
> };
> ```
>
> ```cpp
> class Dog {
> public:
>     // 初始化列表
>     Dog(const Animal &animal) : __animal(animal) {
>         std::cout << "Dog(const Animal &animal) is called" << std::endl;
>     }
>
>     ~Dog() {
>         std::cout << "~Dog() is called" << std::endl;
>     }
> // Dog嵌套Animal
> private:
>     Animal __animal;
> };
> ```
>
> ```cpp
> int main() {
>     Animal animal;
>     std::cout << std::endl;
>     Dog d(animal);
>     std::cout << std::endl;
>     return 0;
> }
> ```
>
> 运行结果：
> ```
> Animal() is called
>
> Animal (const Animal &) is called
> Dog(const Animal &animal) is called
>
> ~Dog() is called
> ~Animal() is called
> ~Animal() is called
> ```
> 依次分析从上到下：
>
> main函数中Animal animal;调用默认构造。
>
> Dog d(animal);等价于：
> Animal __animal = animal;
> 实际上就是调用了拷贝构造，因此输出了：
>
> Animal (const Animal &) is called
> 再然后打印Dog的构造函数里面的输出。
> 最后调用析构，程序结束。

第二种：构造函数赋值来初始化对象。

> 构造函数修改如下：
> ```cpp
> Dog(const Animal &animal) {
>     __animal = animal;
>     std::cout << "Dog(const Animal &animal) is called" << std::endl;
> }
> ```
> 此时输出结果：
> ```
> Animal() is called
>
> Animal() is called
> Animal & operator=(const Animal &) is called
> Dog(const Animal &animal) is called
>
> ~Dog() is called
> ~Animal() is called
> ~Animal() is called
> ```
> 于是得出：
>
> 当调用Dog d(animal);时，等价于：
>
> 先定义对象，再进行赋值，因此先调用了默认构造，再调用=操作符重载函数。
>
> // 假设之前已经有了animal对象
> Animal __animal;
> __animal = animal;
小结

通过上述我们得出如下结论：

* 类中包含其他自定义的class或者struct，采用初始化列表，实际上就是创建对象同时并初始化
* 而采用类中赋值方式，等价于先定义对象，再进行赋值，一般会先调用默认构造，在调用=操作符重载函数。所以才会说基类或成员类中没有默认构造函数的，只能通过初始化列表进行初始化
### 枚举类替换命名空间
可以参考basethings.md中enum章节
### RAII 资源获取即初始化方法
消除垃圾收集器
在C语言中，有三种类型的内存分配:静态、自动和动态。
* 静态：代码中的h常数
* 自动：栈内存
* 动态：堆内存
本章主要讲一些内存分配和销毁的手动与自动化操作，例如C++提供的析构函数、uni指针、vector、string等类型
### copy&swap
从概念上讲，它通过使用拷贝构造函数的功能来创建数据的本地副本，然后使用交换功能获取复制的数据，将旧数据与新数据交换来工作。然后，临时副本将销毁，并随身携带旧数据。我们剩下的是新数据的副本。
### plmpl指向实现的指针
它将类的实现细节从对象表示中移除，放到一个分离的类中，并以一个不透明的指针进行访问。
例子：
> 通常的类：
> ```cpp
> class Widget {
> private:
>     int a;
>     int b;
> };
> ```
> 使用pimpl：
> ```cpp
> class Widget {
> private:
>     struct WidgetImpl;
>     WidgetImpl *pimpl;
> };
> ```
> 实现：
> ```cpp
> struct Widget::WidgetImpl {
>     int a;
>     int b;
> };
> ```
优点：
* 数据隐藏
* 降低二进制兼容性
* 减少编译时间
