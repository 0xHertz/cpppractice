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
**不是很懂**
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
