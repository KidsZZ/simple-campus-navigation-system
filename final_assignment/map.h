#pragma once
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据
#include <string>
#include<iostream>
#include "houses.h"
#include "roads.h"
#include"lines.h"
#include "enum_lib.h"
#include<fstream>
#include <string>
class map {
public:
	friend maps;
	//传入存档路径，houses
	map(std::wstring path,const houses &my_house,const roads& my_roads, lines& my_lines, int column,int row, int width, int height);
	//在maps初始化时调用下方此函数
	map(std::wstring path, const houses& my_house, const roads& my_roads,  lines& my_lines, int column, int row);
	void read_file();
	void write_file();
	void draw(int width, int height, int x, int y);

	//给定坐标和房子id(road id 为0）
	void add_building(int x, int y, int house_type);

	// 给定坐标(删除房子和道路用一个函数）
	void delete_build(int x, int y);

	//返回给定的地图id是否被编辑过
	bool is_edited(int page_id);

	//判断若绘制道路的话属于哪种道路类型
	int select_road_type(int i,int j);
	
private:
	//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
	void tranlate_xy(int* ans, int x, int y);
	const houses& my_houses;
	const roads& my_roads;
	lines& my_lines;
	std::vector<std::vector<char>>mapData;
	//地图行列
	int column;
	int row;
	//地图长宽
	int height;
	int width;
	//存档文件的路径
	std::wstring path;
	//bool类型的数组用于判断道路的种类
	bool is_edited(int page_id);
	//记录(x,y)所对应的格子
	static int real_coord[2];
};