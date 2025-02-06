#include <stdio.h>

// 在C++中调用C函数，需要使用extern "C" functionname
extern "C" void helloworld_C(){
    printf("%s\n","hello world");
}
