#include "../src/mutex_queue.hpp"
#include "../src/containers/ringbuffer.hpp"


void test_multiple_thread_push_pop() {
    queues::GlobalMutexQueue<int, queue_containers::RingBuffer<int, 100>, queues::options::BlockingOptions::Blocking> queue{};
    queue.pop();
}

int main() {
    test_multiple_thread_push_pop();
    return 0;
}
