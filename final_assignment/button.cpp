#include "button.h"
#include <graphics.h>

button::button(int width, int height, int x, int y, const std::wstring& text, const std::function<void()>& on_Click) :text(text), is_mouse_over(false), width(width), height(height), x(x), y(y), scale(1.0), on_Click(on_Click){
	//draw();
}

void button::draw() {

	//根据是否选择更改按钮的配色
	if (is_mouse_over) {
		setlinecolor(RGB(BRS, BGS, BBS));
		setfillcolor(RGB(FRS, FGS, FBS));
	}
	else {
		setlinecolor(RGB(BR, BG, BB));
		setfillcolor(RGB(FR, FG, FB));
	}

	// 缩放后的按钮宽度
	int scaledWidth = width * scale; 

	// 缩放后的按钮高度
	int scaledHeight = height * scale; 

	// 缩放后的按钮x坐标
	int scaledX = x + (width - scaledWidth) / 2; 

	// 缩放后的按钮y坐标
	int scaledY = y + (height - scaledHeight) / 2; 

	// 绘制按钮
	fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); 

	//设置文本颜色为黑色
	settextcolor(BLACK); 

	//设置文本背景透明
	setbkmode(TRANSPARENT);

	//文本大小
	settextstyle(35 * scale, 0, _T("微软雅黑"));

	//居中显示按钮文本
	//计算文本在按钮中央的x坐标
	int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; 
	//计算文本在按钮中央的y坐标

	//在按钮上绘制文本
	int textY = scaledY + (scaledHeight - textheight(_T("TEST"))) / 2; 
	outtextxy(textX, textY, text.c_str()); 
}


//判断鼠标是否在选项上，并据此修改is_mouse_over和scale
bool button::checkMouseOver(int mouse_x,int mouse_y) {
	if (is_mouse_over = (mouse_x >= x) && (mouse_x <= (x + width)) && (mouse_y >= y) && (mouse_y <= (y + height))) {
		scale = 0.9;
		return true;
	}
	else {
		scale = 1.0;
		return false;
	}
}

bool button::checkMouseClick(int mouse_x, int mouse_y)
{
	if ((mouse_x != 0 || mouse_y != 0) && (mouse_x >= x) && (mouse_x <= (x + width)) && (mouse_y >= y) && (mouse_y <= (y + height))) {
		on_Click();
		return true;
	}
	else {
		return false;
	}
}
