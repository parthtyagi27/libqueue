#include <iostream>
#include <optional>
#include "../src/containers/ringbuffer.hpp"

int main() {
    queue_containers::RingBuffer<int, 5> buffer{};
    for (int i = 0; i < 5; i++) {
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

    return 0;
}
