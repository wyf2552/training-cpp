#include "../exercise.h"

#include <iostream>

// READ: 奇异递归模板模式 (CRTP) <https://zh.cppreference.com/w/cpp/language/crtp>

// 定义一个基类模板，使用 CRTP
template<typename Derived>
struct Base {
    void interface() {
        // 调用派生类的实现
        static_cast<Derived *>(this)->implementation();
    }

    // 静态多态：在编译时确定调用哪个函数
    void static_polymorphism() {
        std::cout << "Base::static_polymorphism()" << std::endl;
    }
};

// 定义派生类，继承自 Base<Derived>
struct Derived : public Base<Derived> {
    // 实现基类接口所调用的方法
    void implementation() {
        std::cout << "Derived::implementation()" << std::endl;
    }

    // 重写基类中的方法，展示静态多态
    void static_polymorphism() {
        std::cout << "Derived::static_polymorphism()" << std::endl;
    }
};

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    Derived d;

    // 调用基类接口，该接口会调用派生类的实现
    d.interface();

    // 直接调用派生类的方法
    d.implementation();

    // 调用静态多态方法
    d.static_polymorphism();

    // 通过基类指针调用静态多态方法
    Base<?> *base_ptr = &d;
    base_ptr->static_polymorphism();// 注意：这里调用的是基类的方法

    // 由于静态多态性，即使通过基类指针调用，实际执行的也是编译时确定的基类版本。
    // 如果需要动态多态性（运行时决定调用哪个版本），则需要使用虚函数。

    // THINK: CRTP 如何实现静态多态？它与虚函数动态多态有何不同？
    // THINK: CRTP 的优点和缺点是什么？

    return 0;
}