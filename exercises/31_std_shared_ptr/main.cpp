#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
void TestSharedPtr() {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == ?, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == ?, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == ?, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == ?, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == ?, "");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == ?, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == ?, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == ?, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == ?, "");
}

// NOTICE: shared_ptr 的循环引用问题
class A;
class B;
struct A {
    std::shared_ptr<B> ptr;
    ~A() { std::cout << "A destroyed" << std::endl; }
};
struct B {
    std::shared_ptr<A> ptr;
    ~B() { std::cout << "B destroyed" << std::endl; }
}

void TestSharedPtrCycle() {
    // TODO： 写一个测试用例，展示 shared_ptr 的循环引用问题
    // NOTICE：使用 `std::weak_ptr` 可以解决循环引用问题。
}

template<typename T>
class MySharedPtr {
    // TODO: 实现 shared_ptr 的基本功能
    // NOTICE: 面试时经常会问到 shared_ptr 的实现原理，建议自己独立实现一个简单的 shared_ptr。
    // 例如，构造函数、析构函数、移动构造函数、移动赋值运算符等。
}

int main(int argc, char **argv) {
    TestSharedPtr();
    TestSharedPtrCycle();

    // NOTICE: 在这里使用自己实现的 shared_ptr
    MySharedPtr<int> ptr = MySharedPtr<int>(new int(10));
    MySharedPtr<int> ptr2 = ptr;
    MySharedPtr<int> ptr3 = std::move(ptr);
    ptr = ptr2;
    ptr = std::move(ptr3);

    // TODO: 将下列 `?` 替换为正确的值
    ASSERT(ptr.use_count() == ?, "");
    ASSERT(ptr2.use_count() == ?, "");
    ASSERT(ptr3.use_count() == ?, "");
    return 0;
}
