#pragma once
#include <array>
#include <cstddef>
#include <mutex>
#include <optional>

namespace queues {

/**
 * Thread safe queue backed by a global mutex
 * Queue is backed by a ring buffer
 * Global mutex is simple to reason about but can cause a lot of contention
 * TODO: Benchmark this to come up with numbers
 */

/*
 * * Queue API Design
 * The queue is non-blocking
 * It supports 2 operations, front() and push(T)
 */

template <typename T, class Container>
class GlobalMutexQueue {
private:
    Container queue;
    size_t num_elements;
    std::mutex mtx;

public:
    // delete all copy and move contstructors, not sure what it means to "copy" or "move" a thread-safe queue
    GlobalMutexQueue() : queue{}, num_elements{0}, mtx{} {};
    GlobalMutexQueue(const GlobalMutexQueue&) = delete;
    GlobalMutexQueue(GlobalMutexQueue&&) = delete;
    GlobalMutexQueue& operator=(const GlobalMutexQueue&) = delete;
    GlobalMutexQueue& operator=(GlobalMutexQueue&&) = delete;

    std::optional<T> front();
    bool push(const T& object);
};


}
