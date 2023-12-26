#pragma once
//enum_lib中使用enum储存各类常量，确保在类间的信息通信正确高效
//道路朝向
enum roads_direction{
	//对道路情况进行编号（编号遵循上左右下）
	//两个路口
	up_left=1, up_right, up_down, left_right, left_down, right_down,
	//三岔路
	no_up, no_left, no_right, no_down,
	//十字路口
	crossroads
};

//房屋种类
enum house_type {
	road=0,
	library,
	dorminory,
	teaching_building,
	canteen
};

//判断房门朝向所使用的传参常量
enum direction {
	up=0,
	left,
	right,
	down
};

//页面类型
enum page_id {
	HOME_PAGE = 0,
	MAP_SELECT_PAGE,
	MAP_EDITING_PAGE,
	NAVIGATION_PAGE,
	EXIT
};

//不包括道路的建筑数量
const int building_num = 4;
