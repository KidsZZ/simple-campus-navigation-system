#pragma once
#include "abstract_page.h"
#include "maps.h"
#include "picture_button.h"
#include <vector>
#include "button.h"
//class map_editing实现对地图的编辑
class map_editing_page :public abstract_page {
public:
	map_editing_page(int w, int h, maps& my_maps);
	//virtual void update_maps()override;
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~map_editing_page();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps& my_maps;
	//设置当前选择的建筑id
	void set_now_select_building_id(int id) {
		now_select_building = id;
	}
	//创建右边的建筑选项
	std::vector<picture_button*> my_picture_button;
	//返回按键
	button* return_button;
	//当前选择的建筑
	int now_select_building;
	// 左边地图部分占比
	int left_width, left_height;
	// 右边选项部分占比
	int right_width, right_height;
	// 地图实际长度（居中）
	int map_width;
	// 地图实际宽度
	int map_height;
	//地图左边的空间
	int map_real_x;
	int map_real_y;
	// 一个建筑选项的长宽(指右边选项中的建筑）（外层尺寸）
	int single_object_width;
	int single_object_height;
	
};