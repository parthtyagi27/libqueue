
#include <iostream>
#include <optional>
#include "../src/containers/ringbuffer.hpp"

void test_empty_queue() {
    queue_containers::RingBuffer<int, 100> queue{};
    queue.pop();
}

void test_pop_before_push() {
    queue_containers::RingBuffer<int, 100> queue{};
    queue.pop();
    queue.push(100);
    std::cout << queue.size() << "\n";
    std::cout << *queue.front() << "\n";
    std::cout << queue.size() << "\n";
}

void test_push_pop() {
    queue_containers::RingBuffer<int, 5> buffer{};
    for (int i = 0; i < 4; i++) {
        bool val = buffer.push(i);
        if (val)
            std::cout << "success\n";
        else
            std::cout << "fail\n";
    }

    while (!buffer.empty()) {
        std::optional<int> val = buffer.front();
        if (val) {
            std::cout << *val << ",";
        }
        buffer.pop();
    }
    std::cout << "\n";
    buffer.push(7);
    std::cout << buffer.get_write_idx() << "\n";
    std::cout << buffer.get_read_idx() << "\n";

    std::cout << "\n";
    buffer.push(8);
    std::cout << buffer.get_write_idx() << "\n";
    std::cout << buffer.get_read_idx() << "\n";
}

int main() {
    test_empty_queue();
    test_push_pop();
    test_pop_before_push();
    return 0;
}
