#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//函数对象（仿函数）的用法

class A {
public:
    //重载()运算符，从大到小排序
    bool operator()(int& a, int& b) {
        return a > b;
    }
};

//第一种用法：实例化
void test1() {
    A a;//实例化一个a
    vector<int> res = {3, 5, 2, 6, 1, 4};

    //用实例化的a作为排序标准，此时用a，不带括号
    sort(res.begin(), res.end(), a);
    for(auto i : res) {
        cout << i << ' ';
    }
    cout << endl;
}

//第二种用法：不需要实例化，直接用类名()
void test2() {
    vector<int> res = {3, 5, 2, 6, 1, 4};
    
    //用类名作为排序标准，此时用A()，需要加括号
    sort(res.begin(), res.end(), A());
    for(auto i : res) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    test1();
    test2();
    return 0;
}