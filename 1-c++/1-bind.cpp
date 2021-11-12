#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

//std::bind的用法
//全局函数和类的静态成员函数可用std::bind,也可不用
//类的普通成员函数必须用std::bind

//1,全局函数
bool cmp_com(int a, int b) {
    return a > b;
}

class cmp {
public:
    //2,类静态成员函数
    static bool cmp_static(int a, int b) {
        return a > b;
    }

    //3,类普通成员函数
    bool cmp_member(int a, int b) {
        return a > b;
    }
};

//不同函数的绑定方式
void test1() {
    bool res;

    //若用auto则此句可以省去，即：auto p = std::bind(cmp_com, 1, 3);
    std::function<bool()> p; 

    //1,绑定全局函数，不用引用，可以不用std:bind
    p = std::bind(cmp_com, 1, 3);
    res = p();
    cout << "普通函数输出, res is " << res << endl;

    //2,绑定类静态成员函数，不用引用，用法是类名::函数名,可以不用std:bind
    p = std::bind(cmp::cmp_static, 1, 3);
    res = p();
    cout << "类静态成员函数输出, res is " << res << endl;

    //3,绑定类普通成员函数,函数前需要添加引用，多一个变量参数cmp1,必须用std:bind
    //需要实例化对象并且需要用std::bind且其第一个参数加&，若p是一个类的成员变量，则参数cmp1可换成this
    cmp cmp1;
    p = std::bind(&cmp::cmp_member, cmp1, 1, 3);
    res = p();
    cout << "类普通成员函数输出, res is " << res << endl;

    //1和2可以不用std::bind，以1举例,等价于下面代码, 但是3必须用bind
    //std::function<bool(int,int)> p = cmp_com;
    //res = p(1, 3);
}

//占位符的使用
void test2() {
    bool res;

    //1,不用占位符,function输入参数变为空
    //若用auto，则直接auto p1 = std::bind(cmp_com, 1, 3);不用再考虑类型
    std::function<bool(void)> p1 = std::bind(cmp_com, 1, 3);
    res = p1();//输出0
    cout << "普通函数输出, res is " << res << endl;

    //2,用一个占位符,function输入参数变为int
    //若用auto，则直接auto p2 = std::bind(cmp_com, std::placeholders::_1, 3);不用再考虑类型
    std::function<bool(int)> p2 = std::bind(cmp_com, std::placeholders::_1, 3);
    res = p2(4); //输出1
    cout << "普通函数输出, res is " << res << endl;

    //3,用两个占位符,function输入参数变为int,int
    //若用auto，则直接auto p3 = std::bind(cmp_com, std::placeholders::_1, std::placeholders::_2);不用再考虑类型
    std::function<bool(int,int)> p3 = std::bind(cmp_com, std::placeholders::_1, std::placeholders::_2);
    res = p3(4, 3); //输出1
    cout << "普通函数输出, res is " << res << endl;

    //4,用两个占位符,并颠倒位置,function输入参数变为int,int
    //若用auto，则直接auto p3 = std::bind(cmp_com, std::placeholders::_2, std::placeholders::_1);不用再考虑类型
    std::function<bool(int,int)> p4 = std::bind(cmp_com, std::placeholders::_2, std::placeholders::_1);
    res = p4(4, 3); //输出0
    cout << "普通函数输出, res is " << res << endl;
}

int main() {
    test1();
    cout << "********************" << endl;
    test2(); 
    return 0;
}

