#include "home_page.h"
#include <graphics.h>
#include "enum_lib.h"

//在初始化时向基类传入当前页面的id
home_page::home_page(int w, int h) :abstract_page(page_id::HOME_PAGE, w, h) {

	//设置背景
	bk_img = new IMAGE();
	//背景图片放在项目文件的background_img下，命名background.png
	loadimage(bk_img, L"background_img/background.png");

	//设置标题文本
	title_text = L"简易校园导航系统";

	//设置标题尺寸
	title_size = 100;

	//设置标题的尺寸
	//在设置字体后才能算出标题宽度，算位置
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
	// 使用lambda表达式给按钮设置按下后的回调函数
	//第一个按钮：开始游戏
	my_button.push_back(new button(button_width, button_height, first_button_x, first_button_y, first_button_text, [this]() {set_next_id(page_id::MAP_SELECT_PAGE); }));
	//第二个按钮：退出游戏
	my_button.push_back(new button(button_width, button_height, second_button_x, second_button_y, second_button_text, [this]() {set_next_id(page_id::EXIT); }));

}

//接收鼠标信息
//在这个页面主要判断按钮
void home_page::get_keyboard_message() {
	
	ExMessage msg;

	while (peekmessage(&msg)) {

		//如果鼠标没有按下，调用over函数
		if (msg.message == WM_MOUSEMOVE) {
			for (button* tbutton_ptr : my_button) {
				//over函数会检查当前是否需要更新按钮对象的参数
				tbutton_ptr->checkMouseOver(msg.x, msg.y);
			}
		}

		//如果鼠标按下，调用click函数检查是否点击按钮
		//如果点击按钮，调用构造时设置的回调函数
		else if (msg.message == WM_LBUTTONDOWN) {
			for (button* tbutton_ptr : my_button) {
				tbutton_ptr->checkMouseClick(msg.x,msg.y);
			}
		}
	}
}
void home_page::draw() {

	//绘制背景
	//使用背景图片填充
	putimage(0, 0, width, height, bk_img, 0, 0);

	//在easyx中，需要调用清楚画布的函数才能重新绘制背景
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

	//释放背景图片
	delete bk_img;

	//释放按钮对象
	while (!my_button.empty()) {
		delete my_button.back();
		my_button.pop_back();
	}
}