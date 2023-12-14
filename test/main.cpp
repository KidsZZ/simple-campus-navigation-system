#include <cstdio>

class A {
public:
    A(int& value) : a(value) {}  // 使用构造函数初始化列表将成员a绑定到一个整数引用上
    int& a;
};

int main() {
    int value = 5;
    A obj(value);
    obj.a = 9;
    printf("%d", value);
    // 现在成员a已经被初始化并绑定到变量value上
    return 0;
}
