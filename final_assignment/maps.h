#pragma once
//class maps 用于储存地图及其信息
//模板类，实现文件要放在头文件中
#include <string>
#include "map.h"
#include "houses.h"
#include "roads.h"

template<int NUM=4>
class maps {
public:
	//构造函数，给出数据文件位置
	maps(std::string path);
	//将文件中的数据载入内存
	void read_file();
	//更改当前选择的地图
	void set_selected_map_id(int n);
	//将编辑过的地图数据载入文件(为了方便，全部重写）
	void write_file();
	//绘制指定id的地图
	void draw(int length, int x, int y, int id);
	//绘制当前选择的地图
	void draw_selected(int length, int x, int y);
	//下面三个函数都作用于selected_map_id
	//给定坐标和房子id
	void change_house(int x, int y, int house_type);
	//给定坐标
	void change_road(int x, int y);
	//连接两地（最短路）
	bool connect_houses(int house_type, int house_type);
private:
	int selected_map_id;
	string path;
	map my_map[NUM];
	roads my_roads;
	houses my_houses;
	//每个地图15列，10行
	const static int column = 15;
	const static int row = 10;
};