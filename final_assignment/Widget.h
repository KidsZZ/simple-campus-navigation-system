#pragma once
//这是主页面窗口，管理不同页面（*因为easyx不支持多窗口，所以通过对不同窗口记录index值来切换不同窗口
#include <vector>
#include <string>
#include "abstract_page.h"
#include "maps.h"
#include "enum_lib.h"
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
	//页面id设置(废弃，使用统一my_mpas传参)
	//int previous_page_id = HOME_PAGE;
	//下一帧的页面id
	int now_page_id = HOME_PAGE;
	//页面的宽和高
	int width, height;
	//使用4个地图存档
	static const int show_maps_num = 4;
	//保存地图信息
	maps<show_maps_num> my_maps;
	const static std::string path;
};