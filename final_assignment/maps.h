#pragma once
//class maps 用于储存地图及其信息
#include <string>
#include "map.h"

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
	void draw(int width, int length, int x, int y, int id);
	//绘制当前选择的地图
	void draw_selected(int width, int length, int x, int y);
private:
	int selected_map_id;
	string path;
	map my_map[NUM];
};