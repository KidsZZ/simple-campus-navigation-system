#include "picture_button.h"

picture_button::picture_button(std::wstring path, std::wstring exp, int width, int height, int x, int y, std::function<void()> my_fun) :exp(exp), width(width), height(height), x(x), y(y), my_fun(my_fun)
{
	//初始化选项图片
	opt_img = new IMAGE();
	loadimage(opt_img, path.c_str());

	//图片缩放
	scale = 0.8;

	//设置图片的尺寸
	real_img_length = width * scale;
	real_img_x = x + (width -real_img_length) / 2;
	real_img_y = y + (height - real_img_length * 1.1) / 2;

	//默认鼠标不在选项上
	is_over = false;

	//得到文字尺寸
	//获得文字坐标
	settextstyle(20, 0, L"黑体");
	real_text_x = x + (width - textwidth(exp.c_str())) / 2;
	real_text_y = y + height * 0.9;

}

void picture_button::checkMouseOver(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_length) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		scale = 0.9;
		is_over = true;
	}
	else {
		scale = 0.8;
		is_over = false;
	}
}

void picture_button::checkMouseClick(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_x) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		my_fun();
	}
}

void picture_button::draw() {
	
	//根据scale更新图片尺寸
	real_img_length = width * scale;
	real_img_x = x + (width - real_img_length) / 2;
	real_img_y = y + (height - real_img_length * 1.1) / 2;

	//放置选项图片
	putimage(real_img_x, real_img_y, real_img_length, real_img_length, opt_img, 0, 0);

	//放置文字
	settextstyle(20, 0, L"黑体");
	outtextxy(real_text_x, real_img_y, exp.c_str());
}
picture_button::~picture_button() {
	delete opt_img;
}
