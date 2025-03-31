#include <iostream>
using namespace std;

class Point{
    private:
    int X;
    int Y;
    // static成员变量，属于类，不属于对象,只能在类外初始化
    static int count;

    public:
    Point(int x, int y){
        X = x;
        Y = y;
        count++;
    }
    Point(Point &p);
    int GetX() { return X; }
    int GetY() { return Y; }
    static int GetCount() { return count; }
    void GetC() { cout << " Object id=" << count << endl; }
};

// 初始化静态成员变量
int Point::count = 0;
// 拷贝构造函数
Point::Point(Point &p){
    X = p.X;
    Y = p.Y;
    count++;
}

int main(){
    Point A(4, 5);
    cout << "A: " << A.GetX() << " " << A.GetY() << endl;
    Point B(A);
    cout << "B: " << B.GetX() << " " << B.GetY() << endl;

    cout << Point::GetCount() << endl;
    cout << A.GetCount() << endl;
    return 0;
}
