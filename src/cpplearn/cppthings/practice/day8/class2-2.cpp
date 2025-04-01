// Eg10-12.cpp
#include <iostream>
using namespace std;
class BasicException {
public:
  char *Where() { return "BasicException..."; }
};
class FileSysException : public BasicException {
public:
  char *Where() { return "FileSysException..."; }
};
class FileNotFound : public FileSysException {
public:
  char *Where() { return "FileNotFound..."; }
};
class DiskNotFound : public FileSysException {
public:
  char *Where() { return "DiskNotFound..."; }
};
int main() {
    // 不是虚函数哦
    // 捕获顺序是从最具体的异常类型到最通用的异常类型
  try {
    //         .....  //程序代码
    throw FileSysException();  // FileSysException...
  } catch (DiskNotFound p) {
    cout << p.Where() << endl;
  } catch (FileNotFound p) {
    cout << p.Where() << endl;
  } catch (FileSysException p) {
    cout << p.Where() << endl;
  } catch (BasicException p) {
    cout << p.Where() << endl;
  }
  // 捕获顺序是从最通用的异常类型到最具体的异常类型
  try {
    //        .....  //程序代码
    throw DiskNotFound();   // BasicException...
  } catch (BasicException p) {
      /*
      由于 `DiskNotFound` 是 `BasicException` 的派生类，第一个 `catch` 块就能捕获它。
      - 但是由于对象切片问题，`DiskNotFound` 对象被切片成 `BasicException` 对象，因此输出 `BasicException...`
      */
    cout << p.Where() << endl;
  } catch (FileSysException p) {
    cout << p.Where() << endl;
  } catch (DiskNotFound p) {
    cout << p.Where() << endl;
  } catch (FileNotFound p) {
    cout << p.Where() << endl;
  }
}
