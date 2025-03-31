#ifndef CLOCK
#define CLOCK
class Clock{
    private:
    int hh, mm, ss;
    public:
    /*
    看到没，这里只做了声明，没有做定义，所以这里是一个虚函数。
    */
    Clock(int h, int m, int s);
    // 拷贝构造函数
    Clock(Clock& other);// 如果不写，编译器会自动生成
    void setTime(int h, int m, int s);
    void showTime();
    ~Clock();
};
#endif
