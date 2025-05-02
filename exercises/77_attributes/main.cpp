#include "../exercise.h"
#include <stdexcept>
#include <string>
#include <vector>

// READ: Attributes (C++11 and later) <https://zh.cppreference.com/w/cpp/language/attributes>
// READ: [[nodiscard]] (C++17) <https://zh.cppreference.com/w/cpp/language/attributes/nodiscard>
// READ: [[deprecated]] (C++14) <https://zh.cppreference.com/w/cpp/language/attributes/deprecated>
// READ: [[maybe_unused]] (C++17) <https://zh.cppreference.com/w/cpp/language/attributes/maybe_unused>

// 使用 [[nodiscard]] 属性标记函数，提示调用者不应忽略返回值
[[nodiscard]]
int calculate_value() {
    return 42;
}

// 使用 [[nodiscard("Reason...")]] 提供更详细的提示
[[nodiscard("Ignoring the result of create_resource might lead to resource leaks.")]]
std::string *create_resource() {
    return new std::string("important resource");
}

// 使用 [[deprecated]] 标记不推荐使用的函数
[[deprecated("Use new_function() instead.")]]
void old_function(int x) {
    // ...
}

void new_function(int x) {
    // ...
}

// 使用 [[maybe_unused]] 标记可能未使用的变量或参数，避免编译器警告
void process_data(int data, [[maybe_unused]] bool debug_mode) {
    int result = data * 2;
    // 在非调试模式下，debug_mode 可能未使用
#ifdef DEBUG
    if (debug_mode) {
        std::cout << "Debug mode enabled, result: " << result << std::endl;
    }
#endif
    // ... 使用 result
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. [[nodiscard]]
    // 下面的调用会产生警告（如果编译器支持并启用了相应警告）
    // calculate_value(); // 警告：忽略了带有 [[nodiscard]] 属性的函数返回值
    int value = calculate_value();
    ASSERT(value == ?, "Value should be 42");

    // 下面的调用也会产生警告
    // create_resource(); // 警告：忽略了带有 [[nodiscard]] 属性的函数返回值...
    std::string *resource = create_resource();
    ASSERT(*resource == "important resource", "Resource content mismatch");
    delete resource;// 记得释放资源

    // 2. [[deprecated]]
    // 下面的调用会产生警告
    // old_function(10); // 警告：'old_function' is deprecated: Use new_function() instead.
    new_function(10);// 使用新函数

    // 3. [[maybe_unused]]
    [[maybe_unused]] int unused_variable = 5;// 标记此变量可能未使用
    process_data(20, true);

    // THINK: [[nodiscard]] 主要用于解决什么问题？它如何帮助开发者避免错误？
    // THINK: [[deprecated]] 和直接删除旧函数相比有什么优势？
    // THINK: 在哪些情况下 [[maybe_unused]] 特别有用？

    return 0;
}
