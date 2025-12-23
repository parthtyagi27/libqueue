#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace queue_containers {

/*
 * * Ring Buffer queue implementation
 * Queue does not overwrite, i.e if the write index is equal to the read index in a non_zero queue, we do nothing
 */

template <typename T, size_t buffer_size>
class RingBuffer {
private:
    std::array<T, buffer_size> buffer;
    size_t read_idx;
    size_t write_idx;
    size_t num_elements;

public:
    size_t size() const {return num_elements;}
    bool empty() const {return num_elements == 0;}
    bool full() const {return num_elements == buffer_size;}
    bool push(const T& object) {
        if (full()) {
            return false;
        }
        buffer[write_idx] = object;
        if (write_idx == SIZE_MAX)
            write_idx = 0;
        else
            write_idx = (write_idx + 1) % buffer_size;
        num_elements++;
        return true;
    }
    std::optional<T> front() {
        if (empty())
            return std::nullopt;
        return buffer[read_idx];
    }
    bool pop() {
        if (empty())
            return false;
        if (read_idx == SIZE_MAX) {
            read_idx = 0;
        } else {
            read_idx = (read_idx + 1) % buffer_size;
        }
        num_elements--;
        return true;
    }
    // for debugging
    size_t get_write_idx() const {return write_idx;}
    size_t get_read_idx() const {return read_idx;}
};

}
