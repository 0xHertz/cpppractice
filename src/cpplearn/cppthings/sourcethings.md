## C++源码解读
源码剖析版本为gcc4.9.1。

C++ tr1全称Technical Report 1，是针对C++标准库的第一次扩展。即将到来的下一个版本的C++标准c++0x会包括它，以及一些语言本身的扩充。tr1包括大家期待已久的smart pointer，正则表达式以及其他一些支持范型编程的内容。
### array
有两种实现
#### std::tr1::array
#### std::array
### deque
deque是一个双端队列，分段连续线性空间，随时可以增加一段新的空间，支持随机访问，在两端插入和删除元素的效率很高。




暂时不源码了，先去用
