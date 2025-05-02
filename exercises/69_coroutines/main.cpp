#include "../exercise.h"
#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

// READ: C++20 Coroutines <https://en.cppreference.com/w/cpp/language/coroutines>
// NOTE: Coroutines are a C++20 feature. Ensure your compiler supports C++20.
// NOTE: This is a simplified example. Real-world coroutine usage often involves more complex library support.

// --- A simple generator coroutine ---
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        int current_value;
        Generator get_return_object() { return Generator(handle_type::from_promise(*this)); }
        std::suspend_always initial_suspend() { return {}; }       // Suspend initially
        std::suspend_always final_suspend() noexcept { return {}; }// Suspend finally
        void unhandled_exception() { std::terminate(); }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};// Suspend after yielding
        }
        void return_void() {}
    };

    handle_type coro_handle;
    Generator(handle_type h) : coro_handle(h) {}
    ~Generator() {
        if (coro_handle) {
            coro_handle.destroy();
        }
    }

    // Make Generator movable but not copyable
    Generator(Generator &&other) noexcept : coro_handle(std::exchange(other.coro_handle, nullptr)) {}
    Generator &operator=(Generator &&other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = std::exchange(other.coro_handle, nullptr);
        }
        return *this;
    }
    Generator(const Generator &) = delete;
    Generator &operator=(const Generator &) = delete;

    // Get the next value
    bool move_next() {
        coro_handle.resume();
        return !coro_handle.done();
    }

    // Get the current value
    int current_value() {
        return coro_handle.promise().current_value;
    }
};

Generator count_to(int n) {
    for (int i = 1; i <= n; ++i) {
        co_yield i;// Yield the current value
    }
    // co_return; // Implicit return for void return type
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    auto gen = count_to(3);
    int sum = 0;

    ASSERT(gen.move_next(), "First move_next should succeed");
    ASSERT(gen.current_value() == ?, "First value should be 1");
    sum += gen.current_value();

    ASSERT(gen.move_next(), "Second move_next should succeed");
    ASSERT(gen.current_value() == ?, "Second value should be 2");
    sum += gen.current_value();

    ASSERT(gen.move_next(), "Third move_next should succeed");
    ASSERT(gen.current_value() == ?, "Third value should be 3");
    sum += gen.current_value();

    ASSERT(!gen.move_next(), "Fourth move_next should fail (coroutine done)");
    ASSERT(sum == ?, "Sum should be 1 + 2 + 3");

    // THINK: `co_yield`, `co_await`, `co_return` 的作用分别是什么？
    // THINK: Coroutine 的状态是如何保存和恢复的？
    // THINK: Coroutine 和线程有什么区别？

    return 0;
}