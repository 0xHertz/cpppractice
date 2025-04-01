/* 类模板特化.cpp */
//设计一通用数组类，它能够直接存取数组元素，并能够对数组进行从大到小的排序。
#include <iostream>
#include <cstring>
using namespace std;

const int Size = 5;

template<class T>
class MArray{
    private:
    T a[Size];
    public:
    MArray(){
        for (int i = 0; i < Size; i++) {
            a[i] = 0;
        }
    }
    T &operator[](int);
    void Sort();
};


/*
原型：
template <模板参数列表>
返回值类型 类模板名<模板参数名表>::成员函数名 (参数列表){};
*/
// 仔细看这里的类名怎么写的
template<class T>
T &MArray<T>::operator[](int index){
    if (index < 0 || index > Size - 1) {
        cout << "\n数组下标越界！" << endl;
        exit(1);
    }
    return a[index];
}
// 自己写一个sort
template<class T>
void MArray<T>::Sort(){
    // 冒泡排序
    for (int i = 0; i< Size-1; i++){
        for (int j=i+1; j<Size; j++){
            if (a[i] < a[j]){
                T tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
    }
}
/* 模板的特化值的是针对某种类型单独写一套逻辑 */
// template <> 返回类型 类模板名<特化的数据类型>::特化成员函数名(参数表){}
template <>
void MArray<char *>::Sort(){
    // 针对char* 类型的特化
    for (int i=0; i< Size-1; i++){
        for (int j=i+1; j<Size; j++){
            if (strcmp(a[i], a[j]) < 0){
                char *tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
    }
}

int main(int argc, char* argv[]){
    MArray<int> arr_int;
    MArray<char* > arr_char;

    arr_int[0] = 0;
    arr_int[1] = 1;
    arr_int[2] = 8;
    arr_int[3] = 3;
    arr_int[4] = 2;
    for (int i = 0; i < 5; i++)
        cout << arr_int[i] << "\t";
    arr_int.Sort();
    cout << endl;
    for (int i = 0; i < 5; i++)
        cout << arr_int[i] << "\t";

    cout << endl;
    arr_char[0] = "000";
    arr_char[1] = "001";
    arr_char[2] = "008";
    arr_char[3] = "003";
    arr_char[4] = "002";
    for (int i = 0; i < 5; i++)
        cout << arr_char[i] << "\t";
    arr_char.Sort();
    cout << endl;
    for (int i = 0; i < 5; i++)
        cout << arr_char[i] << "\t";

    return 0;
}
