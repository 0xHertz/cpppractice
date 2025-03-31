#include <iostream>
using namespace std;
class Base{
    private:
    int private_x;
    public:
    int get_prix(){ return private_x; };
    void set_prix(int a){ private_x = a; }
};

class Device : public Base {
    private:
    int private_y;
    public:
    int get_priy(){ return private_y; };
    void set_priy(int a){ private_y = a; }
};

void f1(Base a, int x) { a.set_prix(x); }
void f2(Base *pA, int x) { pA->set_prix(x); }
void f3(Base &rA, int x) { rA.set_prix(x); }

int main(int argc, char* argv[]){
    Base base, *baseptr;
    Device device;

    base.set_prix(1);
    device.set_prix(2);

    //把派生类对象赋值给基类对象。
    /*
    当派生类对象 `device` 赋值给基类对象 `base` 时，
    发生了对象切片（object slicing）。
    对象切片是指当派生类对象赋值给基类对象时，
    派生类对象的特有部分（即派生类新增的成员变量和成员函数）会被切掉，只保留基类部分。
    1. `base` 对象的基类部分被 `device` 对象的基类部分覆盖。
    2. `device` 对象的派生类部分不会被复制到 `base` 对象中
    */
    cout << "把派生类对象赋值给基类对象" << endl;
    base = device;
    cout << base.get_prix() << endl;  // 2
    cout << device.get_prix() << endl; // 2
    base.set_prix(10);
    /* 修改 `base` 的 `private_x` 不会影响 `device`，因为在内存中它们是两个独立的对象。 */
    cout << base.get_prix() << endl; // 10
    cout << device.get_prix() << endl; // 2

    //把派生类对象的地址赋值给基类指针。
    /*
    指针 `baseptr` 可以访问 `device` 的基类部分，但不能访问派生类特有的部分
    */
    cout << "把派生类对象的地址赋值给基类指针" << endl;
    baseptr = &device;
    cout << baseptr->get_prix() << endl; // 2
    cout << device.get_prix() << endl; // 2

    //用派生类对象初始化基类对象的引用。
    /*
    引用 `baseref` 可以访问 `device` 的基类部分，但不能访问派生类特有的部分
    */
    cout << "用派生类对象初始化基类对象的引用" << endl;
    Base &baseref = device;
    baseref.set_prix(20);
    cout << baseref.get_prix() << endl; // 20
    cout << device.get_prix() << endl; // 20
    device.set_prix(30);
    cout << device.get_prix() << endl; // 30

    cout << "函数" << endl;
    /*
    - `f1` 函数通过值传递基类对象。传递的是对象的副本，对副本的修改不会影响原对象。
    - `f2` 函数通过指针传递基类对象。传递的是对象的地址，对指针指向对象的修改会影响原对象。
    - `f3` 函数通过引用传递基类对象。传递的是对象的引用，对引用的修改会影响原对象。
    */
    f1(device, 100);
    cout << device.get_prix() << endl; // 30
    f2(&device, 200);
    cout << device.get_prix() << endl; // 200
    f3(device, 300);
    cout << device.get_prix() << endl; // 300

    return 0;
}
