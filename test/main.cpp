#include <graphics.h>
#include <iostream>
using namespace std;

int main() {
	int a = 2;
	cout << char(a + '0');
	char temp;
	cin >> temp;
	cout << int(temp-'0');
}