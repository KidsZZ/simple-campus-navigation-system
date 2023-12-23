#include <graphics.h>

int main() {
	initgraph(200, 200);
	IMAGE* my_img = new IMAGE();
	loadimage(my_img, L"pic",L"background");
	putimage(0, 0, 200, 200, my_img, 0, 0);
	while (true);
}