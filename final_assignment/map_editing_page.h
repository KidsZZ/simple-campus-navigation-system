//此函数实现对map_select_map中选择的地图的编辑
//分为两个部分，
//右边呈现预设的建筑，供用户选择
//左边放置地图，用户可以通过点击地图上的格子实现对右边选择的建筑的放置

#pragma once

#include <vector>
#include "abstract_page.h"
#include "maps.h"
#include "picture_button.h"
#include "button.h"

//class map_editing实现对地图的编辑
class map_editing_page :public abstract_page {
public:
	
	//构造函数
	map_editing_page(int w, int h, maps& my_maps);

	//对基类构造函数中虚函数的重载
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~map_editing_page();
	virtual int return_page_id()override;

private:

	//背景图片
	IMAGE* bk_img;

	//使用maps类实现地图保存及操作(引用传递）
	maps& my_maps;

	//设置当前选择的建筑id
	//该函数为为右边选择建筑的按钮的回调函数
	void set_now_select_building_id(int id) {
		now_select_building = id;
	}

	//创建右边的建筑选项
	std::vector<picture_button*> my_picture_button;

	//返回按键
	button* return_button;

	//当前选择的建筑
	//在绘制已选择的建筑时，对其背景进行特殊处理
	int now_select_building;

	//地图元素坐标
	// 左边地图部分占比
	int left_width, left_height;
	// 右边选项部分占比
	int right_width, right_height;
	// 地图实际长度（居中）
	int map_width;
	// 地图实际宽度
	int map_height;
	//地图实际坐标
	int map_real_x;
	int map_real_y;

	// 一个建筑选项的长宽(指右边选项中的建筑）（外层尺寸）
	int single_object_width;
	int single_object_height;
	
};