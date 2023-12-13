#pragma once
//这是主页面窗口，管理不同页面（*因为easyx不支持多窗口，所以通过对不同窗口记录index值来切换不同窗口
#include <vector>
#include "abstract_page.h"
class Widget {
public:
	//构造函数，将三个页面载入my_page,设置页面长宽比，将now_page_id设为home_page_id
	Widget(int w,int h);
	//主成员函数
	void run();
	void close();
	~Widget();
private:
	std::vector<abstract_page*> my_page;
	//页面id设置
	enum{
		home_page = 0,
		map_editing,
		navigation
	};
	//下一帧的页面id
	int now_page_id = home_page;
	//页面的宽和高
	int width, height;
};