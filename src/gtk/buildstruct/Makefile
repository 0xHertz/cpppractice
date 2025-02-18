# 定义编译器
CC = g++

# 定义编译选项
CFLAGS = `pkg-config --cflags gtk4` -Wall -g

# 定义链接选项
LDFLAGS = `pkg-config --libs gtk4`

# 定义目标文件
TARGET = myprogram

# 定义源文件
SRCS = notebook_application.cpp tfetextview.cpp tfenotebook.cpp

# 定义目标文件的生成规则
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# 定义清理规则
.PHONY: clean
clean:
	rm -f $(TARGET)
