#include "picture_button.h"

picture_button::picture_button(std::wstring path, std::wstring exp,int width,int height,int x,int y):exp(exp),width(width),height(height),x(x),y(y)
{
	opt_img = new IMAGE();
	loadimage(opt_img, path.c_str());
	//ͼƬ����
	scale = 0.8;
	real_img_x = x + (width * (1 - scale)) / 2;
	real_img_y = y + (height * (1 - scale)) / 2;
	real_img_length = width * scale;
	is_mouse_over = false;
	settextstyle(20, 0, L"����");
	real_text_x = x+(width - textwidth(exp.c_str()))/2;
	real_text_y = y+height * 0.8;

}

void picture_button::checkMouseOver(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_x) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		is_mouse_over = true;
		scale = 0.9;
	}
	else {
		is_mouse_over = false;
		scale = 0.8;
	}
}

void picture_button::checkMouseClick(int mouse_x, int mouse_y) {
	if ((mouse_x >= real_img_x) && (mouse_x <= real_img_x + real_img_x) && (mouse_y >= real_img_y) && (mouse_y <= real_img_y + real_img_length)) {
		is_mouse_over = true;
		scale = 0.9;
	}
	else {
		is_mouse_over = false;
		scale = 0.8;
	}
}

void picture_button::draw() {
	real_img_x = x + (width * (1 - scale)) / 2;
	real_img_y = y + (height * (1 - scale)) / 2;
	real_img_length = width * scale;
	putimage(real_img_x, real_img_y, real_img_length, real_img_length, opt_img, 0, 0);
	settextstyle(20, 0, L"����");
	outtextxy(real_text_x, real_img_y, exp.c_str());
}
