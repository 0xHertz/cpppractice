#include <iostream>
#include <utility>

class MyClass {
public:
    MyClass() : data(nullptr), size(0) {
        std::cout << "Default constructor" << std::endl;
    }

    MyClass(size_t n) : data(new int[n]), size(n) {
        std::cout << "Parameterized constructor" << std::endl;
    }

    ~MyClass() {
        delete[] data;
        std::cout << "Destructor" << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
        std::cout << "Copy constructor" << std::endl;
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor" << std::endl;
    }

    // 拷贝赋值运算符
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete[] data;
            data = new int[other.size];
            size = other.size;
            std::copy(other.data, other.data + size, data);
        }
        std::cout << "Copy assignment operator" << std::endl;
        return *this;
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Move assignment operator" << std::endl;
        return *this;
    }

private:
    int* data;
    size_t size;
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = std::move(obj1); // 调用移动构造函数
    MyClass obj3;
    obj3 = std::move(obj2); // 调用移动赋值运算符

    return 0;
}
