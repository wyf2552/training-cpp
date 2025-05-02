#include "../exercise.h"
#include <cstddef>
#include <iostream>

// READ: std::byte <https://zh.cppreference.com/w/cpp/types/byte>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 创建 std::byte
    std::byte b{42};
    // NOTICE: std::byte 不能隐式转换为整数，需要显式转换
    ASSERT(std::to_integer<int>(b) == ?, "std::byte to integer");

    // 2. std::byte 的位运算
    std::byte b1{0b1101'0010};
    std::byte b2{0b0011'1100};

    std::byte b_and = b1 & b2;// 按位与
    ASSERT(std::to_integer<int>(b_and) == ?, "按位与结果");

    std::byte b_or = b1 | b2;// 按位或
    ASSERT(std::to_integer<int>(b_or) == ?, "按位或结果");

    std::byte b_xor = b1 ^ b2;// 按位异或
    ASSERT(std::to_integer<int>(b_xor) == ?, "按位异或结果");

    std::byte b_not = ~b1;// 按位非
    // NOTICE: 按位非的结果取决于 std::byte 的底层表示，通常是 unsigned char
    //         所以 ~0b11010010 结果是 0b00101101 (假设 8 位)
    ASSERT(std::to_integer<int>(b_not) == ?, "按位非结果");

    // 3. std::byte 的移位运算
    std::byte b_left_shift = b1 << 2;// 左移 2 位
    ASSERT(std::to_integer<int>(b_left_shift) == ?, "左移结果");

    std::byte b_right_shift = b1 >> 3;// 右移 3 位
    ASSERT(std::to_integer<int>(b_right_shift) == ?, "右移结果");

    // 4. 修改 std::byte 的值
    b <<= 1;// 左移并赋值
    ASSERT(std::to_integer<int>(b) == ?, "左移赋值后");
    b |= std::byte{0b0000'0001};// 按位或并赋值
    ASSERT(std::to_integer<int>(b) == ?, "按位或赋值后");

    // THINK: `std::byte` 和 `unsigned char` 或 `char` 的主要区别是什么？
    // THINK: 为什么 C++17 引入了 `std::byte`？它解决了什么问题？
    // THINK: 在哪些场景下应该使用 `std::byte`？

    return 0;
}