﻿#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

template <typename T>
bool almost_equal(T a, T b, T epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}



int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(almost_equal(plus(1.25f, 2.5f), 3.75f), "Plus two float");
    ASSERT(almost_equal(plus(1.25, 2.5), 3.75), "Plus two double");
    ASSERT(almost_equal(plus(0.1, 0.2), 0.3), "How to make this pass?");
    return 0;
}
