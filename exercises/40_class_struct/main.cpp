#include "../exercise.h"
#include <memory>
#include <string>

// READ: class 和 struct 的区别 <https://learn.microsoft.com/zh-cn/cpp/cpp/struct-cpp?view=msvc-170>

// 定义一个结构体和一个类
struct MyStruct {
    int data; // 默认是 public
};

class MyClass {
    int data; // 默认是 private
public:
    void setData(int value) { data = value; }
    int getData() const { return data; }
};

// 定义基类结构体
struct BaseStruct {
    int base_data = 1;
};

// 定义基类类
class BaseClass {
public:
    int base_data = 2;
};

// 派生结构体和类
struct DerivedStruct : BaseStruct { // 默认 public 继承
    int derived_data = 3;
};

class DerivedClass : BaseClass { // 默认 private 继承
    int derived_data = 4;

// 如何能让外部访问基类的成员？
public: // 需要将方法声明为 public
    int get_base_data() const { return base_data; } // 需要公有方法访问基类成员
    int get_derived_data() const { return derived_data; } // 添加公有方法访问私有成员
};

struct DerivedStructFromClass : BaseClass { // 默认 public 继承
    int derived_data = 5;
};

class DerivedClassFromStruct : BaseStruct { // 默认 private 继承
    int derived_data = 6;
public:
    int get_base_data() const { return base_data; }
    int get_derived_data() const { return derived_data; } // 添加公有方法访问私有成员
};


int main(int argc, char **argv) {
    // 成员访问权限测试
    MyStruct s;
    s.data = 10; // 可以直接访问 struct 的成员
    ASSERT(s.data == 10, "结构体成员默认是 public");

    MyClass c;
    // c.data = 20; // 编译错误！类成员默认是 private
    c.setData(20); // 通过公有方法设置私有成员
    ASSERT(c.getData() == 20, "类成员默认是 private，需要通过公有方法访问");

    // 继承访问权限测试
    DerivedStruct ds;
    ASSERT(ds.base_data == 1, "结构体默认 public 继承，可以访问基类 public 成员");
    ASSERT(ds.derived_data == 3, "派生结构体可以访问自己的成员");

    DerivedClass dc;
    // ASSERT(dc.base_data == 2, "类默认 private 继承，无法直接访问基类 public 成员"); // 编译错误
    ASSERT(dc.get_base_data() == 2, "通过派生类的公有方法访问基类成员");
    // ASSERT(dc.derived_data == 4, "派生类无法直接访问自己的 private 成员"); // 编译错误
    ASSERT(dc.get_derived_data() == 4, "通过公有方法访问派生类的私有成员");

    DerivedStructFromClass dsfc;
    ASSERT(dsfc.base_data == 2, "结构体继承类，默认 public 继承，可以访问基类 public 成员");
    ASSERT(dsfc.derived_data == 5, "派生结构体可以访问自己的成员");

    DerivedClassFromStruct dcfs;
    // ASSERT(dcfs.base_data == 1, "类继承结构体，默认 private 继承，无法直接访问基类 public 成员"); // 编译错误
    ASSERT(dcfs.get_base_data() == 1, "通过派生类的公有方法访问基类成员");
    // ASSERT(dcfs.derived_data == 6, "派生类无法直接访问自己的 private 成员"); // 编译错误
    ASSERT(dcfs.get_derived_data() == 6, "通过公有方法访问派生类的私有成员");

    return 0;
}