#include <iostream>
using namespace std;

class A{
    public:
    void showMessage(){
        cout << "hello" << endl;
    }
};

class B : public A {};
class C : public A {};
class D : public B, public C {};
/*
 A
/ \
B  C
\ /
 D
*/

int main (int argc, char* argv[]){
    D d;
    // d.showMessage(); // error, D中有两份A，不知道调用哪个函数
    /*
    class B : virtual public A {};
    class C : virtual public A {};
    class D : public B, public C {};
    */
    // 改为虚继承即可解决
    // d.showMessage(); // ok

    return 0;
}
