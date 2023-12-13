#pragma once
//option类是选项的基类,如开始界面的选项，地图界面的选项
//包括选项的名字，位置
class option {
public:

	//当前选项是否被选中（更新数据成员）
	void is_selected(bool);

	//选项的绘制函数
	//1.判断选项是否被选中（用不同颜色和放缩比例）
	//2.根据选项坐标和横宽比绘制选项选项
	void draw();

private:

	//记录当前选项是否被选中
	bool selected;

	//选项的横宽比
	int width, length;

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