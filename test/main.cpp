#include <graphics.h>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream my_file("index.txt");
	int temp;
	my_file >> temp;
	cout << temp+'0';
}