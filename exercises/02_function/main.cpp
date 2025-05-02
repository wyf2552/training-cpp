#include "../exercise.h"
#include <string>
#include <vector>

// READ: 声明 <https://zh.cppreference.com/w/cpp/language/declarations>
// NOTICE: cppreference 中的示例中指出了复杂声明的解读法，建议认真阅读。
// NOTICE: 补充由内而外读法的机翻解释 <https://learn.microsoft.com/zh-cn/cpp/c-language/interpreting-more-complex-declarators?view=msvc-170>

// TODO: 在这里声明函数
// 基本函数声明练习

// 函数重载练习

// 数组操作函数练习

// 字符串处理函数练习
std::string reverse_string(const std::string& str);

int main(int argc, char **argv) {
    // 基本函数练习
    ASSERT(add(123, 456) == ?, "add(123, 456) should be ?");
    auto x = 1, y = 2;
    std::cout << x << " + " << y << " = " << add(x, y) << std::endl;

    // 函数重载练习
    ASSERT(add(3.14, 2.86) == ?, "add(3.14, 2.86) should be ?");
    ASSERT(add(std::string("Hello, "), std::string("World!")) == ?, "add(\"Hello, \", \"World!\") should be ?");

    // 数组操作练习
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    ASSERT(sum_array(numbers) == ?, "sum_array({1, 2, 3, 4, 5}) should be ?");

    // 字符串处理练习
    ASSERT(reverse_string("hello") == ?, "reverse_string(\"hello\") should be ?");

    return 0;
}

// TODO: 补全函数定义，但不要移动代码行
int add(int a, int b) {
}

double add(double a, double b) {
}

std::string add(const std::string& a, const std::string& b) {
}

int sum_array(const std::vector<int>& arr) {
}

std::string reverse_string(const std::string& str) {
}
