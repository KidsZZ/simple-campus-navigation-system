#include <iostream>
#include <windows.h>
//option类是选项的基类,如开始界面的选项，地图界面的选项
//包括选项的内容，位置
//在创建option类时，要注册回调函数（lambda表达式）
#include <string>
#include <functional>
class option {
public:
	//构造函数，初始化selected，width，height，x,y,scale
	option(int width, int height, int x, int y, const std::wstring& text, const std::function<void()>& my_fun);
	//检查鼠标是否在选项上（更新数据成员）
	bool checkMouseOver(int mouse_x, int mouse_y);

	//检测鼠标是否按下按钮
	bool checkMouseClick(int mouse_x, int mouse_y);

	//选项的绘制函数
	//1.判断选项是否被选中（用不同颜色和放缩比例）
	//2.根据选项坐标和横宽比绘制选项选项
	void draw();

protected:
	//回调函数(检测到按钮按下时调用)
	std::function<void()> on_Click;
	//按钮文本信息
	std::wstring text;

	//记录当前选项是否被选中
	bool is_mouse_over;

	//选项的宽高
	int width, height;

	//选项的位置
	int x, y;

	//选项选中时的参数
	//1.放缩比
	double scale;
	//2.选择时的颜色(selected)
	int BRS = 0, BGS = 120, BBS = 215;//边框(border)
	int FRS = 229, FGS = 241, FBS = 251;//填充（filled）
	//3.未选择时的颜色
	int  BR = 173, BG = 173, BB = 173;
	int FR = 225, FG = 225, FB = 225;
};
//using namespace std;

#include <graphics.h>

option::option(int width, int height, int x, int y, const std::wstring& text, const std::function<void()>& on_Click) :text(text), is_mouse_over(false), width(width), height(height), x(x), y(y), scale(1.0), on_Click(on_Click) {
	//draw();
}

void option::draw() {
	if (is_mouse_over) {
		setlinecolor(RGB(BRS, BGS, BBS));
		setfillcolor(RGB(FRS, FGS, FBS));
	}
	else {
		setlinecolor(RGB(BR, BG, BB));
		setfillcolor(RGB(FR, FG, FB));
	}
	int scaledWidth = width * scale; // 缩放后的按钮宽度
	int scaledHeight = height * scale; // 缩放后的按钮高度
	int scaledX = x + (width - scaledWidth) / 2; // 缩放后的按钮x坐标
	int scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标
	fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮
	settextcolor(BLACK); // 设置文本颜色为黑色
	setbkmode(TRANSPARENT); // 设置文本背景透明
	settextstyle(35 * scale, 0, _T("微软雅黑"));//文本大小
	//居中显示按钮文本
	int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // 计算文本在按钮中央的x坐标
	int textY = scaledY + (scaledHeight - textheight(_T("TEST"))) / 2; // 计算文本在按钮中央的y坐标
	outtextxy(textX, textY, text.c_str()); // 在按钮上绘制文本
}


//判断鼠标是否在选项上，并据此修改is_mouse_over和scale
bool option::checkMouseOver(int mouse_x, int mouse_y) {
	if (is_mouse_over = (mouse_x >= x) && (mouse_x <= (x + width)) && (mouse_y >= y) && (mouse_y <= (y + height))) {
		scale = 0.9;
		return true;
	}
	else {
		scale = 1.0;
		return false;
	}
}

bool option::checkMouseClick(int mouse_x, int mouse_y)
{
	if ((mouse_x >= x) && (mouse_x <= (x + width)) && (mouse_y >= y) && (mouse_y <= (y + height))) {
		on_Click();
		return true;
	}
	else {
		return false;
	}
}

#include <iostream>
int main() {
	initgraph(1920, 1690);
	option* my_option = new option(400, 100, 800, 600, L"lidhlkdjfd", []() {std::cout << "hello world!"; });
	while (true) {
		my_option->draw();
	}
	return 0;
}