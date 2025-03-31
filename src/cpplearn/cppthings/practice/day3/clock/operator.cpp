/* 重载（） */
#include <iostream>
using namespace std;

class Clock{
    private:
    int hh, mm, ss;
    public:
    Clock(int h, int m, int s) : hh(h), mm(m), ss(s) {}
    void operator()(int h, int m, int s){
        hh = h;
        mm = m;
        ss = s;
    }
    void showTime(){
        cout << hh << ":" << mm << ":" << ss << endl;
    }
};

int main(){
    Clock c(12, 34, 56);
    c.showTime();
    c(11, 22, 33);
    c.showTime();
    return 0;
}
