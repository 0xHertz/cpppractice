#include <iostream>
using namespace std;

class A{
    private:
    int a;
    public:
    A(int a) : a(a) {}
    int getA() {
        cout << "non-const getA()" << endl;
        return a;
    }
    int getA() const {
        cout << "const getA()" << endl;
        return a;
    }
};

int main(){
    // 非const对象调用所有成员函数
    A a(10);
    // const对象只能调用const成员函数
    const A b(20);
    a.getA(); // non-const getA()
    b.getA(); // const getA()
    return 0;
}
