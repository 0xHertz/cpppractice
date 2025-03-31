#include "clock.h"
#include <iostream>
using namespace std;

// 定义类的成员函数
Clock::Clock(int h, int m, int s) : hh(h), mm(m), ss(s) {}
Clock::Clock(Clock &c){
    hh = c.hh;
    mm = c.mm;
    ss = c.ss;
}
void Clock::showTime(){
    cout << hh << ":" << mm << ":" << ss << endl;
}
void Clock::setTime(int h, int m, int s){
    hh = h;
    mm = m;
    ss = s;
}
Clock::~Clock() {}


int main(int argc, char const *argv[]) {
  Clock c(0, 0, 0);

  c.setTime(10, 20, 30);
  c.showTime();
  //拷贝构造函数调用
  Clock c1(c);
  c1.showTime();
  c1.setTime(90, 98, 99);
  c1.showTime();
  return 0;
}
