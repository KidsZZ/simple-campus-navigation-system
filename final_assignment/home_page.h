#pragma once
//进入程序后的第一个页面，主要功能是呈现一些简练的信息


#include <string>
#include <vector>
#include "abstract_page.h"
#include "button.h"
#include <graphics.h>

//继承abstract_page实现具体功能
class home_page :public abstract_page {
public:

	//设置页面长宽
	home_page(int w, int h);

	//修改基类中的虚函数
	//使用override确保是重载
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~home_page()override;

private:

	//背景图片
	IMAGE* bk_img;

	//标题文本
	std::wstring title_text;

	//按钮文本
	std::wstring first_button_text;
	std::wstring second_button_text;

	//使用vector储存按钮指针
	std::vector<button*> my_button;

	//标题字号大小
	int title_size;


	//页面元素定位
	int title_x, title_y;
	int button_width, button_height;
	int first_button_x, first_button_y;
	int second_button_x, second_button_y;
};