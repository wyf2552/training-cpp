#include "../exercise.h"
#include <bitset>
#include <limits>
#include <string>

// READ: std::bitset <https://zh.cppreference.com/w/cpp/utility/bitset>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 创建一个 8 位的 bitset，所有位初始化为 0
    std::bitset<8> bs1;
    ASSERT(bs1.to_string() == "?", "bs1 初始应为 00000000");

    // 从 unsigned long long 创建 bitset
    unsigned long long val = 0b1101;
    std::bitset<8> bs2(val);
    ASSERT(bs2.to_string() == "?", "bs2 应为 00001101");

    // 从 std::string 创建 bitset
    std::string bits = "101010";
    std::bitset<8> bs3(bits);
    ASSERT(bs3.to_string() == "?", "bs3 应为 00101010");

    // 设置单个位 (set)
    bs1.set(0);// 设置最低位 (索引 0)
    bs1.set(7);// 设置最高位 (索引 7)
    ASSERT(bs1.to_string() == "?", "bs1 设置第 0 和 7 位后");

    // 重置单个位 (reset)
    bs1.reset(0);
    ASSERT(bs1.to_string() == "?", "bs1 重置第 0 位后");

    // 翻转单个位 (flip)
    bs1.flip(7);
    ASSERT(bs1.to_string() == "?", "bs1 翻转第 7 位后");

    // 测试单个位 (test)
    ASSERT(bs2.test(?) == true, "bs2 的第 0 位应为 1");
    ASSERT(bs2.test(?) == false, "bs2 的第 1 位应为 0");
    ASSERT(bs2.test(?) == true, "bs2 的第 2 位应为 1");

    // 获取位集中 1 的数量 (count)
    ASSERT(bs2.count() == ?, "bs2 中 1 的数量");

    // 获取位集的大小 (size)
    ASSERT(bs1.size() == ?, "bs1 的大小");

    // 检查是否有任何位为 1 (any)
    ASSERT(bs2.any() == ?, "bs2 应该有位为 1");
    std::bitset<8> bs_zero;
    ASSERT(bs_zero.any() == ?, "bs_zero 不应有位为 1");

    // 检查是否所有位都为 1 (all)
    std::bitset<4> bs_all_set("1111");
    ASSERT(bs_all_set.all() == ?, "bs_all_set 所有位都为 1");
    ASSERT(bs2.all() == ?, "bs2 不应所有位都为 1");

    // 检查是否没有位为 1 (none)
    ASSERT(bs_zero.none() == ?, "bs_zero 应该没有位为 1");
    ASSERT(bs2.none() == ?, "bs2 不应没有位为 1");

    // 位运算：AND (&), OR (|), XOR (^), NOT (~)
    std::bitset<8> op1("11001100");
    std::bitset<8> op2("10101010");

    std::bitset<8> res_and = op1 & op2;
    ASSERT(res_and.to_string() == "?", "op1 & op2");

    std::bitset<8> res_or = op1 | op2;
    ASSERT(res_or.to_string() == "?", "op1 | op2");

    std::bitset<8> res_xor = op1 ^ op2;
    ASSERT(res_xor.to_string() == "?", "op1 ^ op2");

    std::bitset<8> res_not = ~op1;
    ASSERT(res_not.to_string() == "?", "~op1");

    // 位移：左移 (<<), 右移 (>>)
    std::bitset<8> shift_target("00011000");
    std::bitset<8> res_left = shift_target << 2;
    ASSERT(res_left.to_string() == "?", "shift_target << 2");

    std::bitset<8> res_right = shift_target >> 1;
    ASSERT(res_right.to_string() == "?", "shift_target >> 1");

    // 转换为整数 (to_ulong, to_ullong)
    std::bitset<8> bs_num("00001111");
    ASSERT(bs_num.to_ulong() == ?, "转换为 unsigned long");

    // THINK: std::bitset 和普通的整数类型在位操作方面有什么异同？
    // THINK: std::bitset 的大小在编译时确定，这带来了哪些优缺点？

    return 0;
}