#include "../exercise.h"
#include <functional>
#include <string>
#include <vector>

// READ: std::invoke <https://zh.cppreference.com/w/cpp/utility/functional/invoke>


// 一个普通的函数
int add(int a, int b) {
    return a + b;
}

// 一个函数对象（functor）
struct Multiplier {
    int operator()(int a, int b) const {
        return a * b;
    }
};

// 一个包含成员函数的类
struct Container {
    std::vector<int> data;

    void add_element(int x) {
        data.push_back(x);
    }

    int get_element(size_t index) const {
        return data.at(index);
    }

    size_t size() const {
        return data.size();
    }
};

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 调用普通函数
    ASSERT(std::invoke(?, 10, 20) == 30, "Calling function add failed");

    // 调用函数对象
    Multiplier multiplier;
    ASSERT(std::invoke(?, 5, 6) == 30, "Calling functor Multiplier failed");

    // 调用成员函数
    Container container;
    std::invoke(&Container::add_element, ?, 42); // 调用非 const 成员函数
    ASSERT(container.size() == 1, "Calling member function add_element failed");
    ASSERT(std::invoke(&Container::get_element, ?, 0) == 42, "Calling const member function get_element failed");

    // THINK: `std::invoke` 主要解决了什么问题？
    // THINK: `std::invoke` 和直接调用函数/成员函数有什么区别？在什么场景下 `std::invoke` 特别有用？
    // THINK: `std::invoke` 如何处理指向成员函数和指向成员变量的指针？

    return 0;
}