#include <string>
#include <iostream>
using namespace std;
class Human {

    /* attbuit */
    public:
    int age;
    static std::string sth;
    private:
    string name;

    /* methods */
    public:
    string get_name(){
        return name;
    }
    int get_age(){
        return age;
    }
    static void static_print_sth();

    /* constructor & destructor */
    // 必须采用与类相同的名称，并且没有返回类型
    Human(){}
    // 构造函数内赋值
    Human(int a,string n){
        name = n;
        age = a;
    }
    // 初始化列表赋值
    Human(string n) : name(n) {}
    // 析构函数，采用与类相同的名称，前面带有~ ，并且没有返回类型
    ~Human(){}

    /* 虚函数，子类必须重写该方法 */
    // 添加 =0 后，指纯虚函数，该类变为抽象类，不可以new对象
    virtual void print_all() = 0;
    void print_sth(){
        cout << "father sth virtual func overridden" << endl;
    }
};
