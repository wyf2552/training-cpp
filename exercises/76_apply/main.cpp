#include "../exercise.h"
#include <functional>
#include <iostream>
#include <tuple>

// READ: std::apply (C++17) <https://zh.cppreference.com/w/cpp/utility/apply>

// 一个接受多个参数的函数
int sum(int a, int b, int c) {
    return a + b + c;
}

// 一个接受不同类型参数的函数
void print_info(const std::string &name, int age, double height) {
    std::cout << "Name: " << name << ", Age: " << age << ", Height: " << height << std::endl;
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 使用 std::apply 调用接受固定数量参数的函数
    std::tuple<int, int, int> args1 = {10, 20, 30};
    ASSERT(std::apply(?, ?) == 60, "Calling sum with tuple failed");

    // 使用 std::apply 调用接受不同类型参数的函数
    std::tuple<std::string, int, double> args2 = {"Alice", 30, 1.65};
    // std::apply 可以直接调用 void 函数
    std::apply(?, ?);
    // 这里没有 ASSERT，因为 print_info 是 void 函数，我们主要看它是否能成功调用

    // 使用 std::apply 调用 lambda 表达式
    auto lambda = [](const std::string &s, int n) {
        return s + std::to_string(n);
    };
    std::pair<std::string, int> args3 = {"Value: ", 42};
    ASSERT(std::apply(?, ?) == "Value: 42", "Calling lambda with pair failed");

    // THINK: `std::apply` 和 `std::invoke` 有什么关系？它们各自解决了什么问题？
    // THINK: `std::apply` 可以用于哪些类型的“类元组”对象？
    // THINK: 如果元组中的元素数量或类型与函数参数不匹配，`std::apply` 会发生什么？

    return 0;
}