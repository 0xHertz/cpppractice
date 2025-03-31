#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <array>
#include <mutex>
#include <string>
#include <atomic>
#include <threads.h>
#include <thread>
#include <vector>
#include "human.cpp"

int double_number_a(int x){ return 2*x; };
void double_number_b(int* x){ *x *= 2; };
extern "C" void helloworld_C();

using namespace std;

void helloWorld(){
    std::cout << "Hello World" << std::endl;
}

void typePractice(){
    /* init */
    int a = 0; // C like
    int b {0}; // don't allow type change underline
    int c (0); // Contructor init
    char greet_a[6] = {'H','e','l','l','o','\n'};
    char greet_b[] = "Hello";
    char* greet_c = "Hello";
    std::string greet_d = "Hello"; // C++ string type
    /* output */
    std::cout << greet_c << std::endl;
}

void arrayPractice(){
    // C like
    int my_array[5];
    int my_array_b[] = {0,1,2,3,4};

    unsigned int len = sizeof(my_array) / sizeof(my_array[0]);
    for (int i = 0;i<len;i++){
        my_array[i] = my_array_b[i];
        std::cout << my_array[i] << std::endl;
    }

    std::cout << "++++++++++++ \t C++20 \t +++++++++++++" << std::endl;

    // C++20
    std::array<int ,5> my_array_c;
    for(int i = 0; i<my_array_c.size(); i++){
        my_array_c[i] = my_array[i];
        std::cout << my_array_c[i] << std::endl;
    }
}

void funcPractice(){
    int a = 3;
    std::cout << double_number_a(a) << std::endl;
    std::cout << a << std::endl;
    double_number_b(&a);
    std::cout << a << std::endl;
}

void loopPractice(){
    int num = 5;
    std::cout << "++++++++++++ \t for loop \t +++++++++++++" << std::endl;
    // for loop
    for( auto i = 0; i<num; i++){
        std::cout << i << std::endl;
    }
    std::cout << "++++++++++++ \t while loop \t +++++++++++++" << std::endl;
    // while loop
    while(num>=0){
        std::cout << num-- << std::endl;
    }
}

void gotoPractice(){
    int x;
    std::cin >> x;
    if (x < 3){
        goto cleanup;
    }else{
        cout << x << endl;
    }
    // Program code here
cleanup:
    cout << "end" << endl;
}

// 整数提升
void promotionPra(){
    // C like
    char a = 'A';
    // C++
    auto b = 'A';
    if (a < 'a') {
        cout << "less than" << endl;
    }else {
        cout << "more than" << endl;
    }
}

void argmPractice(int argc, char* argv[]){
    cout << argc << endl;
    while (argc) {
        // argv first argment is itself
        argc--;
        cout << argv[argc] << endl;
    }
    // can not run this loop
    for(auto i=0; i<argc; i++){
        cout << argv[i] << endl;
    }
}

// extern
void durofobject(){
    // C17
    extern int ex_num; // define anywhere else
    cout << ex_num << endl;
    static int b = 2; // hold value between invocation
    register int c=0; // store in CPU register for fast access
    auto d=0; // automatic storage duration

    // c++20
    extern const int ex_num_2;
    cout << ex_num_2 << endl;
    static int g;
    register int h;
    thread_local int i;
    helloworld_C();
}
// 类型限定符
void qualifiersPra(){
    // C++20
    const int a = 1; // can not be change
    std::atomic<int> b; // can only be modified by one thread at a time
    volatile int c; // 保证指令不被编译器优化，保证指令顺序
}

inline void inlineFunc(){
    // 不会发生函数调用开销；消除了堆栈上压入/弹出变量的开销；消除了返回调用的开销
    cout << "this is a inline function!" << endl;
}

void c20ifPratice(){
    // C++ 20 allow init x in if()
    if (int x = 4 ; x < 0) {
        cout << "if yes" << endl;
    }else{
        cout << "if not" << endl;
    }
}

/*
    在 C++ 中，结构体（struct）和类（class）本质上是一样的，
    唯一的区别是默认的成员访问权限不同。
    类的默认成员是 private 的，
    而结构体的默认成员是 public 的。
    因此，结构体也可以拥有构造函数、析构函数、成员函数等特性，和类没有区别。
    在C中没有以上这些特性
*/
struct S_User {
    int age;
    string name;
};
void structPratice(){
    struct S_User user;
    user.age = 18;
    user.name = "kechen";
    cout << "user name: " << user.name << endl;
    cout << "user age: " << user.age << endl;
}

// share the same addr, size of union object equals to the biggest item in union
// 默认访问控制符为public
// 可以含有构造函数、析构函数，没有成员函数
// 无法继承和被继承
union U_User {
    int age;
    char name[20];
};
void unionPratice(){
    union U_User user;
    cout << "Size of U_User: " << sizeof(user) << endl;
}

void bitOption(){
    // why use unsigned char? char take 1 byte
    unsigned char a = 5; // 00000101
    unsigned char b = 9; // 00001001
    // and
    cout << "a & b = " << (a & b) << endl; // 00000001
    // or
    cout << "a | b = " << (a | b) << endl; // 00001101
    // ^
    cout << "a ^ b = " << (a ^ b) << endl; // 00001100
    // not
    cout << "~a = " << (~a) << endl; // 11111010
    // left
    cout << "b << 1 = " << (b << 1) << endl; // 00010010
    // right
    cout << "b >> 1 = " << (b >> 1) << endl; // 00000100
}

// define unsigned char to byte for better readable
typedef unsigned char onebyte;
void typedefPratice(){
    onebyte a_byte = 'a';
    cout << a_byte << endl;
}

enum o_week {o_Sun, o_Mon, o_Tue, o_Wed, o_Thu, o_Fri, o_Sat};
//枚举常量Sun,Mon,Tue,Wed,Thu,Fri,Sat的值分别为0,1,2,3,4,5,6。
enum week {Sun=7, Mon=1, Tue, Wed, Thu, Fri, Sat};
//枚举常量Sun,Mon,Tue,Wed,Thu,Fri,Sat的值分别为7,1,2,3,4,5,6。
void enumPratice(){
    for(int i = o_Sun; i<=o_Sat; i++){
        cout << i << endl;
    }
}

// 可变参数
void varFuncPratice(int count,...){
    int total, i, temp;
    total = 0;
    va_list vars;
    va_start(vars, count);
    // 这个宏检索函数参数列表中类型为 type 的下一个参数
    int* ns = va_arg(vars,int*);
    for(int i=0; i < sizeof(ns); i++){
        cout << ns[i] << endl;
        total += ns[i];
    }
    cout << "sum is : " << total << endl;
    /*
    C/C++ 中的参数提升规则规定，
    所有的 char 和 short 类型在传递给可变参数函数时都会被提升为 int 类型
    按照char类型检索汇报错
   */
    // cout << va_arg(nums,char);
    cout << (char)va_arg(vars,int) << endl;
    va_end(vars);
}

void threadFunc(){
    std::cout << "Printing from Thread" << std::endl;
}
int c17_threadFunc(void* arg){
    std::cout << "Printing from Thread" << std::endl;
    return 0;
}
void threadPractice(){
    /* C17 */
    thrd_t thread_id;
    // create thread
    thrd_create(&thread_id, c17_threadFunc, NULL);
    // stop main thread , exec sub thread and wait for finish
    thrd_join(thread_id, NULL);
    cout << "C17 Thread End" << endl;

    /* C++20 */
    std::thread thread_obj(threadFunc);
    thread_obj.join();
    cout << "C++20 Thread End" << endl;
}

typedef struct data{
    // C17
    mtx_t c_17_mtx;
    // C++
    std::mutex c_20_mtx;
    int x;
} m_data;
void thread_mutex_func(m_data* d){
    // 拿到指针，就要使用->访问内部变量，或者先解引用，再使用.
    // mtx_lock(&(d->c_17_mtx));
    d->c_20_mtx.lock();
    d->x = 20;
    d->c_20_mtx.unlock();
    // 注意运算优先级
    // mtx_unlock(&d->c_17_mtx);
}
int c17_thread_mutex_func(void* arg){
    m_data* d = (m_data*) arg;
    mtx_lock((&(*d).c_17_mtx));
    // (*d).c_20_mtx.lock();
    (*d).x = 17;
    // (*d).c_20_mtx.unlock();
    mtx_unlock(&(*d).c_17_mtx);
    return 0;
}
void mutexPratice(){
    m_data d;
    // C17
    thrd_t c17_thread_id;
    thrd_create(&c17_thread_id, c17_thread_mutex_func, (void*) &d);
    thrd_join(c17_thread_id, NULL);


    // C++20
    thread thread_obj(thread_mutex_func,&d);
    thread_obj.join();

    cout << d.x << endl;
}

void heapPratice(){
    /* C17 */
    int* ptr_c17 = (int*) malloc(sizeof(int));
    if (ptr_c17) {
        free(ptr_c17);
    }

    /* C++20 */
    int* ptr_c20 = new int;
    delete ptr_c20;
}
void assertionsPra(){
    int i = 1;
    assert(i == 2);
}

/* 编译时需要添加-fmodules-ts来启用module功能 */
/* 编译时注意编译顺序，必须在import之前编译好module */
import Module_foo;
void modulePratice(){
    cout << Bar::ex_func() << endl;
}

/* 引用传递，引用是int&，指针是int*，引用相当于别名，必须指向同一个变量 */
void x_square(int& x){
    x *= x;
}
void referPratice(){
    int x = 3;
    x_square(x);
    cout << "x ^ 2 = " << x << endl;
}

void rangePratice(){
    int a[] = {23,34,4,6,6,5,3,4,2,42};
    for (auto item : a) {
        cout << item << endl;
    }

    vector<int> v = {23,4,4,5,34,3};
    for (const int& item : v) {
        cout << item << endl;
    }
}

namespace ns1 {
    void func(){
        cout << "hello ns1" << endl;
    }
}
namespace ns2 {
    void func(){
        cout << "hello ns2" << endl;
    }
}
void namespacePra(){
    ns1::func();
    ns2::func();
}

/* 继承 */
// public 指定继承的属性和方法为public，否则默认private，虽然是public但是父类中private还是private
class Teacher : public Human{
    // 私有属性(默认)
    // 也可以显示表示
    private:
    string school;

    // 继承构造函数
    public:
    Teacher():Human(){}
    Teacher(int a,string n) : Human(a, n){}
    // 自有构造函数
    // 构造函数体内赋值
    Teacher(int a,string n,string s){
        age = a;
        // can not assess father private val
        // name = n;
        school = s;
    }
    // 初始化列表赋值
    Teacher(string n) : Human(n) {}

    string get_school(){
        return school;
    }
    void set_school(string s){
        school = s;
    }

    // 重写虚函数
    void print_all(){
        cout << "all virtual func overridden" << endl;
    }
    // 重写父函数
    void print_sth(){
        cout << "sub sth virtual func overridden" << endl;
    }
    // 友元函数，声明在类内部，但定义在类外部
    // 在其范围之外定义的类的函数，但有权访问该类的所有私有和受保护成员
    friend void print_school(Teacher t);
    // 友元类,声明在类内部，但定义在类外部
    friend class Student;
    // 重载运算符
    Teacher operator+(const Teacher& t){
        Teacher teacher;
        teacher.age = this->age + t.age;
        return teacher;
    }
    // 作用域解析运算符
    void print_name(){
        // 可以使用作用域解析运算符 :: 来引用类的静态成员
        Human::sth = "hello";
        cout << Human::sth << endl;
        // 可以使用作用域解析运算符 :: 来使用类的静态函数
        Human::static_print_sth();
    }
};
class Student{
    public:
    void print_school(Teacher t){
        // 友元类可以访问私有成员
        cout << t.school << endl;
    }
};
// 可以使用作用域解析运算符 :: 来定义类的静态函数  和 构造函数
void Human::static_print_sth() {
    cout << Human::sth << endl;
}

void classPratice(){
    // 初始化方式：包括复制初始化（copy initialization）、直接初始化（direct initialization）和列表初始化（list initialization）
    // 复制初始化： 复制初始化使用等号 `=` 进行初始化。编译器会尝试找到一个合适的构造函数或转换函数来完成初始化
    // 直接初始化： 直接初始化使用括号 `()` 进行初始化。编译器会尝试找到一个合适的构造函数来完成初始化
    Teacher kechen(22,"kechen");
    // 列表初始化： 列表初始化使用花括号 `{}` 进行初始化。编译器会尝试找到一个合适的构造函数来完成初始化
    Teacher chen{18,"kechen"};
    // Human user(18,"kechen");
    Teacher ke(22,"kehcen");
    ke.set_school("xinghua");
    // 父类中的方法，被继承为public
    ke.print_sth();
    // cout << user.get_name() << " is " << user.get_age() << endl;
    cout << ke.get_name() << " is " << ke.get_age() << " work at " << ke.get_school() << endl;
}

void virtualFuncPra(){
    Teacher ke(22,"kehcen");
    ke.print_all();
    ke.print_sth();
}

void print_school(Teacher t){
    cout << t.school << endl;
}

void friendFuncPratice(){
    /* 定义在类作用域外的函数，可以访问类的内部变量 */
    Teacher ke(22,"ke");
    ke.set_school("xing");
    print_school(ke);
}

void operatorPra(){
    Teacher ke(22,"ke");
    Teacher chen(22,"chen");
    Teacher all;
    all = chen + ke;
    cout << all.get_age() << endl;
}

// 声明从元组、对或结构初始化的多个变量的便捷方法。通常用于捕获函数的多个返回值。
void structBindPra(){
    S_User user = {18,"kechen"};
    // this
    auto[a,b] = user;
    cout << a << endl;
    cout << b << endl;
}

void lambdaPratice(){
    int i=0,j=0;
    auto f_1 = [i,&j](int a, int& b) mutable -> bool {
        i = 20;
        j = 20;
        cout << "a: " << a << endl; // 30
        cout << "b: " << b << endl; // 20
        return (a>b) ? true : false;
    };
    i = 30, j = 10;
    cout << f_1(i, j) << endl; // true
    cout << i << " " << j << endl; //30 20
}

double divide(double a, double b){
    if (b == 0){
        // 抛出的异常类型要和捕获的相同
        throw string("Cannot divide by 0!\n");
    }
    return a/b;
}
void exceptionhandle(){
    double a;
    double b;
    cout << "please input two number: ";
    cin >> a >> b;
    cout << "a = " << a << ", b = " << b << endl;
    try{
        cout << "a/b = " << divide(a, b) << endl;
    } catch (const string err){  // 捕获string类型的异常
        cout << err << endl;
    }
}

void templatePra(){

}
