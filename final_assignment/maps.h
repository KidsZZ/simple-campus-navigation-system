#pragma once
//class maps 用于储存地图及其信息
//模板类，实现文件要放在头文件中
#include <string>
#include "map.h"
#include "houses.h"
#include "roads.h"

//模板类实现起来太麻烦，不用了，没有必要
class maps {
public:
	//构造函数，给出数据文件位置
	maps(std::string path);
	//将文件中的数据载入内存
	void read_file();
	//返回当前选择的地图id
	int now_selected_map_id();
	//更改当前选择的地图
	void set_selected_map_id(int n);
	//将编辑过的地图数据载入文件(为了方便，全部重写）
	void write_file();
	//绘制指定id的地图
	void draw(int width,int height, int x, int y, int id);
	//绘制当前选择的地图
	void draw_selected(int width,int height, int x, int y);
	//下面三个函数都作用于selected_map_id
	//增加东西(如果已经有了就替代
	//给定坐标和房子id(road id 为0）
	void add_building(int x, int y, int house_type);
	//给定坐标
	//删除东西
	// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
	void delete_build(int x, int y);
	//连接两地（最短路）
	bool connect_houses(int house_type1, int house_type2);
	//返回给定的地图id是否被编辑过
	bool is_edited(int page_id);
private:
	const static int NUM = 4;
	//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
	void tranlate_xy(int* ans, int x, int y);
	int selected_map_id;
	std::wstring path;
	map my_map[NUM];
	roads my_roads;
	houses my_houses;
	//每个地图15列，10行
	const static int column = 15;
	const static int row = 10;
};