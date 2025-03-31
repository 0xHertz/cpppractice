#include <iostream>
using namespace std;
class Base{
    private:
    int private_x;
    protected:
    int protetced_x;
    public:
    int public_x;

    void get_pri(){ cout << private_x << endl; };
    void get_pro(){ cout << protetced_x << endl; };
    void get_pub(){ cout << public_x << endl; };
};
/*
派生方式为protected的继承称为保护继承，在这种继承方式下，
基类的public成员在派生类中会变成protected成员，
基类的protected和private成员在派生类中保持原来的访问权限
*/
class Device : protected Base {
    public:
    void access_base(){
        // 类内部可访问
        get_pri(); // ok
        get_pro(); // ok
        get_pub(); // ok
    }
};

int main(int argc, char* argv[]){
    Device d;
    // 类对象不能访问
    // d.get_pri(); // can not access
    // d.get_pro(); // can not access
    // d.get_pub(); // can not access
    // 可通过类对象访问
    d.access_base();
    return 0;
}
