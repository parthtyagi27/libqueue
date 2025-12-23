#pragma once
#include <array>
#include <cstddef>
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
    bool push(const T& object) {
        if (write_idx == read_idx) {
            if (num_elements == 0) {
                // we can push
                buffer[write_idx] = object;
                write_idx++;
                num_elements++;
                return true;
            } else {
                // can't push to queue
                // TODO: maybe return bool to indicate success?
                return false;
            }
        } else {
            buffer[write_idx] = object;
            write_idx = (write_idx + 1) % buffer_size;
            num_elements++;
            return true;
        }
    }
    std::optional<T> front() {
        if (read_idx == write_idx) {
            if (num_elements == 0) {
                // we don't have any elements
                return std::nullopt;
            } else {
                // our indicies are the same but we have elements, what to do?
                std::optional<T> value = buffer[read_idx];
                return value;
            }
        } else {
            std::optional<T> value = buffer[read_idx];
            return value;
        }
    }
    void pop() {
        if (read_idx == write_idx) {
            if (num_elements > 0) {
                // we can pop
                read_idx = (read_idx + 1) % buffer_size;
                num_elements--;
            }
        } else {
            read_idx = (read_idx + 1) % buffer_size;
            num_elements--;
        }
    }
};

}
