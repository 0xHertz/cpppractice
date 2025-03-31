#include <iostream>
using namespace std;

int jiecheng(int x);

int main(int argc, char* argv[]){
    cout << "input x: ";
    int x;
    cin >> x;
    cout << "x! = " << jiecheng(x) << endl;
    return 0;
}

int jiecheng(int x){
    if (x == 0){
        return 1;
    } else {
        return x * jiecheng(x-1);
    }
}
