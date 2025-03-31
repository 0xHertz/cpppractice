#include <iostream>
using namespace std;

class A{
    public:
    A(){ cout << "A ing" << endl; }
    ~A(){ cout << "A ed" << endl; }
};
class B{
    public:
    B(){ cout << "B ing" << endl; }
    ~B(){ cout << "B ed" << endl; }
};
class C{
    public:
    C(){ cout << "C ing" << endl; }
    ~C(){ cout << "C ed" << endl; }
};
/* 先构造成员，再构造自身 */
class D : C{
    public:
    D(){ cout << "D ing" << endl; }
    ~D(){ cout << "D ed" << endl; }
    A a;
    B b;
    C c;
};
/* 输出
C ing
A ing
B ing
C ing
D ing
D ed
C ed
B ed
A ed
C ed
*/
int main(int argc, char* argv[]){
    D d;
    return 0;
}
