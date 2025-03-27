#include <stdio.h>

// 在C++中调用C函数，需要在cpp中使用extern "C" functionname
void helloworld_C(){
    printf("%s\n","hello world");
}
