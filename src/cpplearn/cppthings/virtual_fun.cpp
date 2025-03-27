#include<iostream>
using namespace std;
class Base
{
public:
    virtual void show(int info = 0)
    {
        cout << "Base" << info << endl;
    }
};
class Derived : public Base
{
public:
    void show(int info = 1)
    {
        cout << "Derived" << info << endl;
    }
};
class Derived2 : public Base
{
private:
    void show(int info = 2)
    {
        cout << "Derived2" << info << endl;
    }
};

int main(){
    // 虚函数动态绑定
    Base *item[] = {new Base(), new Derived(), new Derived2()};
    for(int i = 0; i < 3; i++)
    {
        item[i]->show();
    }

    // 虚函数参数默认值
    Derived *d = new Derived();
    d->show(); // 输出 Device 1
    Base *b = d;
    b->show(); // 输出 Device 0

    // 调用私有函数
    Base *b2 = new Derived2();
    b2->show(); // 输出 Device2 0
    return 0;
}
