
//button类是选项的基类,如开始界面的选项，地图界面的选项
//包括选项的内容，位置
//在创建button类时，要注册回调函数（lambda表达式）

#pragma once
#include <string>
#include <functional>
class button {
public:

	//构造函数，初始化selected，width，height，x,y,scale
	button(int width, int height, int x, int y, const std::wstring& text, const std::function<void()>& my_fun);

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