//map_select_page的功能是让用户选择当前需要进行操作的地图
//将各个地图使用缩略图的形式绘制在选项上，以便选择
//在对象中需要保存maps对象的引用，通过maps对象调用相关函数

#pragma once

#include <vector>
#include "abstract_page.h"
#include "maps.h"
#include "button.h"

//继承abstract_page，实现具体函数
class map_select_page :public abstract_page {
public:

	//构造函数
	//要通过基类初始化页面的宽高和下一个页面id
	map_select_page(int w,int h, maps& my_maps);

	//接收鼠标数据，调用地图选项和按钮相关函数
	virtual void get_keyboard_message()override;

	//绘制画面
	virtual void draw()override;

	//析构函数
	//释放返回按键，功能按钮
	virtual ~map_select_page();

private:

	//使用maps类实现地图保存及操作(引用传递）
	maps &my_maps;

	//背景图片
	IMAGE* bk_img;

	//右边功能菜单按钮
	std::vector<button*> my_button;

	//返回按钮
	button* return_button;

	//地图尺寸
	int map_width, map_height;

	//地图选择前的缩放比
	double unselected_scale;
	//地图选择后的缩放比
	double selected_scale;

	//按钮尺寸
	int button_width, button_height;

	//按钮文本
	std::wstring first_button_text;
	std::wstring second_button_text;


	//页面元素定位相关数据
	//左地图选择模块的宽高
	int left_width, left_height;
	//右选项模块的宽高
	int  right_width, right_height;
	//按钮位置
	int first_button_x, first_button_y;
	int second_button_x, second_button_y;

	//按照先行后列的顺序存储鼠标是否在地图上
	bool is_map_over[2][2];
	//储存当前选中的地图id
	int map_selected_id;
	//地图放大前间隔空间
	int map_left_space_x;
	int map_left_space_y;
	//地图放大后间隔空间
	int map_left_space_x_selected;
	int map_left_space_y_selected;

	//四张地图当前间隔空间
	int map_real[2][2][2];
};