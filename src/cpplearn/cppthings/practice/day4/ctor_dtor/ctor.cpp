#include <iostream>
using namespace std;

class Base {
    private:
    int x;
    public:
    Base(int a) : x(a) {
        cout << "Base ctor" << endl;
    };
    ~Base(){
        cout << "Base dtor" << endl;
    };
};
class Device : Base {
    private:
    int y;
    public:
    Device(int a, int b) : Base(a) , y(b) {
        cout << "Device ctor" << endl;
    };
    ~Device(){
        cout << "Device dtor" << endl;
    }
};

int main(int argc, char* argv[]){
    Device device{1,2};
    // Device devices = Device(3,4);

    return 0;
}
