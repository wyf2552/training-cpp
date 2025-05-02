#include "../exercise.h"

#include <mutex>
#include <string>
#include <utility>
#include <vector>

// READ: Class Template Argument Deduction (CTAD) (C++17) <https://zh.cppreference.com/w/cpp/language/class_template_argument_deduction>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // C++17 之前，必须显式指定模板参数
    std::vector<int> vec1 = {1, 2, 3};
    std::pair<int, std::string> p1 = {1, "hello"};
    std::lock_guard<std::mutex> lg1(std::mutex{});

    // C++17 引入了类模板参数推导 (CTAD)
    // 编译器可以根据构造函数参数推导出模板参数

    // 使用 CTAD 创建 std::vector
    std::vector vec2 = {4, 5, 6};// 推导出 std::vector<int>
    ASSERT(vec2.size() == ?, "vec2 size should be 3");
    ASSERT(vec2[0] == ?, "vec2[0] should be 4");
    ASSERT(typeid(vec2) == typeid(std::vector<int>), "vec2 should be std::vector<int>");

    // 使用 CTAD 创建 std::pair
    std::pair p2 = {2, "world"};// 推导出 std::pair<int, const char*>
    ASSERT(p2.first == ?, "p2.first should be 2");
    ASSERT(std::string(p2.second) == "world", "p2.second should be \"world\"");
    // 注意：字符串字面量 "world" 的类型是 const char[6]，推导为 const char*
    ASSERT(typeid(p2) == typeid(std::pair<int, const char *>), "p2 should be std::pair<int, const char*>");

    // 使用 CTAD 创建 std::lock_guard
    std::mutex mtx;
    std::lock_guard lg2 = std::lock_guard(mtx);// 推导出 std::lock_guard<std::mutex>
    // 或者更简洁：
    std::lock_guard lg3(mtx);// 同样推导出 std::lock_guard<std::mutex>
    ASSERT(typeid(lg2) == typeid(std::lock_guard<std::mutex>), "lg2 should be std::lock_guard<std::mutex>");
    ASSERT(typeid(lg3) == typeid(std::lock_guard<std::mutex>), "lg3 should be std::lock_guard<std::mutex>");

    // 用户定义的类模板也可以使用 CTAD
    template<typename T1, typename T2>
    struct MyPair {
        T1 first;
        T2 second;
        // 构造函数允许推导
        MyPair(T1 f, T2 s) : first(f), second(s) {}
    };

    MyPair mp = {10, std::string("CTAD")};// 推导出 MyPair<int, std::string>
    ASSERT(mp.first == ?, "mp.first should be 10");
    ASSERT(mp.second == "CTAD", "mp.second should be \"CTAD\"");
    ASSERT(typeid(mp) == typeid(MyPair<int, std::string>), "mp should be MyPair<int, std::string>");

    // THINK: CTAD 主要简化了什么？
    // THINK: CTAD 对 `std::vector`, `std::pair`, `std::tuple`, `std::lock_guard` 等标准库类型有什么影响？

    return 0;
}