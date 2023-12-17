#pragma once

#include "abstract_page.h"
#include "maps.h"
#include <vector>
class map_select_page :public abstract_page {
public:
	//构造函数，要通过基类初始化页面的宽高和下一个页面id
	map_select_page(int next_id,int w,int h, maps<show_maps_num>& my_maps);
	//virtual void update_maps()override;
	virtual void get_keyboard_message()override;
	virtual void draw()override;

	virtual ~map_select_page();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps<show_maps_num> &my_maps;
	//默认选择第一张地图
	int now_selected_page_id = page_id::HOME_PAGE;
	//左地图选择模块的宽高
	int left_width, left_height;
	//右选项模块的宽高
	int  right_width, right_height;
	//地图尺寸
	int map_width, map_height;
	//地图选择前的缩放比
	double unselected_scale;
	//地图选择后的缩放比
	double selected_scale;
};