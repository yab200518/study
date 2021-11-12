#include <iostream>
using namespace std;

//类内static静态成员函数用法
//B，C属于同一个类中的static函数，B中调用C可以不加类名
//B，A属于两个类中国的static函数，B中调用A需要使用类名

class A {
 public:
  A() = default;
  ~A() = default;
  static void PrintA();
};

class B {
 public:
  B() = default;
  ~B() = default;
  static void PrintB();
  static void PrintC();
};

void B::PrintC() {
  cout << "ccc" << endl;
}

void A::PrintA() {
  cout << "aaa" << endl;
}

void B::PrintB() {
  A::PrintA();//不同的类必须用类名
  PrintC();//同一个类可以不用类名
}

int main() {
  B::PrintB();
  return 0;
}


