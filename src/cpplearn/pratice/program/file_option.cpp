#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
/* C17 */
void c17_file_option(){
    FILE *source_file,*des_file;
    char buf[4096];
    size_t bytes_read;

    source_file = fopen("source.txt", "rb");
    des_file = fopen("des.txt", "rw");

    if (source_file == NULL || des_file == NULL) {
        cout << "file open error" << endl;
        exit(1);
    }
    /* fread(buf, read size per time(byte), total byte, file) */
    while ((bytes_read = fread(buf, 1, sizeof(buf), source_file)) > 0) {
        fwrite(buf, 1, bytes_read, des_file);
    }

    fclose(source_file);
    fclose(des_file);
}

/* C++20 */
void c20_file_option(){
    const string source_file = "source.txt";
    const string des_file = "des.txt";

    /* 相当于fopen src_input 和 des_output 是自定义变量 */
    // 新建类的语法
    std::ifstream src_input(source_file,std::ios::binary);
    std::ofstream des_output(des_file,std::ios::binary);

    if (!src_input.is_open() || !des_output.is_open()) {
        cout << "file open error" << endl;
        exit(1);
    }

    des_output << src_input.rdbuf();

    des_output.close();
    src_input.close();
}

void fileCopy(){
    c17_file_option();
    c20_file_option();
}
