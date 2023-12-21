#include "picture_button.h"

picture_button::picture_button(std::wstring path, std::wstring exp, int width, int height, int x, int y, std::function<void()> my_fun) :exp(exp), width(width), height(height), x(x), y(y), my_fun(my_fun)
{
	opt_img = new IMAGE();
	loadimage(opt_img, path.c_str());
	//图片缩放
	scale = 0.8;
	real_img_x = x + (width * (1 - scale)) / 2;
	real_img_y = y + (height * (1 - scale)) / 2;
	real_img_length = width * scale;
	//默认不被选中
	is_selected = false;
	settextstyle(20, 0, L"黑体");
	real_text_x = x+(width - textwidth(exp.c_str()))/2;
	real_text_y = y+height * 0.8;

}

void picture_button::checkMouseOver(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_x) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		scale = 0.9;
	}
	else {
		scale = 0.8;
	}
}

void picture_button::checkMouseClick(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_x) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		my_fun();
		is_selected = true;
	}
	else {
		is_selected = false;
	}
}

void picture_button::draw() {
	//如果选中，选项背景颜色发生更改
	if (is_selected) {
		setfillcolor(0xAAAAAA);
		rectangle(x, y, x + width, y + height);
	}
	real_img_x = x + (width * (1 - scale)) / 2;
	real_img_y = y + (height * (1 - scale)) / 2;
	real_img_length = width * scale;
	putimage(real_img_x, real_img_y, real_img_length, real_img_length, opt_img, 0, 0);
	settextstyle(20, 0, L"黑体");
	outtextxy(real_text_x, real_img_y, exp.c_str());
}
picture_button::~picture_button() {
	delete opt_img;
}
