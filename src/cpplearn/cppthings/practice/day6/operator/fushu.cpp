/*
运算符重载：
复数运算
*/
#include <iostream>
using namespace std;

// 定义类
class Complex{
    private:
    double i,r;
    public:
    Complex(double i=0, double r=0) : i(i), r(r) {};
    Complex operator+(Complex c);
    Complex operator-(Complex c);
    Complex operator*(Complex c);
    Complex operator/(Complex c);
    void display();
};
// 实现成员函数
Complex Complex::operator+(Complex c){
    return Complex(r+c.r, i+c.i);
}
Complex Complex::operator-(Complex c){
    return Complex(r-c.r, i-c.i);
}
Complex Complex::operator*(Complex c){
    Complex t;
    t.r = r * c.r - i * c.i;
    t.i = r * c.i + i * c.r;
    return t;
}
Complex Complex::operator/(Complex b) {
  Complex t;
  double x;
  x = 1 / (b.r * b.r + b.i * b.i);
  t.r = x * (r * b.r + i * b.i);
  t.i = x * (i * b.r - r * b.i);
  return t;
}
void Complex::display(){
    cout << r;
    if (i > 0)
        cout << "+";
    if (i != 0)
        cout << i << "i" << endl;
}

int main(int argc, char* argv[]){
    Complex A{1,2},B{3,4};
    Complex C = B-A;
    Complex D = B+A;
    Complex E = B*A;
    Complex F = B/A;

    C.display();
    D.display();
    E.display();
    F.display();
    return 0;
}
