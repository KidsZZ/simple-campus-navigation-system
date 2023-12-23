#include "home_page.h"
#include <graphics.h>
#include "enum_lib.h"
home_page::home_page(int w, int h) :abstract_page(page_id::HOME_PAGE, w, h), mouse_x(0), mouse_y(0) {
	//设置背景


	//设置标题文本
	title_text = L"简易校园导航系统";
	//设置标题尺寸
	title_size = 100;
	//设置标题的尺寸
	settextstyle(title_size, 0, L"华文新魏");
	//设置标题位置
	title_x = (width - textwidth(title_text.c_str())) / 2;//居中
	title_y = height * 0.15;//距离顶部20%的宽度


	//按钮宽度
	button_width = 400;
	//按钮高度
	button_height = 100;

	//设置第一个按钮参数
	// 按钮文本
	first_button_text = L"开始游戏";
	//按钮坐标
	first_button_x = (width - button_width) / 2;
	first_button_y = (height / 2);

	//设置第二个按钮参数
	// 按钮文本
	second_button_text = L"退出游戏";
	//按钮坐标
	second_button_x = (width - button_width) / 2;
	second_button_y = (height * 0.75);


	//放置按钮
	my_button.push_back(new button(button_width, button_height, first_button_x, first_button_y, first_button_text, [this]() {set_next_id(page_id::MAP_SELECT_PAGE); }));
	my_button.push_back(new button(button_width, button_height, second_button_x, second_button_y, second_button_text, [this]() {set_next_id(page_id::EXIT); }));

	//draw();

}

void home_page::get_keyboard_message() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		if (msg.message == WM_MOUSEMOVE) {
			for (button* tbutton_ptr : my_button) {
				tbutton_ptr->checkMouseOver(msg.x, msg.y);
			}
		}
		else if (msg.message == WM_LBUTTONDOWN) {
			for (button* tbutton_ptr : my_button) {
				tbutton_ptr->checkMouseClick(msg.x,msg.y);
			}
		}
	}
}
void home_page::draw() {
	//绘制背景
	setbkcolor(LIGHTBLUE);
	cleardevice();
	//绘制标题
	settextstyle(title_size, 0, L"仿宋");
	outtextxy(title_x, title_y, title_text.c_str());
	//绘制按钮
	for (button* tbutton_ptr : my_button) {
		tbutton_ptr->draw();
	}
}

home_page::~home_page() {
	while (!my_button.empty()) {
		delete my_button.back();
		my_button.pop_back();
	}
}