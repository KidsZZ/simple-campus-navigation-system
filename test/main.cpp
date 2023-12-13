#include <iostream>
#include <cstdio>
using namespace std;
class base {
public:
	virtual void print();
protected:
	void fun();
};
void base::fun() {
	printf("base fun()\n");
}
void base::print() {
	fun();
}
class son :public base {
private:
	virtual void print()override;
protected:
	void fun();
};
void son::print() {
	fun();
}
void son::fun() {
	printf("son fun()\n");
}

int main() {
	base* b = new son();
	b->print();
}