#pragma once
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据
#include <string>
#include<iostream>
#include "houses.h"
#include "roads.h"
#include "enum_lib.h"
#include<fstream>
#include <string>
class map {
public:
	//传入存档路径，houses
	map(std::wstring path,const houses &my_house,const roads& my_roads,int column,int row);
	void read_file();
	void write_file();
	void draw(int width, int height, int x, int y);

	//给定坐标和房子id(road id 为0）
	void add_building(int x, int y, int house_type);

	// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
	void delete_build(int x, int y);

	//返回给定的地图id是否被编辑过
	bool is_edited(int page_id);
private:
	//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
	void tranlate_xy(int* ans, int x, int y);
	const houses& my_houses;
	const roads& my_roads;
	std::vector<std::vector<char>>mapData;
	//地图行列
	int column;
	int row;
	//存档文件的路径
	std::wstring path;
	bool is_edited(int page_id);
};