#include "../exercise.h"
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

// READ: std::shared_mutex <https://zh.cppreference.com/w/cpp/thread/shared_mutex>
// READ: std::shared_lock <https://zh.cppreference.com/w/cpp/thread/shared_lock>
// READ: std::unique_lock <https://zh.cppreference.com/w/cpp/thread/unique_lock>

class ThreadSafeCounter {
public:
    ThreadSafeCounter() = default;

    // 多个读取者可以同时读取计数器
    unsigned int get() const {
        // 使用共享锁允许多个读取者
        std::shared_lock lock(?);
        return value_;
    }

    // 只有一个写入者可以修改计数器
    void increment() {
        // 使用唯一锁确保只有一个写入者
        std::unique_lock lock(?);
        value_++;
    }

private:
    // NOTICE: 这里为什么要 mutable ?
    mutable std::shared_mutex mutex_;
    unsigned int value_ = 0;
};

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    ThreadSafeCounter counter;
    int num_reader_threads = 5;
    int num_writer_threads = 2;
    int increments_per_writer = 10000;
    int reads_per_reader = 5000;

    std::vector<std::thread> threads;

    // 创建写入者线程
    for (int i = 0; i < num_writer_threads; ++i) {
        threads.emplace_back([&counter, increments_per_writer]() {
            for (int j = 0; j < increments_per_writer; ++j) {
                counter.increment();
            }
        });
    }

    // 创建读取者线程
    for (int i = 0; i < num_reader_threads; ++i) {
        threads.emplace_back([&counter, reads_per_reader]() {
            for (int j = 0; j < reads_per_reader; ++j) {
                unsigned int value = counter.get();
                // 读取操作可以并行执行
                // std::cout << "Reader thread " << std::this_thread::get_id() << " read value: " << value << std::endl;
            }
        });
    }

    // 等待所有线程完成
    for (auto &t : threads) {
        t.join();
    }

    // 验证最终计数器的值
    unsigned int final_value = counter.get();
    unsigned int expected_value = num_writer_threads * increments_per_writer;
    ASSERT(final_value == ?, "Counter value should be the total number of increments.");
    ASSERT(expected_value == 20000, "Check logic");// 2 * 10000

    // THINK: `std::shared_mutex` 和 `std::mutex` 的主要区别是什么？
    // THINK: 什么情况下应该使用 `std::shared_lock`？什么情况下应该使用 `std::unique_lock`？
    // THINK: 如果在读取者函数 `get()` 中使用了 `std::unique_lock` 会发生什么？

    return 0;
}