## basethings
### const
常类型是指使用类型修饰符**const**说明的类型，常类型的变量或对象的值是不能被更新的
* 必须在定义时初始化
* 被const修饰的变量想要被其他文件extern引用，必须在定义时**显式添加extern**关键字（常规变量默认可以被其他文件引用）
* const与指针的关系
> const 位于 * 左侧：指针指向的内容是常量，不能通过指针修改内容
> ```cpp
> const int *p = &a;
> int const *p = &a;
> // 例如
> const int *ptr;
> *ptr = 10; //error
> ```
> const 位于 * 右侧：指针是常量，不能指向其他内容，常指针
> ```cpp
> int * const p = &a;
> const int * const p = &a;
> // 例如
> int num=0;
> int * const ptr=&num; //const指针必须初始化！且const指针的值不能修改
> int * t = &num;
> *t = 1;// ok
> cout<<*ptr<<endl;
> ```
* const与函数的关系
> * const 修饰函数返回值：
> ```cpp
> const int func();
> const int *func(); // 指针指向的内容不变。
> int *const func(); // 指针本身不可变。
> ```
> * const 修饰函数参数：
> 传递过来的参数及指针本身在函数内不可变
> ```cpp
> // 值传递，本来就是形参，变不变**无意义**
> void func(const int a); // 传递的参数不可变
> void func(int *const var); // 指针本身不可变
> // 地址传递
> void func(const int *a); // 指针指向的内容不可变,如果函数体内的语句试图改动a的内容，编译器将指出错误
> // 引用(别名)传递
> void func(const int &a); // 传递的参数不可变
> ```
* const与类的关系
> * const 成员变量只能通过初始化列表进行初始化
> * const 对象只能调用const成员函数const MyClass constObj(30);
> const 成员函数指的是在函数声明和定义中都加上const关键字的成员函数，const成员函数不能修改类的成员变量，也不能调用非const成员函数
> ```cpp
> class A
> {
> public:
>     A(int a) : _a(a) {}
>     void func() const
>     {
>         // _a = 1; // error
>     }
>     void func()
>     {
>         // _a = 1; // ok
>     }
> private:
>     const int _a;
> };
> ```
### static
* 静态变量
1. 函数中的静态变量
静态局部变量在程序执行到该对象的声明处时被首次初始化，以后再次调用函数时不再进行初始化，直到程序结束才销毁，常用于需要存储先前函数状态的任何其他应用程序
> ```cpp
> void demo()
> {
>     // static variable
>     static int count = 0;
>     cout << count << " ";
>
>     // value is updated and
>     // will be carried to next
>     // function calls
>     count++;
> }
>
> int main()
> {
>     for (int i=0; i<5; i++)
>         demo();
>     return 0;
> }
> // 输出
> 0 1 2 3 4
> ```
2. 类中的静态变量
静态数据成员是类的所有对象中共享的成员，而不是某个对象的成员，静态数据成员在类的所有对象中是唯一的，对静态数据成员的引用不需要使用对象名，而是使用类名即可
对静态变量的引用可以通过类名::静态变量名或对象名.静态变量名
> ```cpp
> int Apple::i = 1;
> ```
* 静态对象
> ```cpp
> class Apple
> {
>     int i;
>     public:
>         Apple()
>         {
>             i = 0;
>             cout << "Inside Constructor\n";
>         }
>         ~Apple()
>         {
>             cout << "Inside Destructor\n";
>         }
> };
> // 非静态对象，仅在if语句块内有效
> int main()
> {
>     int x = 0;
>     if (x==0)
>     {
>         Apple obj;
>     }
>     cout << "End of main\n";
> }
> // 输出：Inside Constructor->Inside Destructor->End of main
> // 静态对象，整个程序有效
> int main()
> {
>     if (x==0)
>     {
>         Apple obj;
>     }
>     cout << "End of main\n";
> }
> // 输出：Inside Constructor->End of main->Inside Destructor
* 静态函数
1. 普通静态函数
好像无
2. 类中的静态函数
像类中的静态数据成员或静态变量一样，静态成员函数也不依赖于类的对象
我们被允许使用对象和'.'来调用静态成员函数。但建议使用类名和范围解析运算符调用静态成员
静态成员函数仅访问静态数据成员或其他静态成员函数，它们无法访问类的非静态数据成员或成员函数。
### 引用和指针
所以C++中的引用只是C++对指针操作的一个“语法糖”，在底层实现时C++编译器实现这两种操作的方法完全相同。
* 引用必须初始化，指针不必
> ```cpp
> int a = 10;
> int &b = a; // ok
> int &c; // error
> int *c; // ok
> ```
* 引用不能为NULL，指针可以
> ```cpp
> void test_p(int * p){
>     // 必须判断指针是否为空
>     if(p != null_ptr){
>         *p = 3;
>     }
> }
> void test_r(int & r){
>     // 引用不需要判断是否为空
>     r = 3;
> }
> ```
* 引用不能更换目标，指针可以
> ```cpp
> int a = 1;
> int b = 2;
>
> int &r = a;    //初始化引用r指向变量a
> int *p = &a;   //初始化指针p指向变量a
>
> p = &b;        //指针p指向了变量b
> r = b;         //引用r依然指向a，但a的值变成了b
> ```
### 宏
几种特殊符号
* #：将宏参数转换为字符串
> ```cpp
> #define str1(x) #x
> #define str2(x) printf("test s is:%s\n",#x)
> #define str3(x) printf("test s is:%s\n",x)
>
> str1(   abc   ) // 转化成abc,自动去掉前后空格
> str1(   abc   def  ) // 转化成abc def,自动去掉前后空格,并且中间空格保留一个
> str2(abc) // 输出 test s is:abc
> str3("abc") // 输出 test s is:abc
> ```
* ##：连接两个参数
> * 当用##连接形参时，##前后的空格可有可无。
> * 连接后的实际参数名，必须为实际存在的参数名或是编译器已知的宏定义。
> * 如果##后的参数本身也是一个宏的话，##会阻止这个宏的展开。
> ```cpp
> // 注意事项2
> #define expA(s) printf("前缀加上后的字符串为:%s\n",gc_##s)  //gc_s必须存在
> // 注意事项1
> #define expB(s) printf("前缀加上后的字符串为:%s\n",gc_  ##  s)  //gc_s必须存在
> #define gc_hello1 "I am gc_hello1"
> int main() {
>     // 注意事项1
>     const char * gc_hello = "I am gc_hello";
>     expA(hello);// 拼接成为gc_hello，存在
>     expB(hello1);// 拼接成为gc_hello1，存在
> }
> ```
* \：续行符
当定义的宏不能用一行表达完整时，可以用”\”表示下一行继续此宏的定义。
> ```cpp
> #define MAX(a,b) ((a)>(b) ? (a) \
>    :(b))
> int main() {
>     int max_val = MAX(3,6);
>     cout<<max_val<<endl;
> }
> ```
### this
this是一个指向当前对象的指针，this指针是所有成员函数的隐含参数，所有成员函数中都有一个this指针，指向调用该成员函数的对象
### inline
省略函数调用的开销，将函数体直接插入到调用处
用于函数定义（{}），而不是函数声明
> ```cpp
> int Max(int x, int y); // 声明时不加inline
> // 定义时加inline
> inline int Max(int x, int y)
> {
>     return (x > y) ? x : y;
> }
> ```
* 不宜使用内联的情况
> * 函数体过大
> * 函数中出现循环
* 在类中使用内联函数
> 头文件中声明方法
> ```cpp
> class A
> {
> public:
>     /**
>      * @brief 类中定义了的函数是隐式内联函数,声明要想成为内联函数，必须在实现处(定义处)加inline关键字。
>      * @param x
>      * @param y
>      */
>     void Foo(int x,int y){};/// 带花括号（声明+定义），类中函数定义即默认隐式内联函数！
>     void f1(int x); ///声明后，要想成为内联函数，必须在定义处加inline关键字。
> };
> ```
> 实现文件中方法
> ```cpp
> inline void A::f1(int x)
> {
>     cout << "f1" << endl;
> } ///定义处加inline关键字
> ```
* 虚函数可以是内联函数吗
  虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。（因为编译时不能确定运行时具体调用哪个多态函数）

> ```cpp
> #include <iostream>
> using namespace std;
> class Base
> {
> public:
>     inline virtual void who()
>     {
>         cout << "I am Base\n";
>     }
>     virtual ~Base() {}
> };
> class Derived : public Base
> {
> public:
>     inline void who()  // 不写inline时隐式内联
>     {
>         cout << "I am Derived\n";
>     }
> };
>
> int main()
> {
>     // 此处的虚函数 who()，是通过类（Base）的具体对象（b）来调用的，编译期间就能确定了，所以它可以是内联的，但最终是否内联取决于编译器。
>     Base b;
>     b.who();
>
>     // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能为内联。
>     /**
>     * 这里，`ptr`是一个指向`Base`的指针，
>     * 但它实际指向的是`Derived`对象。调用`ptr->who()`时，程序需要在运行时通过虚函数表查找`Derived`类的`who`函数。
>     * 这种查找过程无法在编译时完成，因此无法进行内联。
>     */
>     Base *ptr = new Derived();
>     ptr->who();
>
>     // 因为Base有虚析构函数（virtual ~Base() {}），所以 delete 时，会先调用派生类（Derived）析构函数，再调用基类（Base）析构函数，防止内存泄漏。
>     delete ptr;
>     ptr = nullptr;
>
>     system("pause");
>     return 0;
> }
> ```
### sizeof
sizeof是一个运算符，用于计算数据类型或变量的大小，单位是字节
常见数据类型大小：
> * char：1
> * short：2
> * int：4
> * long：4
> * long long：8
> * float：4
> * double：8
> * long double：12
> * 指针：4（32位系统），8（64位系统）
> * 引用：和被引用对象的大小相同
> * 空类：1
* 类
> * 空类的大小为1字节
> * 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。
> * 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小。
> * 普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小
> * 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(32位操作系统4字节，64位操作系统 8字节)！
### virtual
#### 虚函数
虚函数是在基类中使用关键字virtual声明的函数，它在派生类中可以被重写，实现多态性
> ```cpp
> class Base
> {
> public:
>     virtual void show(int info = 0)
>     {
>         cout << "Base" << info << endl;
>     }
> };
> class Derived : public Base
> {
> public:
>     void show(int info = 1)
>     {
>         cout << "Derived" << info << endl;
>     }
> };
> class Derived2 : public Base
> {
> public:
>     void show(int info = 2)
>     {
>         cout << "Derived2" << info << endl;
>     }
> };
> ```
* 虚函数与运行时多态
虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型
> ```cpp
> Base *items[] = {new Base, new Derived, new Derived2};
> for (int i = 0; i < 3; i++)
> {
>     items[i]->show();
> } // 输出 Base 0 \n Derived 0 \n Derived2 0
> ```
* 虚函数的默认参数
虚函数的默认参数是静态绑定的，即在编译时就确定了，而不是动态绑定的，但是虚函数本身是动态绑定的，默认参数的使用需要看指针或者引用本身的类型，而不是对象的类型。
> ```cpp
> Device *d = new Device();
> d->show(); // 输出 Device 1
> Base *b = d;
> b->show(); // 输出 Device 0
> ```
#### 可不可以
* 静态函数可以是虚函数吗
静态函数不能是虚函数，因为静态函数不属于任何对象，而虚函数是动态绑定的，需要通过对象来调用
* 构造函数可以是虚函数吗
构造函数不能是虚函数，因为构造函数是在对象创建时调用的，而虚函数是在对象创建后调用的
* 析构函数可以是虚函数吗
析构函数可以是虚函数，因为析构函数是在对象销毁时调用的，而虚函数是在对象销毁前调用的
* 虚函数可以是私有函数吗
基类的指针指向派生类对象，调用的是派生类的虚函数，此时派生类的虚函数是私有的，但是可以被调用
#### 纯虚函数和抽象类
纯虚函数：没有函数体的虚函数，在声明时在函数后面加上=0
抽象类：包含纯虚函数的类
* 纯虚函数
构造函数不能是虚函数，而析构函数可以是虚析构函数。
> ```cpp
> virtual void show() = 0; // 纯虚函数
> ```
* 抽象类
抽象类只能作为基类来派生新类使用，不能创建抽象类的对象,抽象类的指针和引用->由抽象类派生出来的类的对象！
如果一个类从抽象类派生而来，它必须实现了基类中的所有纯虚函数，才能成为非抽象类。
### volatile
防止代码被编译器优化，举例说明：
* 一个例子：并行设备的硬件寄存器
> 并行设备的硬件寄存器（如状态寄存器）。 假设要对一个设备进行初始化，此设备的某一个寄存器为0xff800000。
> ```cpp
> int  *output = (unsigned  int *)0xff800000; //定义一个IO端口；
> int   init(void)
> {
>     int i;
>     for(i=0;i< 10;i++)
>     {
>     *output = i;
>     }
> }
> ```
> 经过编译器优化后，编译器认为前面循环半天都是废话，对最后的结果毫无影响，因为最终只是将output这个指针赋值为 9，所以编译器最后给你编译编译的代码结果相当于：
> ```cpp
> int  init(void)
> {
>     *output = 9;
> }
> ```
> 如果你对此外部设备进行初始化的过程是必须是像上面代码一样顺序的对其赋值，显然优化过程并不能达到目的。反之如果你不是对此端口反复写操作，而是反复读操作，其结果是一样的，编译器在优化后，也许你的代码对此地址的读操作只做了一次。然而从代码角度看是没有任何问题的。这时候就该使用volatile通知编译器这个变量是一个不稳定的，在遇到此变量时候不要优化。
* 一个例子：中断服务程序
> ```cpp
> static int i=0;
> int main()
> {
>     while(1)
>     {
>     if(i) dosomething();
>     }
> }
> /* Interrupt service routine */
> void IRS()
> {
>     i=1;
> }
> ```
> 上面示例程序的本意是产生中断时，由中断服务子程序IRS响应中断，变更程序变量i，使在main函数中调用dosomething函数，但是，由于编译器判断在main函数里面没有修改过i，因此可能只执行一次对从i到某寄存器的读操作，然后每次if判断都只使用这个寄存器里面的“i副本”，导致dosomething永远不会被调用。如果将变量i加上volatile修饰，则编译器保证对变量i的读写操作都不会被优化，从而保证了变量i被外部程序更改后能及时在原程序中得到感知。
* 一个例子：多线程中共享的变量
防止编译器优化后，将变量从内存保存到寄存器中，导致多线程中共享的变量不同步，使用volatile修饰变量，保证每次读取都是从内存中读取
> ```cpp
> volatile  bool bStop=false;  //bStop 为共享全局变量
> //第一个线程
> void threadFunc1()
> {
>     ...
>     while(!bStop){...}
> }
> //第二个线程终止上面的线程循环
> void threadFunc2()
> {
>     ...
>     bStop = true;
> }
> ```
如果不加volatile，编译器可能会将bStop的值缓存到寄存器中，导致threadFunc1中的while循环不会结束
### assert
是一个宏，用于调试程序，如果表达式为假，assert宏会终止程序执行，并在标准错误流中输出一条诊断信息
如果需要关闭assert，可以在程序开头include之前加上#define NDEBUG
> ```cpp
> #include <assert.h>
> int main()
> {
>     int x = 7;
>     assert(x == 5); // 输出：Assertion failed: (x == 5), function main, file assert.cpp, line 5.
>     return 0;
> }
> ```
### 位域
位域是一种数据结构，可以把数据以位的形式紧凑的储存，并允许程序员对此结构的位进行操作
缺点是位域的使用会使程序的可移植性降低，因为位域的长度和顺序是依赖于编译器的
> ```cpp
> struct _PRCODE
> {
>     // type field_name : width;
>     // type：数据类型，如int
>     // field_name：位域的名字
>     // width：位域的宽度,单位为位
>     unsigned int a : 2;
>     unsigned int b : 2;
>     unsigned int   : 3; // 未命名的位域，用于填充
>     unsigned int c : 8;
> };
> struct _PRCODE prcode;
> prcode.a = 2;
> prcode.b = 3;
> prcode.c = 255;
> ```
* 位域的大小：按照unsigned int的大小来分配，如32位系统中，unsigned int为4字节，所以位域的宽度不能超过32位，即使位域成员仅为1位，整个位域也要占用4字节
* 位域的对齐：如果位域成员超过了一个unsigned int的大小，那么下一个位域成员将从下一个unsigned int开始
> ```cpp
> struct _PRCODE
> {
>     unsigned int a : 30;
>     unsigned int b : 4;
>     unsigned int c : 8;
>     // 位域a+b占用了34位，超过了一个unsigned int的大小，所以会填充2位到a后，位域b从下一个unsigned int开始，整个位域大小为32+32=64位
> };
> // 也可以手动对齐，使用0位域填充
> struct _PRCODE
> {
>     unsigned int a : 30;
>     unsigned int   : 2;
>     unsigned int b : 4;
>     unsigned int   : 0; // 位域c从下一个unsigned int开始
>     unsigned int c : 8;
> };
> // 整个位域大小为32+32+32=96位
> ```
* 位域初始化
与结构体成员初始化一样
* 位域重映射
32位的位域可以重映射为int
> ```cpp
> struct box {
>     unsigned int ready:     2;
>     unsigned int error:     2;
>     unsigned int command:   4;
>     unsigned int sector_no: 24;
> }b1;
> int *p = (int *)&b1; // 重映射
> *p = 0; // 清除所有位域
> ```
### extern
#### c++调用c
由于编译结果不同，c++编译器会对函数名进行修饰，导致c++调用c函数时出现找不到函数的情况，例如int add(int a, int b)函数经过C++编译器生成.o文件后，add会变成形如add_int_int之类的, 而C的话则会是形如_add, 就是说：相同的函数，在C和C++中，编译后生成的符号不同。
> 引用C的头文件时，需要加extern "C"
> ```cpp
> //add.h
> #ifndef ADD_H
> #define ADD_H
> int add(int x,int y);
> #endif
> ```
>
> ```cpp
> //add.c
> #include "add.h"
>
> int add(int x,int y) {
>     return x+y;
> }
> ```
>
> ```cpp
> //add.cpp
> #include <iostream>
> extern "C" { #include "add.h" } // 引用C的头文件
> using namespace std;
> int main() {
>     add(2,3);
>    return 0;
> }
> ```
#### c调用c++
extern "C"在C中是语法错误，需要放在C++头文件中。
> ```cpp
> //add.h
> #ifndef ADD_H
> #define ADD_H
> extern "C" { int add(int x,int y); }
> #endif
> ```
>
> ```cpp
> //add.cpp
> #include "add.h"
>
> int add(int x,int y) {
>     return x+y;
> }
> ```
>
> ```cpp
> //add.c
> #include <stdio.h>
> #include "add.h"
> int main() {
>     printf("%d\n",add(2,3));
>    return 0;
> }
> ```
### struct
### union
### explicit（显式）
explicit 修饰构造函数时，可以防止隐式转换和复制初始化，只能用于直接初始化
> ```cpp
> #include <iostream>
>
> class MyClass {
> public:
>     explicit MyClass(int x) : value(x) {}
>
>     int getValue() const {
>         return value;
>     }
>
> private:
>     int value;
> };
>
> void printValue(const MyClass& obj) {
>     std::cout << "Value: " << obj.getValue() << std::endl;
> }
>
> int main() {
>     MyClass obj1(10); // 直接初始化，合法
>     printValue(obj1);
>
>     // MyClass obj2 = 20; // 错误：不能进行隐式转换
>     MyClass obj2 = MyClass(20); // 显式转换，合法
>     printValue(obj2);
>
>     return 0;
> }
> ```
explicit 修饰转换运算符时，可以防止隐式转换，但按语境转换除外
> ```cpp
> #include <iostream>
>
> class MyClass {
> public:
>     explicit operator int() const {
>         return value;
>     }
>
>     MyClass(int x) : value(x) {}
>
>     int getValue() const {
>         return value;
>     }
>
> private:
>     int value;
> };
> void printValue(int value) {
>     std::cout << "Value: " << value << std::endl;
> }
>
> int main() {
>     MyClass obj(10);
>     // int x = obj; // 错误：不能进行隐式转换
>     int x = static_cast<int>(obj); // 显式转换，合法
>     printValue(obj); // 错误：不能进行隐式转换
>     printValue(static_cast<int>(obj)); // 显式转换，合法
>
>     return 0;
> }
> ```
[示例代码](https://github.com/Light-City/CPlusPlusThings/blob/master/basic_content/explicit/explicit.cpp)
### friend
友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。
友元类的所有成员都是友元函数
### using
### 作用域
* 全局作用域符（::name）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为全局命名空间
* 类作用域符（class::name）：用于表示指定类型的作用域范围是具体某个类的
* 命名空间作用域符（namespace::name）:用于表示指定类型的作用域范围是具体某个命名空间的
### enum
枚举类型是一种用户自定义的数据类型，用于定义表示整数值的符号常量
* 解决枚举值冲突
> c中使用前缀来避免枚举值冲突
> 使用命名空间来避免枚举值冲突
> 使用结构体来避免枚举值冲突
> 使用枚举类来避免枚举值冲突
* 解决隐式类型转换
传统的枚举会隐式转换为int，而枚举类不会
> ```cpp
> enum class Color {red, green, blue}; // 等价于 enum class Color : int {red, green, blue};
> Color r = Color::red;
> int i = static_cast<int>(r); // 必须显式转换
> ```
可以前向声明枚举类型，但是不能定义枚举类型
> ```cpp
> // 前向声明
> enum class Week : char;
> // 定义
> enum class Week : char {Mon='mon' , Tue, Wed, Thu, Fri, Sat, Sun};
> // 显式类型转换
> Week day = Week::Mon;
> char c = static_cast<char>(day);
> ```
### decltype
decltype(var)返回表达式的数据类型
