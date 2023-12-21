#pragma once
//单个map，使用maps进行管理
//具体存储单张地图数据，并
#include <string>
#include "houses.h"
#include "roads.h"
#include "enum_lib.h"
#include<fstream>
#include <string>
class map {
public:
	//传入存档路径，houses
	map(std::wstring path,const houses &my_house,const roads& my_roads);
	void draw(int width,int height, int x, int y);
	void read_file();
	void write_file();
private:
	//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
	void tranlate_xy(int* ans, int x, int y);
	const houses& my_houses;
	const roads& my_roads;
	std::vector<std::string>mapData;
	//地图行列
	int column;
	int row;
	//存档文件的路径
	std::wstring path;
};