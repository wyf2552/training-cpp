#include "../exercise.h"
#include <string>
#include <string_view>

// READ: std::string_view <https://zh.cppreference.com/w/cpp/string/basic_string_view>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::string s = "Hello, world!";
    std::string_view sv = s;

    // 1. 创建 string_view
    ASSERT(sv.length() == ?, "string_view 的长度");
    ASSERT(sv.data() == s.data(), "string_view 指向原始字符串数据");

    // 2. string_view 的子串
    std::string_view sub = sv.substr(7, 5);// 从索引 7 开始，长度为 5
    ASSERT(sub == ?, "子串应该是 'world'");

    // 3. 修改原始字符串
    s[0] = 'h';
    // NOTICE: string_view 观察的是原始字符串，所以也会改变
    ASSERT(sv[0] == ?, "原始字符串修改后，string_view 也改变");

    // 4. string_view 的比较
    std::string s2 = "hello, world!";
    std::string_view sv2 = s2;
    ASSERT(sv == sv2, "比较两个 string_view");

    // 5. 从 C 风格字符串创建 string_view
    const char *c_str = "C-style string";
    std::string_view sv_from_c = c_str;
    ASSERT(sv_from_c.length() == ?, "从 C 风格字符串创建的 string_view 长度");

    // 6. string_view 的 remove_prefix 和 remove_suffix
    sv = "prefix_content_suffix";
    sv.remove_prefix(7);// 移除 "prefix_"
    ASSERT(sv == ?, "移除前缀后");
    sv.remove_suffix(7);// 移除 "_suffix"
    ASSERT(sv == ?, "移除后缀后");

    // THINK: std::string_view 与 std::string 的主要区别是什么？
    // THINK: 在什么情况下使用 std::string_view 比 std::string 更优？
    // THINK: std::string_view 是否拥有其指向的字符串数据？

    return 0;
}