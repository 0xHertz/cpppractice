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
除了基类中private保持不变，其他都变为public
*/
class Device : public Base {};

int main(int argc, char* argv[]){
    Device d;
    d.get_pri(); // access
    d.get_pro(); // access
    d.get_pub(); // access
    return 0;
}
