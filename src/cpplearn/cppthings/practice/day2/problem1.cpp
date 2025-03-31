/* 函数综合练习题.cpp */
/*
一圆型游泳池如图所示，现在需在其周围建一圆型过道，并在其四周围上栅栏。栅栏价格为35元/米，过道造价为20元/平方米。
过道宽度为3米，游泳池半径由键盘输入。要求编程计算并输出过道和栅栏的造价。

图形描述：大圆嵌套小圆：
小圆在大圆中间，小圆为游泳池，大圆与小圆间隔为过道。
*/
#include <iostream>
using namespace std;
const float PI = 3.14159;
const float FencePrice = 35;
const float ConcretePrice = 20;


class Circle{
    public:
    Circle(float r);
    float GetArea(); // 圆的面积
    float GetPerimeter(); // 圆的周长
    private:
    float R;
};


// 初始化
Circle::Circle(float r){
    R = r;
}
// 圆的面积
float Circle::GetArea(){
    return PI * R * R;
}
// 圆的周长
float Circle::GetPerimeter(){
    return 2 * PI * R;
}


int main(int argc, char* argv[]){
    int r;
    cout << "Enter the radius of the pool: ";
    cin >> r;
    Circle pool(r);
    Circle poolpath(r+3);

    float fencecost = poolpath.GetPerimeter() * FencePrice;
    float concretecost = (poolpath.GetArea() - pool.GetArea()) * ConcretePrice;

    cout << "The fence cost is " << fencecost << endl;
    cout << "The concrete cost is " << concretecost << endl;

    return 0;
}
