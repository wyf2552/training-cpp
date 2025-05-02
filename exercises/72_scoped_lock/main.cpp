#include "../exercise.h"
#include <mutex>
#include <thread>
#include <vector>

// READ: std::scoped_lock <https://zh.cppreference.com/w/cpp/thread/scoped_lock>
// READ: RAII <https://zh.cppreference.com/w/cpp/language/raii>

int shared_counter = 0;
std::mutex mtx1;
std::mutex mtx2;

void worker1() {
    for (int i = 0; i < 10000; ++i) {
        // 使用 scoped_lock 同时锁定 mtx1 和 mtx2
        std::scoped_lock lock(?, ?);
        shared_counter++;
        shared_counter--;
    }
}

void worker2() {
    for (int i = 0; i < 10000; ++i) {
        // 以不同的顺序锁定 mtx1 和 mtx2，scoped_lock 会处理死锁问题
        std::scoped_lock lock(?, ?);
        shared_counter++;
        shared_counter--;
    }
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::thread t1(worker1);
    std::thread t2(worker2);

    t1.join();
    t2.join();

    // 由于 scoped_lock 正确处理了锁，最终计数器应该为 0
    ASSERT(shared_counter == ?, "最终计数器应为 0");

    // THINK: `std::scoped_lock` 和 `std::lock_guard` 的主要区别是什么？
    // THINK: `std::scoped_lock` 如何避免死锁？
    // THINK: 为什么推荐使用 RAII 风格的锁（如 `std::scoped_lock`, `std::lock_guard`, `std::unique_lock`）而不是手动调用 `lock()` 和 `unlock()`？

    return 0;
}