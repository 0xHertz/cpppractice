/* 设计一个字符串类String，
通过运算符重载实现字符串的输入、输出以及+=、==、!=、<、>、>=、[]等运算 */
#include <iostream>
#include <cstring>
using namespace std;

class MString{
    private:
    int len; // 字符串长度
    char *sptr; // 字符串指针
    void setStr(const char* str);
    friend ostream &operator<<(ostream &os, const MString &s){
        return os << s.sptr;
    };
    friend istream &operator>>(istream &is, MString &s) {
        return is >> s.sptr;
    };

    public:
    MString(const char* str=""){
        sptr = new char[strlen(str) + 1];
        strcpy(sptr, str);
        len = strlen(str);
    };
    // 重载赋值运算符
    const MString &operator=(const MString &R){
        len = R.len;
        strcpy(sptr, R.sptr);
        return *this;
    }
    //字符串的连接 +=
    const MString &operator+=(const MString &R){
        len += R.len;
        char* tmp = sptr;
        sptr = new char[len + 1];
        strcpy(sptr,tmp);
        strcat(sptr, R.sptr);
        delete[] tmp;
        return *this;
    }
    //字符串的相等比较 ==
    bool operator==(const MString &R){
        return strcmp(sptr, R.sptr);
    }
    //字符串的不等比较 !=
    bool operator!=(const MString &R){
        return !strcmp(sptr, R.sptr);
    }
    //判定字符串是否为空
    bool operator!(){
        return len == 0;
    }
    //字符串的小于比较 <
    bool operator<(const MString &R){
        return len < R.len;
    }
    //字符串的大于比较 >
    bool operator>(const MString &R){
        return len > R.len;
    }
    //字符串的大于等于比较
    bool operator<=(const MString &R){
        return len <= R.len;
    }
    //字符串的下标运算[]
    char &operator[](int i){
        return sptr[i];
    }
};

int main(int argc, char* argv[]){
    MString str1{"char"},str2{"int"};
    str1 += str2;
    cout << str1 << endl;
    cout << (str1==str2 ? "true" : "false") << endl;
    cout << (str1!=str2 ? "true" : "false") << endl;
    cout << (str1>str2 ? "true" : "false") << endl;
    cout << (str1<str2 ? "true" : "false") << endl;
    cout << (str1<=str2 ? "true" : "false") << endl;
    cout << str1[3] << endl;

    return 0;
}
