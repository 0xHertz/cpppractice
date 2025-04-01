/* 虚函数例子.cpp */

// Eg7-1.cpp
//基类指针或引用指向派生类对象时,虚函数与非虚函数区别：
//声明Employee的print为虚函数，则可访问到Manager的print函数，非虚函数，则只能访问到Employee的print
#include <iostream>
#include <string>
using namespace std;
class Employee {
public:
  Employee(string name, string id);
  string getName();
  string getId();
  float getSalary();
  virtual void print();

private:
  string Name;
  string Id;
};
Employee::Employee(string name, string id) {
  Name = name;
  Id = id;
}
string Employee::getName() { return Name; }
string Employee::getId() { return Id; }
float Employee::getSalary() { return 0.0; }
void Employee::print() {
  cout << "姓名：" << Name << "\t"
       << "编号：" << Id << endl;
}

class Manager : public Employee {
public:
  Manager(string name, string id, float s = 0.0) : Employee(name, id) {
    weeklySalary = s;
  }
  void setSalary(float s) { weeklySalary = s; } //设置经理的周薪
  float getSalary() { return weeklySalary; }    //获取经理的周薪
  void print() { //打印经理姓名、身份证、周薪
    cout << "经理：" << getName() << "\t\t 编号: " << getId()
         << "\t\t 周工资: " << getSalary() << endl;
  }

private:
  float weeklySalary; //周薪
};

/*
虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型
*/
int main() {
  Employee e("小米", "NO0001"), *pM;
  Manager m("小汪", "NO0002", 128);
  m.print(); // 小汪
  pM = &m;
  pM->print(); // 小汪
  Employee &rM = m;
  rM.print(); // 小汪

  return 0;
}
