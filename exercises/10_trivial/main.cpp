#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
     if (i >= 16) {
        // 处理超出缓存范围的情况
        return 0;
    }

    // 如果请求的索引尚未缓存，则从最后缓存的位置开始计算
    if (i >= cache.cached) {
        for (int idx = cache.cached; idx <= i; ++idx) {
            cache.cache[idx] = cache.cache[idx - 1] + cache.cache[idx - 2];
        }
        cache.cached = i + 1; // 更新已缓存的数量（0到i共i+1项）
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    
    FibonacciCache fib = {
     {0, 1},
     2
    };
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
