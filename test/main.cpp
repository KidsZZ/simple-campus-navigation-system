#include <string>
#include <graphics.h>
#include <Windows.h>
using namespace std;

class m {
public:
	m(const wstring &ws) {
		text = ws;
	}
	wstring text;
};
	
int main() {
	int a = 5;
	const double& b = a;
	m fg(L"223");
}
