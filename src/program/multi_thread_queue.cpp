/* 生产者消费者问题，需要使用互斥锁 和 条件变量实现 */
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>
#include <threads.h>
#include <iostream>

#define BUFFER_SIZE 4

/* C17 */
mtx_t c17_mtx; // 保证资源访问的互斥性
cnd_t c17_cv; // 用于线程同步，保证线程执行顺序
int count = 0;
char c17_queue[BUFFER_SIZE];

/* C++20 */
std::mutex c20_mtx;
std::condition_variable c20_cv;
std::queue<int> c20_queue;

int c17_producer(void* arg){
    int i = 0;
    for (i = 0; i<BUFFER_SIZE; i++){
        mtx_lock(&c17_mtx);
        while (count == BUFFER_SIZE) {
            cnd_wait(&c17_cv, &c17_mtx);
        }
        c17_queue[count] = i;
        count++;
        cnd_signal(&c17_cv);
        mtx_unlock(&c17_mtx);
    }
    return 0;
}
int c17_consumer(void* arg){
    while (1) {
        mtx_lock(&c17_mtx);
        while (count == 0) {
            cnd_wait(&c17_cv, &c17_mtx);
        }
        int message = c17_queue[count - 1];
        count--;
        cnd_signal(&c17_cv);
        mtx_unlock(&c17_mtx);
        std::cout << "meaasge from c17 is : " << message << std::endl;
    }
}

void c20_producer(){

}
void c20_consumer(){

}
void multi_thread_queue(){
    /* c17 */
    mtx_init(&c17_mtx, mtx_plain);
    cnd_init(&c17_cv);
    thrd_t c17_producer_thrd, c17_consumer_thrd;
    thrd_create(&c17_producer_thrd, c17_producer, NULL);
    thrd_create(&c17_consumer_thrd, c17_consumer, NULL);
    thrd_join(c17_producer_thrd, NULL);
    thrd_join(c17_consumer_thrd, NULL);
    mtx_destroy(&c17_mtx);
    cnd_destroy(&c17_cv);

}
