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
// 不写，默认private,基类所有成员变量和成员函数都为private
class Device : Base {};

int main(int argc, char* argv[]){
    Device d;
    // d.get_pri(); // can not access
    // d.get_pro(); // can not access
    // d.get_pub(); // can not access
    return 0;
}
