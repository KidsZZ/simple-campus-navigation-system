#include "home_page.h"
#include <graphics.h>
#include "enum_lib.h"
home_page::home_page(int next_id, int w, int h) :abstract_page(next_id, w, h), mouse_x(0), mouse_y(0) {
	//设置背景


	//设置标题文本
	title_text = L"欢迎使用简易校园导航系统";
	//设置标题的尺寸
	settextstyle(100, 0, L"微软雅黑");
	//设置标题位置
	//title_x = (width - textwidth(title_text.c_str())) / 2;//居中
	title_x = 600;//居中

	title_y = height * 2 / 10;//距离顶部20%的宽度

	//按钮宽度
	button_width = 400;
	//按钮高度
	button_height = 100;

	//设置第一个按钮参数
	// 按钮文本
	first_button_text = L"开始游戏";
	//按钮坐标
	first_button_x = (width - button_width / 2);
	first_button_y = (height / 2);

	//设置第二个按钮参数
	// 按钮文本
	second_button_text = L"退出游戏";
	//按钮坐标
	second_button_x = (width - button_width / 2);
	second_button_y = (height * 0.35);


	//绘制背景

	//绘制标题
	outtextxy(title_x, title_y, title_text.c_str());

	//放置按钮
	my_option.push_back(new option(button_width, button_height, first_button_x, first_button_y, first_button_text, [this]() {set_next_id(page_id::MAP_SELECT_PAGE); }));
	my_option.push_back(new option(button_width, button_height, second_button_x, second_button_y, second_button_text, [this]() {set_next_id(page_id::EXIT); }));

}

void home_page::get_keyboard_message() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		if (msg.message == WM_MOUSEMOVE) {
			for (option* toption_ptr : my_option) {
				toption_ptr->checkMouseOver(msg.x, msg.y);
			}
		}
		else if (msg.message == WM_LBUTTONDOWN) {
			for (option* toption_ptr : my_option) {
				toption_ptr->checkMouseClick(msg.x,msg.y);
			}
		}
	}
}
void home_page::draw() {
	for (option* toption_ptr : my_option) {
		toption_ptr->draw();
	}
}

home_page::~home_page() {
	while (!my_option.empty()) {
		delete my_option.back();
		my_option.pop_back();
	}
}