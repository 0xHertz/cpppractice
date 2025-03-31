# include <iostream>
using namespace std;

class Application {
    private:
    static int global_id;
    char* name;
    public:
    static void getid();
    static void setid();
};
// 初始化静态成员变量
int Application::global_id = 0;
// 静态成员函数
void Application::getid(){
    // 静态成员函数只能引用属于该类的静态数据成员或静态成员函数。
    cout << "global_id: " << global_id << endl;

    /* Invalid use of member 'name' in static member function */
    // cout << "name" << name << endl;
}
void Application::setid(){
    global_id++;
}

int main(int argc, char* argv[]){
    Application::getid();
    Application::setid();
    Application::getid();

    return 0;
}
