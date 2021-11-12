#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

//stds::function用法
//绑定类普通成员函数时需要用到std::bind

//p_fun等价于函数指针，指向参数<int, int>，返回值为bool的函数
std::function<bool(int, int)> p_fun;

//1,普通函数
bool cmp_com(int a, int b) {
    return a > b;
}

//2,lambda表达式
auto cmp_lmd = [](int a, int b) { return a > b; };

//3,仿函数
class cmp_class {
public:
    bool operator () (int a, int b) {
        return a > b;
    }
};

class cmp {
public:
    //4,类普通成员函数
    bool cmp_member(int a, int b) {
        return a > b;
    }

    //5,类静态成员函数
    static bool cmp_static(int a, int b) {
        return a > b;
    }
};

void test1() {
    bool res;

    //1,绑定普通函数
    p_fun = cmp_com;
    res = p_fun(10, 1);
    cout << "普通函数输出, res is " << res << endl;

    //2,绑定lambda表达式
    p_fun = cmp_lmd;
    res = p_fun(10, 1);
    cout << "lambda表达式输出, res is " << res << endl;

    //3,绑定仿函数，用到类名()，需要加括号
    p_fun = cmp_class();
    res = p_fun(10, 1);
    cout << "仿函数输出, res is " << res << endl;

    //4,绑定类静态成员函数，用法是类名::函数名
    p_fun = cmp::cmp_static;
    res = p_fun(10, 1);
    cout << "类静态成员函数输出, res is " << res << endl;

    //5,绑定类普通成员函数
    //需要实例化对象并且需要用std::bind且其第一个参数加&，若p_fun属于一个类成员变量，则参数cmp1可换成this
    cmp cmp1;
    p_fun = std::bind(&cmp::cmp_member, cmp1, std::placeholders::_1, std::placeholders::_2);
    res = p_fun(10, 1);
    cout << "类普通成员函数输出, res is " << res << endl;
}

int main() {
    test1();
    return 0;
}