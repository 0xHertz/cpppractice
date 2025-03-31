/* 重载++的时钟.cpp */
/*
设计一个时钟类，能够记录时、分、秒，重载它的++运算符，每执行一次++运算，加时1秒，但要使计时过程能够自动进位。
*/
#include <iostream>
using namespace std;

class Clock{
    private:
    int hh, mm, ss;
    public:
    Clock(int h, int m, int s) : hh(h), mm(m), ss(s) {}
    Clock operator++(){
        ++ss;
        if (ss >= 60){
            ss -= 60;
            ++mm;
            if (mm >= 60){
                mm -= 60;
                ++hh;
                if (hh >= 24){
                    hh = 0;
                }
            }
        }
        return *this;
    }
    void showTime(){
        cout << hh << ":" << mm << ":" << ss << endl;
    }
};

int main(int argc, char* argv[]){
    Clock c(23, 59, 59);
    c.showTime();
    ++c;
    c.showTime();
    return 0;
}
