#pragma once
enum roads_direction{
	//对道路情况进行编号（编号遵循上左右下）
	//两个路口
	up_left, up_right, up_down, left_right, left_down, right_down,
	//三岔路
	no_up, no_left, no_right, no_down,
	//十字路口
	crossroads
};
enum house_type {
	museum = 1,
	dorminory,
	teaching_building,
	canteen
};

enum direction {
	up,
	left,
	right,
	down
};