#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
void TestSharedPtr() {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 1, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 2, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");
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
};

void TestSharedPtrCycle() {
    // TODO： 写一个测试用例，展示 shared_ptr 的循环引用问题
    // NOTICE：使用 `std::weak_ptr` 可以解决循环引用问题。
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->ptr = b;
    b->ptr = a;
}

template<typename T>
class MySharedPtr {
    // TODO: 实现 shared_ptr 的基本功能
    // NOTICE: 面试时经常会问到 shared_ptr 的实现原理，建议自己独立实现一个简单的 shared_ptr。
    // 例如，构造函数、析构函数、移动构造函数、移动赋值运算符等。

private:
    T* ptr = nullptr;
    int* refCount = nullptr;

    void release() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

public:
    explicit MySharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)) {}

    ~MySharedPtr() { release(); }

    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    MySharedPtr(MySharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }

    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    int use_count() const {
        return refCount ? *refCount : 0;
    }

    T* get() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

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
    ASSERT(ptr.use_count() == 2, "");
    ASSERT(ptr2.use_count() == 2, "");
    ASSERT(ptr3.use_count() == 0, "");
    return 0;
}
