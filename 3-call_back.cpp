#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

//回调函数的用法,std::function和std::bind结合
/*
B类中包含了add函数和sub函数，add函数实现加法，sub函数是普通成员函数，后者实现减法，是静态成员函数
A中通过构造传入的B类中的函数，来执行
相当于B类中是用户层自定义的函数，A是系统层，实现获取回调函数和执行回调函数
*/

class A {
public:
    //等同于typedef std::function<int(int, int)> CallBack;
    using CallBack = std::function<int(int, int)>;

public:
    A() {}
    ~A() {}

    //用户设置CallBack
    A(CallBack call_back) : call_back_(call_back) {}
    
    //运行，执行CallBack
    void Run(int a, int b) {
        int res = call_back_(a, b);
        cout << "res = " << res << endl;
    }

private:
    CallBack call_back_;
};

class B {
public:
    B() {}
    ~B() {}

    //加法,类的普通成员函数
    int add (int a, int b) {
        return a + b;
    }

    //减法,类的静态成员函数
    static int sub (int a, int b) {
        return a - b;
    }
};

//测试回调函数
void test1() {
    
    //绑定类的普通成员函数及其参数，用引用，还需要实例化的对象b
    B b;
    //此时auto call_back1就是std::function<int(int, int)> call_back1
    auto call_back1 = std::bind(&B::add, b, std::placeholders::_1, std::placeholders::_2);
    A a1(call_back1);//设置回调函数
    a1.Run(2, 1);//运行

    //绑定类的静态成员函数及其参数，不加引用符号&，也不用实例化的对象b，绑定静态的可以不用std:bind
    //auto call_back2 = std::bind(B::sub, std::placeholders::_1, std::placeholders::_2);与下面一句等价
    auto call_back2 = B::sub;
    A a2(call_back2);//设置回调函数
    a2.Run(2, 1);//运行
}

int main() {
    test1();
    return 0;
}

