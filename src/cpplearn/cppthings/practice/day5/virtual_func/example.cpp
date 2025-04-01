/* 编程实例.cpp */
/*
某公司有经理、销售员、小时工等多类人员。经理按周计算薪金；销售员每月底薪800元，
然后加销售提成，每销售1件产品提取销售利润的5%；小时工按小时计算薪金。每类人员都有姓名和身份证号等数据。
为简化问题，把各类人员的共有信息抽象成基类Employee，其他人员则继承该类的功能。
*/
#include <iostream>
#include <map>
using namespace std;

// base class
class Employee {
    private:
    char * name;
    char * id;
    float money;
    public:
    Employee(char* n, char* i) : name(n),id(i) {};
    char * getName(){ return name; }
    char * getId(){ return id; }
    float getMoney(){ return money; }
    void setMoney(float m){ money = m; }
    virtual void compute_money(int i) = 0;
    virtual void printAll() = 0;
};
// manager class
class Manager : public Employee {
    private:
    float weeky_money;
    public:
    Manager(char* n, char* i,int w) : Employee(n, i) {
        weeky_money = w;
    };
    void compute_money(int week){
        setMoney(week*weeky_money);
    }
    void printAll(){
        cout << "Manager " << getName() \
        << " " << getId() \
        << " 's money is " \
        << getMoney() << endl;
    }
};
// saler class
class SaleWorker : public Employee {
    private:
    const float base_money = 800.0;
    std::map<int, float> sale_map;
    public:
    SaleWorker(char* n, char* i, std::map<int, float> m) : Employee(n, i) {
        sale_map = m;
    };
    void compute_money(int i){
        float tmp = 0;
        for (const auto& pair : sale_map){
            tmp += pair.second;
        }
        setMoney(tmp+base_money);
    }
    void getSaleMap(){
        for (const auto& pair : sale_map) {
            std::cout << "number: " << pair.first << ", lirun: " << pair.second << std::endl;
        }
    }
    void printAll(){
        cout << "SaleWorker " << getName() \
        << " " << getId() \
        << " 's money is " \
        << getMoney() << endl;
    }
};
// hourworker class
class HourWorker : public Employee {
    private:
    float hour_money;
    public:
    HourWorker(char* n, char* i,int h) : Employee(n, i) {
        hour_money = h;
    };
    void compute_money(int hour){
        setMoney(hour*hour_money);
    }
    void printAll(){
        cout << "HourWorker " << getName() \
        << " " << getId() \
        << " 's money is " \
        << getMoney() << endl;
    }
};


int main(int argc, char* argv[]){

    Manager m{"kechen","0001",1000};
    map<int , float> sale = {{100,300.0},{34,59.0},{67,80.0}};
    SaleWorker s{"sober", "0002",sale};
    HourWorker h{"wangq", "0003", 100};


    int m_work_week,h_work_hour;
    cout << "请输入经理" << m.getName() << "的工作周数：";
    cin >> m_work_week;
    cout << "请确认销售员工作业绩: " << endl;
    s.getSaleMap();
    cout << "请输入小时工" << h.getName() << "的工作时长：";
    cin >> h_work_hour;

    m.compute_money(m_work_week);
    m.printAll();

    s.compute_money(0);
    s.printAll();

    h.compute_money(h_work_hour);
    h.printAll();
    return 0;
}
