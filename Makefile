# 基本语法
# target: dependencies
# 	command

# 定义变量
CC = g++
CFlAGS = -std=c++20
CMODULE = -fmodules-ts
SRC_DIR = ./src/pratice/
BUILD_DIR = ./test/

# 目标：所有
all: $(BUILD_DIR)helloworld

# 目标：可执行文件
$(BUILD_DIR)helloworld: $(BUILD_DIR)Module_foo.o $(BUILD_DIR)externc.o $(BUILD_DIR)externvar.o $(SRC_DIR)helloworld.cpp
	$(CC) $(CFLAGS) $(CMODULE) $(BUILD_DIR)Module_foo.o $(BUILD_DIR)externc.o $(BUILD_DIR)externvar.o $(SRC_DIR)helloworld.cpp -o $(BUILD_DIR)helloworld

# 目标：编译各种.o
$(BUILD_DIR)Module_foo.o: $(SRC_DIR)module_foo.cpp
	$(CC) $(CFLAGS) $(CMODULE) -c $(SRC_DIR)module_foo.cpp -o $(BUILD_DIR)Module_foo.o
$(BUILD_DIR)externc.o: $(SRC_DIR)externc.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)externc.c -o $(BUILD_DIR)externc.o
$(BUILD_DIR)externvar.o: $(SRC_DIR)externvar.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)externvar.cpp -o $(BUILD_DIR)externvar.o

clean:
	rm -rf $(BUILD_DIR)*.o $(BUILD_DIR)helloworld
